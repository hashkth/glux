#include "oal_bindings.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstring>

// ---------------- WaveData helpers ----------------
size_t WaveData::n_samples() const {
    // number of frames (per channel)
    if (channels <= 0) return 0;
    return samples.size() / channels;
}

double WaveData::duration() const {
    if (channels <= 0 || sample_rate <= 0) return 0.0;
    return static_cast<double>(n_samples()) / static_cast<double>(sample_rate);
}

// ----------------- Decoders (internal) -----------------
// Return false on failure. Fill samples (interleaved int16), channels and sample rate.
static bool decode_wav_file(const std::string& filename, std::vector<int16_t>& out_samples, int& out_channels, int& out_sample_rate) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    // Minimal WAV parser: expects PCM (format=1) and 16-bit samples
    char riff[4];
    uint32_t file_size;
    char wave[4];

    file.read(riff, 4);
    file.read(reinterpret_cast<char*>(&file_size), 4);
    file.read(wave, 4);
    if (std::strncmp(riff, "RIFF", 4) != 0 || std::strncmp(wave, "WAVE", 4) != 0) {
        return false;
    }

    int16_t audio_format = 0;
    int16_t num_channels = 0;
    int sample_rate = 0;
    int16_t bits_per_sample = 0;

    std::vector<char> data_chunk;

    while (file) {
        char chunk_id[4] = {0};
        uint32_t chunk_size = 0;
        file.read(chunk_id, 4);
        if (!file) break;
        file.read(reinterpret_cast<char*>(&chunk_size), 4);
        if (std::strncmp(chunk_id, "fmt ", 4) == 0) {
            file.read(reinterpret_cast<char*>(&audio_format), 2);
            file.read(reinterpret_cast<char*>(&num_channels), 2);
            file.read(reinterpret_cast<char*>(&sample_rate), 4);
            file.ignore(6); // byteRate + blockAlign
            file.read(reinterpret_cast<char*>(&bits_per_sample), 2);
            if (chunk_size > 16) {
                file.ignore(chunk_size - 16);
            }
        } else if (std::strncmp(chunk_id, "data", 4) == 0) {
            data_chunk.resize(chunk_size);
            file.read(data_chunk.data(), chunk_size);
        } else {
            file.ignore(chunk_size);
        }
    }

    if (audio_format != 1) return false; // only PCM
    if (bits_per_sample != 16) return false; // only 16-bit for now
    if (data_chunk.empty()) return false;

    size_t total_samples = data_chunk.size() / 2;
    out_samples.resize(total_samples);
    std::memcpy(out_samples.data(), data_chunk.data(), data_chunk.size());
    out_channels = num_channels;
    out_sample_rate = sample_rate;
    return true;
}

static bool decode_ogg_file(const std::string& filename, std::vector<int16_t>& out_samples, int& out_channels, int& out_sample_rate) {
    int error = 0;
    stb_vorbis* v = stb_vorbis_open_filename(filename.c_str(), &error, nullptr);
    if (!v) return false;
    stb_vorbis_info info = stb_vorbis_get_info(v);
    out_channels = info.channels;
    out_sample_rate = info.sample_rate;

    int total_frames = stb_vorbis_stream_length_in_samples(v);
    if (total_frames <= 0) {
        // fallback: read until EOF
        std::vector<int16_t> buffer;
        std::vector<int16_t> temp(4096);
        int read;
        while ((read = stb_vorbis_get_samples_short_interleaved(v, out_channels, temp.data(), temp.size())) > 0) {
            buffer.insert(buffer.end(), temp.begin(), temp.begin() + read * out_channels);
        }
        out_samples.swap(buffer);
    } else {
        out_samples.resize(static_cast<size_t>(total_frames) * out_channels);
        int got = stb_vorbis_get_samples_short_interleaved(v, out_channels, out_samples.data(), static_cast<int>(out_samples.size()));
        out_samples.resize(static_cast<size_t>(got) * out_channels);
    }
    stb_vorbis_close(v);
    return !out_samples.empty();
}

static bool decode_mp3_file(const std::string& filename, std::vector<int16_t>& out_samples, int& out_channels, int& out_sample_rate) {
    drmp3 mp3;
    if (!drmp3_init_file(&mp3, filename.c_str(), nullptr)) return false;
    out_channels = mp3.channels;
    out_sample_rate = mp3.sampleRate;

    drmp3_uint64 total_frames = drmp3_get_pcm_frame_count(&mp3);
    if (total_frames == 0) {
        // try streaming read
        std::vector<int16_t> tmp;
        drmp3_uint64 frames_read = drmp3_read_pcm_frames_s16(&mp3, UINT64_MAX, nullptr);
        // dr_mp3 doesn't provide easy streaming to vector without knowing size,
        // but most files will give a frame count above.
        drmp3_uninit(&mp3);
        return false;
    }
    out_samples.resize(static_cast<size_t>(total_frames) * out_channels);
    drmp3_read_pcm_frames_s16(&mp3, total_frames, out_samples.data());
    drmp3_uninit(&mp3);
    return !out_samples.empty();
}

static std::string to_lower(const std::string& s) {
    std::string o = s;
    std::transform(o.begin(), o.end(), o.begin(), [](unsigned char c){ return std::tolower(c); });
    return o;
}

static bool decode_file_by_ext(const std::string& path, WaveData& out) {
    // simple extension-based dispatch; could augment with header sniffing
    auto pos = path.find_last_of('.');
    if (pos == std::string::npos) return false;
    std::string ext = to_lower(path.substr(pos + 1));
    std::vector<int16_t> samples;
    int channels = 0, rate = 0;
    bool ok = false;
    if (ext == "wav" || ext == "wave") {
        ok = decode_wav_file(path, samples, channels, rate);
    } else if (ext == "ogg" || ext == "oga") {
        ok = decode_ogg_file(path, samples, channels, rate);
    } else if (ext == "mp3") {
        ok = decode_mp3_file(path, samples, channels, rate);
    } else {
        // try header sniff: check OggS or RIFF
        std::ifstream f(path, std::ios::binary);
        if (!f) return false;
        char header[4] = {0};
        f.read(header, 4);
        f.close();
        std::string h(header, 4);
        if (h == "RIFF") ok = decode_wav_file(path, samples, channels, rate);
        else if (h == "OggS") ok = decode_ogg_file(path, samples, channels, rate);
        else ok = false;
    }

    if (!ok) return false;
    out.samples = std::move(samples);
    out.channels = channels;
    out.sample_rate = rate;
    out.bits_per_sample = 16;
    return true;
}

// ----------------- OpenAL helpers -----------------
void OpenALContext::check_al_error(const std::string& where) {
    ALenum e = alGetError();
    if (e != AL_NO_ERROR) {
        std::ostringstream ss;
        ss << where << " (AL error " << std::hex << e << ")";
        throw std::runtime_error(ss.str());
    }
}

void OpenALContext::make_current() const {
    if (!context_) throw std::runtime_error("OpenAL context not initialized");
    if (!alcMakeContextCurrent(context_)) throw std::runtime_error("Failed to make context current");
}

// ----------------- OpenALContext implementation -----------------
OpenALContext::OpenALContext() {
    device_ = alcOpenDevice(nullptr); // default device
    if (!device_) throw std::runtime_error("Failed to open OpenAL device");
    context_ = alcCreateContext(device_, nullptr);
    if (!context_) {
        alcCloseDevice(device_);
        device_ = nullptr;
        throw std::runtime_error("Failed to create OpenAL context");
    }
    if (!alcMakeContextCurrent(context_)) {
        alcDestroyContext(context_);
        alcCloseDevice(device_);
        context_ = nullptr;
        device_ = nullptr;
        throw std::runtime_error("Failed to make OpenAL context current");
    }
}

OpenALContext::~OpenALContext() {
    // if context still current, clear it first
    try {
        if (context_) {
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(context_);
            context_ = nullptr;
        }
        if (device_) {
            alcCloseDevice(device_);
            device_ = nullptr;
        }
    } catch (...) {
        // destructors must not throw
    }
}

std::string OpenALContext::get_device_name() const {
    if (!device_) return std::string();
    const ALCchar* dev = alcGetString(device_, ALC_DEVICE_SPECIFIER);
    return dev ? std::string(dev) : std::string();
}

std::shared_ptr<ALSource> OpenALContext::create_source() {
    // Keep shared_ptr to this context so context lives
    auto self = shared_from_this();
    return std::make_shared<ALSource>(self);
}

std::shared_ptr<ALBuffer> OpenALContext::create_buffer_from_file(const std::string& path) {
    WaveData data = decode_file(path);
    auto self = shared_from_this();
    return std::make_shared<ALBuffer>(self, std::move(data));
}

WaveData OpenALContext::decode_file(const std::string& path) {
    WaveData w;
    if (!decode_file_by_ext(path, w)) {
        throw std::runtime_error("Failed to decode audio file: " + path);
    }
    return w;
}

OpenALContextPtr OpenALContext::enter() {
    // ensure made current
    make_current();
    return shared_from_this();
}

void OpenALContext::exit() {
    // user called exit; actual cleanup will happen in destructor when last shared_ptr dies
    // but here we explicitly unbind context (safe no-op if already unbound)
    if (context_) {
        alcMakeContextCurrent(nullptr);
    }
}

// ----------------- ALBuffer implementation -----------------
ALBuffer::ALBuffer(OpenALContextPtr ctx, WaveData&& data)
    : ctx_(std::move(ctx)), data_(std::move(data)) {
    // must ensure context is current before uploading
    ctx_->make_current();

    alGenBuffers(1, &buf_id_);
    OpenALContext::check_al_error("alGenBuffers");

    // choose format (mono/stereo only for simplicity)
    ALenum format = 0;
    if (data_.channels == 1) format = AL_FORMAT_MONO16;
    else if (data_.channels == 2) format = AL_FORMAT_STEREO16;
    else {
        // For more channels, OpenAL extensions are needed; refuse for now
        throw std::runtime_error("Unsupported channel count for ALBuffer: " + std::to_string(data_.channels));
    }

    alBufferData(buf_id_, format, data_.samples.data(),
                 static_cast<ALsizei>(data_.samples.size() * sizeof(int16_t)),
                 data_.sample_rate);
    OpenALContext::check_al_error("alBufferData");
}

ALBuffer::~ALBuffer() {
    if (buf_id_ != 0 && ctx_) {
        try {
            ctx_->make_current(); // ensure context alive and current
            alDeleteBuffers(1, &buf_id_);
        } catch (...) {
            // swallow exceptions in destructor
        }
    }
}

ALBuffer::ALBuffer(ALBuffer&& o) noexcept
    : ctx_(std::move(o.ctx_)), buf_id_(o.buf_id_), data_(std::move(o.data_)) {
    o.buf_id_ = 0;
    o.ctx_.reset();
}

ALBuffer& ALBuffer::operator=(ALBuffer&& o) noexcept {
    if (this != &o) {
        if (buf_id_ != 0 && ctx_) {
            try { ctx_->make_current(); alDeleteBuffers(1, &buf_id_); } catch (...) {}
        }
        ctx_ = std::move(o.ctx_);
        buf_id_ = o.buf_id_;
        data_ = std::move(o.data_);
        o.buf_id_ = 0;
    }
    return *this;
}

ALuint ALBuffer::id() const { return buf_id_; }
const WaveData& ALBuffer::data() const { return data_; }

// ----------------- ALSource implementation -----------------
ALSource::ALSource(OpenALContextPtr ctx) : ctx_(std::move(ctx)) {
    ctx_->make_current();
    alGenSources(1, &src_id_);
    OpenALContext::check_al_error("alGenSources");
}

ALSource::~ALSource() {
    if (src_id_ != 0 && ctx_) {
        try {
            ctx_->make_current();
            alDeleteSources(1, &src_id_);
        } catch (...) {
            // swallow
        }
    }
}

ALSource::ALSource(ALSource&& o) noexcept : ctx_(std::move(o.ctx_)), src_id_(o.src_id_) {
    o.src_id_ = 0;
}

ALSource& ALSource::operator=(ALSource&& o) noexcept {
    if (this != &o) {
        if (src_id_ != 0 && ctx_) {
            try { ctx_->make_current(); alDeleteSources(1, &src_id_); } catch (...) {}
        }
        ctx_ = std::move(o.ctx_);
        src_id_ = o.src_id_;
        o.src_id_ = 0;
    }
    return *this;
}

ALuint ALSource::id() const { return src_id_; }

void ALSource::play(const ALBuffer& buffer) {
    if (!ctx_) throw std::runtime_error("Context expired for source");
    ctx_->make_current();
    alSourcei(src_id_, AL_BUFFER, static_cast<ALint>(buffer.id()));
    OpenALContext::check_al_error("alSourcei(AL_BUFFER)");
    alSourcePlay(src_id_);
    OpenALContext::check_al_error("alSourcePlay");
}

void ALSource::pause() {
    ctx_->make_current();
    alSourcePause(src_id_);
    OpenALContext::check_al_error("alSourcePause");
}

void ALSource::resume() {
    ctx_->make_current();
    ALint state = 0;
    alGetSourcei(src_id_, AL_SOURCE_STATE, &state);
    if (state == AL_PAUSED) {
        alSourcePlay(src_id_);
        OpenALContext::check_al_error("alSourcePlay (resume)");
    }
}

void ALSource::stop() {
    ctx_->make_current();
    alSourceStop(src_id_);
    alSourcei(src_id_, AL_BUFFER, 0);
    OpenALContext::check_al_error("alSourceStop");
}

void ALSource::rewind() {
    ctx_->make_current();
    alSourceRewind(src_id_);
    OpenALContext::check_al_error("alSourceRewind");
}

void ALSource::set_looping(bool loop) {
    ctx_->make_current();
    alSourcei(src_id_, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
    OpenALContext::check_al_error("alSourcei(AL_LOOPING)");
}

void ALSource::set_gain(float g) {
    ctx_->make_current();
    alSourcef(src_id_, AL_GAIN, g);
    OpenALContext::check_al_error("alSourcef(AL_GAIN)");
}

void ALSource::set_offset_seconds(float sec) {
    ctx_->make_current();
    alSourcef(src_id_, AL_SEC_OFFSET, sec);
    OpenALContext::check_al_error("alSourcef(AL_SEC_OFFSET)");
}

float ALSource::get_offset_seconds() const {
    ctx_->make_current();
    float off = 0.0f;
    alGetSourcef(src_id_, AL_SEC_OFFSET, &off);
    return off;
}

bool ALSource::is_playing() const {
    ctx_->make_current();
    ALint state = 0;
    alGetSourcei(src_id_, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool ALSource::is_paused() const {
    ctx_->make_current();
    ALint state = 0;
    alGetSourcei(src_id_, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

bool ALSource::is_stopped() const {
    ctx_->make_current();
    ALint state = 0;
    alGetSourcei(src_id_, AL_SOURCE_STATE, &state);
    return state == AL_STOPPED || state == AL_INITIAL;
}

// ========== Streaming decoders ==========

// --- WavStreamDecoder ---
WavStreamDecoder::WavStreamDecoder(const std::string& path) : file_(path, std::ios::binary) {
    if(!file_) throw std::runtime_error("WAV: failed to open " + path);

    char riff[4]; uint32_t file_size = 0; char wave[4];
    file_.read(riff,4); file_.read(reinterpret_cast<char*>(&file_size),4); file_.read(wave,4);
    if(std::strncmp(riff,"RIFF",4)!=0 || std::strncmp(wave,"WAVE",4)!=0)
        throw std::runtime_error("WAV: not a RIFF/WAVE file");

    int16_t audio_format=0, num_channels=0, bps=0; int sr=0;
    bool have_fmt=false, have_data=false;
    while(file_) {
        char id[4]; uint32_t sz=0;
        file_.read(id,4); if(!file_) break;
        file_.read(reinterpret_cast<char*>(&sz),4);
        if(std::strncmp(id,"fmt ",4)==0) {
            file_.read(reinterpret_cast<char*>(&audio_format),2);
            file_.read(reinterpret_cast<char*>(&num_channels),2);
            file_.read(reinterpret_cast<char*>(&sr),4);
            file_.ignore(6); // byteRate+blockAlign
            file_.read(reinterpret_cast<char*>(&bps),2);
            if(sz>16) file_.ignore(sz-16);
            have_fmt=true;
        } else if(std::strncmp(id,"data",4)==0) {
            data_offset_ = static_cast<uint64_t>(file_.tellg());
            data_bytes_ = sz;
            file_.seekg(sz, std::ios::cur);
            have_data = true;
        } else {
            file_.seekg(sz, std::ios::cur);
        }
        if(have_fmt && have_data) break;
    }
    if(audio_format!=1 || bps!=16) throw std::runtime_error("WAV: only PCM16 supported");
    channels_ = num_channels;
    sample_rate_ = sr;
    rewind();
}

size_t WavStreamDecoder::read_frames(int16_t* dst, size_t max_frames) {
    const size_t bytes_req = max_frames * channels_ * sizeof(int16_t);
    file_.read(reinterpret_cast<char*>(dst), static_cast<std::streamsize>(bytes_req));
    size_t got_bytes = static_cast<size_t>(file_.gcount());
    bytes_read_ += got_bytes;
    return got_bytes / (channels_*sizeof(int16_t));
}

void WavStreamDecoder::rewind() {
    file_.clear();
    file_.seekg(static_cast<std::streamoff>(data_offset_), std::ios::beg);
    bytes_read_ = 0;
}

// --- OggStreamDecoder ---
OggStreamDecoder::OggStreamDecoder(const std::string& path) {
    int err=0;
    v_ = stb_vorbis_open_filename(path.c_str(), &err, nullptr);
    if(!v_) throw std::runtime_error("OGG: open failed");
    stb_vorbis_info info = stb_vorbis_get_info(v_);
    channels_ = info.channels;
    sample_rate_ = info.sample_rate;
}

OggStreamDecoder::~OggStreamDecoder() {
    if(v_) stb_vorbis_close(v_);
}

size_t OggStreamDecoder::read_frames(int16_t* dst, size_t max_frames) {
    // returns sample frames read
    int got = stb_vorbis_get_samples_short_interleaved(v_, channels_, dst,
                                                       static_cast<int>(max_frames*channels_));
    return static_cast<size_t>(got);
}

void OggStreamDecoder::rewind() {
    if(v_) stb_vorbis_seek_start(v_);
}

// --- Mp3StreamDecoder ---
Mp3StreamDecoder::Mp3StreamDecoder(const std::string& path) : path_(path) {
    inited_ = drmp3_init_file(&mp3_, path.c_str(), nullptr);
    if(!inited_) throw std::runtime_error("MP3: open failed");
    channels_ = mp3_.channels;
    sample_rate_ = mp3_.sampleRate;
}

Mp3StreamDecoder::~Mp3StreamDecoder() {
    if(inited_) drmp3_uninit(&mp3_);
}

size_t Mp3StreamDecoder::read_frames(int16_t* dst, size_t max_frames) {
    if(!inited_) return 0;
    drmp3_uint64 got = drmp3_read_pcm_frames_s16(&mp3_, static_cast<drmp3_uint64>(max_frames), dst);
    return static_cast<size_t>(got);
}

void Mp3StreamDecoder::rewind() {
    if(inited_) { drmp3_uninit(&mp3_); }
    inited_ = drmp3_init_file(&mp3_, path_.c_str(), nullptr);
}

// Factory
static std::string ext_lower(const std::string& p) {
    auto pos = p.find_last_of('.');
    if(pos==std::string::npos) return {};
    std::string e = p.substr(pos+1);
    std::transform(e.begin(), e.end(), e.begin(), [](unsigned char c){ return std::tolower(c); });
    return e;
}

std::unique_ptr<IAudioDecoder> make_stream_decoder(const std::string& path) {
    std::string e = ext_lower(path);
    if(e=="wav" || e=="wave") return std::make_unique<WavStreamDecoder>(path);
    if(e=="ogg" || e=="oga")  return std::make_unique<OggStreamDecoder>(path);
    if(e=="mp3")               return std::make_unique<Mp3StreamDecoder>(path);
    // Fallback: sniff header
    std::ifstream f(path, std::ios::binary);
    if(!f) throw std::runtime_error("Unknown audio format: " + path);
    char h[4]={0}; f.read(h,4);
    if(std::string(h,4)=="RIFF") return std::make_unique<WavStreamDecoder>(path);
    if(std::string(h,4)=="OggS") return std::make_unique<OggStreamDecoder>(path);
    throw std::runtime_error("Unsupported audio format for streaming: " + path);
}

// ========== ALStream implementation ==========
ALStream::ALStream(OpenALContextPtr ctx) : ctx_(std::move(ctx)) {
    init_source_();
}

ALStream::~ALStream() {
    try {
        stop();
        if(src_) {
            ctx_->make_current();
            alDeleteSources(1, &src_);
        }
    } catch (...) {}
}

void ALStream::init_source_() {
    ctx_->make_current();
    alGenSources(1, &src_);
    OpenALContext::check_al_error("ALStream alGenSources");
    alGenBuffers(kNumBuffers, bufs_);
    OpenALContext::check_al_error("ALStream alGenBuffers");
}

void ALStream::play(const std::string& path, bool loop) {
    stop(); // clear any previous
    looping_ = loop;

    dec_ = make_stream_decoder(path);
    channels_ = dec_->channels();
    sample_rate_ = dec_->sample_rate();

    if(channels_!=1 && channels_!=2) {
        throw std::runtime_error("ALStream: only mono/stereo supported for now");
    }

    // prepare a reusable chunk buffer
    chunk_.resize(kChunkFrames * channels_);

    queue_initial_();

    // kick off playback
    ctx_->make_current();
    alSourcePlay(src_);
    OpenALContext::check_al_error("ALStream alSourcePlay");
}

void ALStream::queue_initial_() {
    ctx_->make_current();
    int queued = 0;
    for(int i=0;i<kNumBuffers;i++) {
        if(!refill_one_(bufs_[i])) break;
        alSourceQueueBuffers(src_, 1, &bufs_[i]);
        queued++;
    }
    if(queued==0) throw std::runtime_error("ALStream: no audio data to queue");
}

bool ALStream::refill_one_(ALuint buf) {
    // read up to kChunkFrames from decoder
    size_t got = dec_->read_frames(chunk_.data(), kChunkFrames);
    buffer_frames_[buf] = got;
    if(got==0) {
        if(looping_) {
            dec_->rewind();
            got = dec_->read_frames(chunk_.data(), kChunkFrames);
        }
        if(got==0) return false;
    }

    ctx_->make_current();
    ALenum fmt = (channels_==1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(buf, fmt, chunk_.data(),
                 static_cast<ALsizei>(got * channels_ * sizeof(int16_t)),
                 sample_rate_);
    OpenALContext::check_al_error("ALStream alBufferData");
    return true;
}

void ALStream::update() {
    ctx_->make_current();
    ALint processed = 0;
    alGetSourcei(src_, AL_BUFFERS_PROCESSED, &processed);
    while(processed-- > 0) {
        ALuint b=0;
        alSourceUnqueueBuffers(src_, 1, &b);
        OpenALContext::check_al_error("ALStream unqueue");

        // Update playback cursor with how many frames were in this buffer
        auto it = buffer_frames_.find(b);
        if (it != buffer_frames_.end()) {
            play_cursor_sec_ += double(it->second) / double(sample_rate_);
            buffer_frames_.erase(it);
        }

        if(refill_one_(b)) {
            alSourceQueueBuffers(src_, 1, &b);
            OpenALContext::check_al_error("ALStream requeue");
        }
    }

    // If we ran out of data and the source stopped, restart (non-looping end is allowed to stop)
    ALint state=0;
    alGetSourcei(src_, AL_SOURCE_STATE, &state);
    if(state!=AL_PLAYING) {
        // Check if still have queued buffers (e.g., after refill)
        ALint queued=0; alGetSourcei(src_, AL_BUFFERS_QUEUED, &queued);
        if(queued>0) {
            alSourcePlay(src_);
        }
    }
}

void ALStream::stop() {
    ctx_->make_current();
    alSourceStop(src_);
    OpenALContext::check_al_error("ALStream stop");
    // Unqueue any buffers
    ALint queued=0; alGetSourcei(src_, AL_BUFFERS_QUEUED, &queued);
    while(queued-- > 0) {
        ALuint b=0; alSourceUnqueueBuffers(src_, 1, &b);
    }
    // No need to delete/recreate buffers each time; keep them for reuse
    dec_.reset();
    play_cursor_sec_ = 0.0;
}

void ALStream::pause() {
    ctx_->make_current();
    alSourcePause(src_);
}

void ALStream::resume() {
    ctx_->make_current();
    alSourcePlay(src_);
}

bool ALStream::is_playing() const {
    ctx_->make_current();
    ALint s=0; alGetSourcei(src_, AL_SOURCE_STATE, &s);
    return s==AL_PLAYING;
}

void ALStream::set_gain(float g) {
    ctx_->make_current();
    alSourcef(src_, AL_GAIN, g);
}

bool ALStream::is_paused() const {
    ctx_->make_current();
    ALint state = 0;
    alGetSourcei(src_, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

bool ALStream::is_stopped() const {
    ctx_->make_current();
    ALint state = 0;
    alGetSourcei(src_, AL_SOURCE_STATE, &state);
    return state == AL_STOPPED || state == AL_INITIAL;
}

float ALStream::get_offset_seconds() const {
    ctx_->make_current();
    float off = 0.0f;
    alGetSourcef(src_, AL_SEC_OFFSET, &off);
    return static_cast<float>(play_cursor_sec_ + off);
}

void ALStream::set_offset_seconds(float sec) {
    ctx_->make_current();
    stop();          // stop + unqueue buffers
    dec_->rewind();  // reset decoder

    // Skip frames until reaching target position
    int64_t target_frames = static_cast<int64_t>(sec * sample_rate_);
    std::vector<int16_t> dummy(kChunkFrames * channels_);
    int64_t skipped = 0;
    while (skipped < target_frames) {
        int64_t to_read = std::min<int64_t>(kChunkFrames, target_frames - skipped);
        size_t got = dec_->read_frames(dummy.data(), static_cast<size_t>(to_read));
        if (got == 0) break; // EOF
        skipped += got;
    }

    play_cursor_sec_ = sec;
    queue_initial_();
    alSourcePlay(src_);
}


// ----------------- Pybind11 bindings -----------------
void bind_oal(py::module_& m) {
    py::class_<WaveData>(m, "WaveData")
        .def_readonly("samples", &WaveData::samples) // exposes vector<int16_t>
        .def_readonly("channels", &WaveData::channels)
        .def_readonly("sample_rate", &WaveData::sample_rate)
        .def_readonly("bits_per_sample", &WaveData::bits_per_sample)
        .def_property_readonly("nsamples", &WaveData::n_samples)
        .def_property_readonly("duration", &WaveData::duration)
        .def("to_bytes", &WaveData::to_bytes);

    py::class_<OpenALContext, OpenALContextPtr>(m, "Context")
        .def(py::init([](){ return std::make_shared<OpenALContext>(); }))
        .def("__enter__", [](OpenALContext& self){ return self.enter(); })
        .def("__exit__", [](OpenALContext& self, py::object, py::object, py::object){ self.exit(); })
        .def("get_device_name", &OpenALContext::get_device_name)
        .def("source", &OpenALContext::create_source)
        .def("buffer", &OpenALContext::create_buffer_from_file)
        .def("stream", [](OpenALContext& self){
            return std::make_shared<ALStream>(self.shared_from_this());
            })
        .def_static("decode", &OpenALContext::decode_file);

    py::class_<ALBuffer, std::shared_ptr<ALBuffer>>(m, "Buffer")
        .def("id", &ALBuffer::id)
        .def("data", &ALBuffer::data, py::return_value_policy::reference_internal);

    py::class_<ALSource, std::shared_ptr<ALSource>>(m, "Source")
        .def("id", &ALSource::id)
        .def("play", &ALSource::play)
        .def("pause", &ALSource::pause)
        .def("resume", &ALSource::resume)
        .def("stop", &ALSource::stop)
        .def("rewind", &ALSource::rewind)
        .def("set_looping", &ALSource::set_looping)
        .def("set_gain", &ALSource::set_gain)
        .def("set_offset", &ALSource::set_offset_seconds)
        .def("get_offset", &ALSource::get_offset_seconds)
        .def("is_playing", &ALSource::is_playing)
        .def("is_paused", &ALSource::is_paused)
        .def("is_stopped", &ALSource::is_stopped);

    py::class_<ALStream, std::shared_ptr<ALStream>>(m, "Stream")
        .def(py::init<OpenALContextPtr>())
        .def("play", &ALStream::play, py::arg("path"), py::arg("loop") = false)
        .def("pause", &ALStream::pause)
        .def("resume", &ALStream::resume)
        .def("stop", &ALStream::stop)
        .def("update", &ALStream::update)
        .def("is_playing", &ALStream::is_playing)
        .def("is_paused", &ALStream::is_paused)
        .def("is_stopped", &ALStream::is_stopped)
        .def("set_gain", &ALStream::set_gain)
        .def("set_offset", &ALStream::set_offset_seconds)
        .def("get_offset", &ALStream::get_offset_seconds)
        .def_property_readonly("channels", &ALStream::channels)
        .def_property_readonly("sample_rate", &ALStream::sample_rate);

    // helpful constants
    m.attr("AL_FORMAT_MONO16") = AL_FORMAT_MONO16;
    m.attr("AL_FORMAT_STEREO16") = AL_FORMAT_STEREO16;
}

