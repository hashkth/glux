#pragma once

#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <unordered_map>

#include <AL/al.h>
#include <AL/alc.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#define STB_VORBIS_IMPLEMENTATION
#include "stb_vorbis.c"

#define DR_MP3_IMPLEMENTATION
#include "dr_mp3.h"

namespace py = pybind11;

struct WaveData {
    std::vector<int16_t> samples; // interleaved PCM16
    int channels = 0;
    int sample_rate = 0;
    int bits_per_sample = 16;

    // convenience accessors
    size_t n_samples() const; // total sample frames (per channel)
    double duration() const;  // seconds

    // expose raw PCM as Python bytes
    py::bytes raw_data() const {
        return py::bytes(reinterpret_cast<const char*>(samples.data()),
                         samples.size() * sizeof(int16_t));
    }
};

class OpenALContext;
using OpenALContextPtr = std::shared_ptr<OpenALContext>;

class ALBuffer {
public:
    // Construct from decoded WaveData (uploads to OpenAL)
    ALBuffer(OpenALContextPtr ctx, WaveData&& data);
    ~ALBuffer();

    // non-copyable, movable
    ALBuffer(const ALBuffer&) = delete;
    ALBuffer& operator=(const ALBuffer&) = delete;
    ALBuffer(ALBuffer&&) noexcept;
    ALBuffer& operator=(ALBuffer&&) noexcept;

    ALuint id() const;
    const WaveData& data() const;

private:
    OpenALContextPtr ctx_; // keep context alive while buffer exists
    ALuint buf_id_ = 0;
    WaveData data_;
};

class ALSource {
public:
    ALSource(OpenALContextPtr ctx);
    ~ALSource();

    ALSource(const ALSource&) = delete;
    ALSource& operator=(const ALSource&) = delete;
    ALSource(ALSource&&) noexcept;
    ALSource& operator=(ALSource&&) noexcept;

    ALuint id() const;

    // Playback controls
    void play(const ALBuffer& buffer);
    void pause();
    void resume();
    void stop();
    void rewind();

    // Properties
    void set_looping(bool loop);
    void set_gain(float g);
    void set_offset_seconds(float sec);
    float get_offset_seconds() const;
    bool is_playing() const;
    bool is_paused() const;
    bool is_stopped() const;

private:
    OpenALContextPtr ctx_;
    ALuint src_id_ = 0;
};

class OpenALContext : public std::enable_shared_from_this<OpenALContext> {
public:
    OpenALContext();
    ~OpenALContext();

    // no copying/moving
    OpenALContext(const OpenALContext&) = delete;
    OpenALContext& operator=(const OpenALContext&) = delete;

    // Python-friendly helpers
    std::string get_device_name() const;

    // create resource wrappers
    std::shared_ptr<ALSource> create_source();
    std::shared_ptr<ALBuffer> create_buffer_from_file(const std::string& path);

    // decoding function exposed (useful if user wants decoded data only)
    static WaveData decode_file(const std::string& path);

    // context manager helpers (for Python)
    OpenALContextPtr enter(); // returns shared_ptr to self
    void exit(); // cleans up (calls destructor behaviour)

    // helpers
    void make_current() const;
    static void check_al_error(const std::string& where);

private:
    friend class ALBuffer;
    friend class ALSource;

    ALCdevice* device_ = nullptr;
    ALCcontext* context_ = nullptr;
};


// --- Streaming decoders + ALStream ----------------------------------------
class IAudioDecoder {
public:
    virtual ~IAudioDecoder() = default;
    virtual int channels() const = 0;
    virtual int sample_rate() const = 0;
    // Read up to max_frames; returns frames actually read. Interleaved PCM16.
    virtual size_t read_frames(int16_t* dst, size_t max_frames) = 0;
    // Rewind to beginning (for looping)
    virtual void rewind() = 0;
};

// Streamable WAV (PCM16) decoder
class WavStreamDecoder : public IAudioDecoder {
public:
    explicit WavStreamDecoder(const std::string& path);
    ~WavStreamDecoder() override = default;
    int channels() const override { return channels_; }
    int sample_rate() const override { return sample_rate_; }
    size_t read_frames(int16_t* dst, size_t max_frames) override;
    void rewind() override;

private:
    std::ifstream file_;
    int channels_ = 0;
    int sample_rate_ = 0;
    int bits_per_sample_ = 16;
    uint64_t data_offset_ = 0;
    uint64_t data_bytes_ = 0;
    uint64_t bytes_read_ = 0;
};

// Streamable Ogg Vorbis decoder (stb_vorbis)
class OggStreamDecoder : public IAudioDecoder {
public:
    explicit OggStreamDecoder(const std::string& path);
    ~OggStreamDecoder() override;
    int channels() const override { return channels_; }
    int sample_rate() const override { return sample_rate_; }
    size_t read_frames(int16_t* dst, size_t max_frames) override;
    void rewind() override;

private:
    stb_vorbis* v_ = nullptr;
    int channels_ = 0;
    int sample_rate_ = 0;
};

// Streamable MP3 decoder (dr_mp3)
class Mp3StreamDecoder : public IAudioDecoder {
public:
    explicit Mp3StreamDecoder(const std::string& path);
    ~Mp3StreamDecoder() override;
    int channels() const override { return channels_; }
    int sample_rate() const override { return sample_rate_; }
    size_t read_frames(int16_t* dst, size_t max_frames) override;
    void rewind() override;

private:
    drmp3 mp3_{};
    bool inited_ = false;
    int channels_ = 0;
    int sample_rate_ = 0;
    std::string path_; // for rewind
};

// Factory
std::unique_ptr<IAudioDecoder> make_stream_decoder(const std::string& path);

// Queue-based streaming source
class ALStream {
public:
    explicit ALStream(OpenALContextPtr ctx);
    ~ALStream();

    // Non-copyable
    ALStream(const ALStream&) = delete;
    ALStream& operator=(const ALStream&) = delete;

    // Controls
    void play(const std::string& path, bool loop=false);
    void stop();
    void pause();
    void resume();
    bool is_playing() const;
    bool is_paused() const;
    bool is_stopped() const;
    void set_offset_seconds(float sec);
    float get_offset_seconds() const;

    // Call this regularly (e.g., per frame) to keep buffers filled
    void update();

    // Properties
    void set_gain(float g);
    int channels() const { return channels_; }
    int sample_rate() const { return sample_rate_; }


private:
    void init_source_();
    void queue_initial_();
    bool refill_one_(ALuint buf);

    OpenALContextPtr ctx_;
    std::unique_ptr<IAudioDecoder> dec_;
    ALuint src_ = 0;
    static constexpr int kNumBuffers = 4;
    static constexpr size_t kChunkFrames = 4096; // per channel frames per buffer (tweakable)
    ALuint bufs_[kNumBuffers]{};
    std::vector<int16_t> chunk_; // reused storage
    bool looping_ = false;
    int channels_ = 0;
    int sample_rate_ = 0;
    // Playback tracking
    double play_cursor_sec_ = 0.0;  // how many seconds have been played so far
    std::unordered_map<ALuint, size_t> buffer_frames_; // frames queued per buffer
};

void bind_oal(py::module_& m);