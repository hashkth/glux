
#include "window.h"
#include "input.h"


// Keep track of Window instance per GLFWwindow*
static std::unordered_map<GLFWwindow*, Window*> g_window_map;

Window::Window(int width, int height, const std::string& title,
               int gl_major, int gl_minor,
               bool vsync, bool y_up)
    : width_(width), height_(height), title_(title),
      gl_major_(gl_major), gl_minor_(gl_minor),
      vsync_(vsync), y_up_(y_up)
{
    init_glfw();
    init_imgui();
    g_window_map[window_] = this;
}

Window::~Window() {
    cleanup();
}

Window::Window(Window&& other) noexcept {
    *this = std::move(other);
}

Window& Window::operator=(Window&& other) noexcept {
    if (this != &other) {
        cleanup();
        window_ = other.window_;
        width_ = other.width_;
        height_ = other.height_;
        title_ = std::move(other.title_);
        gl_major_ = other.gl_major_;
        gl_minor_ = other.gl_minor_;
        vsync_ = other.vsync_;
        y_up_ = other.y_up_;
        events_fn_ = std::move(other.events_fn_);
        process_fn_ = std::move(other.process_fn_);
        render_fn_ = std::move(other.render_fn_);
        render_ui_fn_ = std::move(other.render_ui_fn_);
        g_window_map[window_] = this;

        other.window_ = nullptr;
    }
    return *this;
}

void Window::init_glfw() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major_);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor_);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
    if (!window_) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(vsync_ ? 1 : 0);

    if (!gladLoadGL(glfwGetProcAddress)) {
        glfwDestroyWindow(window_);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    glfwSetKeyCallback(window_, key_callback);
    glfwSetMouseButtonCallback(window_, mouse_button_callback);
    glfwSetScrollCallback(window_, scroll_callback);
    glfwSetCursorPosCallback(window_, cursor_position_callback);
}

void Window::init_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (!ImGui_ImplGlfw_InitForOpenGL(window_, true))
        throw std::runtime_error("Failed to init ImGui GLFW backend");
    if (!ImGui_ImplOpenGL3_Init("#version 330"))
        throw std::runtime_error("Failed to init ImGui OpenGL backend");
}

void Window::cleanup() {
    if (window_) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window_);
        g_window_map.erase(window_);
        window_ = nullptr;

        if (g_window_map.empty()) {
            glfwTerminate();
        }
    }
}

void Window::run() {
    while (!glfwWindowShouldClose(window_)) {
        if (events_fn_) events_fn_();
        if (process_fn_) process_fn_();
        if (render_fn_) render_fn_();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (render_ui_fn_) render_ui_fn_();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);

        // reset input state
        keyboard.key = -1;
        keyboard.scancode = -1;
        keyboard.action = -1;
        keyboard.mods = 0;
        mouse.button = -1;
        mouse.action = -1;
        mouse.mods = 0;
        mouse.xoffset = 0.0;
        mouse.yoffset = 0.0;

        glfwPollEvents();
    }
}

std::pair<int,int> Window::get_size() const {
    int w, h;
    glfwGetWindowSize(window_, &w, &h);
    return {w, h};
}

void Window::set_size(int width, int height) {
    width_ = width;
    height_ = height;
    if (window_) {
        glfwSetWindowSize(window_, width, height);
    }
}

void Window::set_title(const std::string& title) {
    title_ = title;
    if (window_) {
        glfwSetWindowTitle(window_, title_.c_str());
    }
}

void Window::set_vsync(bool enabled) {
    vsync_ = enabled;
    if (window_) {
        glfwSwapInterval(vsync_ ? 1 : 0);
    }
}

void Window::set_y_up(bool y_up) {
    y_up_ = y_up;
}

// --- Static callbacks ---
void Window::framebuffer_size_callback(GLFWwindow* win, int w, int h) {
    auto* self = g_window_map[win];
    if (self) {
        self->width_ = w;
        self->height_ = h;
    }
    glViewport(0, 0, w, h);
}

void Window::key_callback(GLFWwindow*, int key, int scancode, int action, int mods) {
    keyboard.set(key, scancode, action, mods);
}

void Window::mouse_button_callback(GLFWwindow*, int button, int action, int mods) {
    mouse.set(button, action, mods);
}

void Window::scroll_callback(GLFWwindow*, double xoffset, double yoffset) {
    mouse.set_scroll(xoffset, yoffset);
}

void Window::cursor_position_callback(GLFWwindow* win, double xpos, double ypos) {
    auto* self = g_window_map[win];
    if (self && self->y_up_) {
        cursor.set(xpos, self->height_ - ypos - 1);
    } else {
        cursor.set(xpos, ypos);
    }
}

bool Window::should_close() const {
    return glfwWindowShouldClose(window_);
}

void Window::close() {
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

std::pair<int,int> Window::get_framebuffer_size() const {
    int w, h;
    glfwGetFramebufferSize(window_, &w, &h);
    return {w, h};
}

std::pair<int,int> Window::get_position() const {
    int x, y;
    glfwGetWindowPos(window_, &x, &y);
    return {x, y};
}

void Window::set_position(int x, int y) {
    if (window_) {
        glfwSetWindowPos(window_, x, y);
    }
}

GLFWwindow* Window::get_glfw_window() const {
    return window_;
}

int py_get_key(const Window &w, int key) {
    return glfwGetKey(w.get_glfw_window(), key);
}

void Window::set_fullscreen(bool enabled) {
    if (fullscreen_ == enabled || !window_) return;

    fullscreen_ = enabled;
    if (fullscreen_) {
        monitor_ = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor_);
        glfwSetWindowMonitor(window_, monitor_, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        monitor_ = nullptr;
        glfwSetWindowMonitor(window_, nullptr, 100, 100, width_, height_, 0);
    }
}

void Window::set_cursor_visible(bool visible) {
    if (window_) {
        glfwSetInputMode(window_, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
    }
}

void Window::set_cursor_mode(CursorMode mode) {
    if (!window_) return;
    switch (mode) {
        case CursorMode::Normal:
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case CursorMode::Hidden:
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            break;
        case CursorMode::Disabled:
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
    }
}

void Window::set_icon(int width, int height, const unsigned char* pixels) {
    if (!window_ || !pixels) return;

    GLFWimage img;
    img.width = width;
    img.height = height;
    img.pixels = const_cast<unsigned char*>(pixels);  // GLFW expects non-const

    glfwSetWindowIcon(window_, 1, &img);
}

std::vector<unsigned char> Window::screenshot(bool flip_vertically) const {
    if (!window_) return {};

    int fb_width, fb_height;
    glfwGetFramebufferSize(window_, &fb_width, &fb_height);

    std::vector<unsigned char> pixels(fb_width * fb_height * 4);
    glReadPixels(0, 0, fb_width, fb_height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    if (flip_vertically) {
        // Flip the image vertically
        int row_bytes = fb_width * 4;
        std::vector<unsigned char> tmp_row(row_bytes);
        for (int y = 0; y < fb_height / 2; ++y) {
            unsigned char* row_top = pixels.data() + y * row_bytes;
            unsigned char* row_bottom = pixels.data() + (fb_height - 1 - y) * row_bytes;
            std::memcpy(tmp_row.data(), row_top, row_bytes);
            std::memcpy(row_top, row_bottom, row_bytes);
            std::memcpy(row_bottom, tmp_row.data(), row_bytes);
        }
    }

    return pixels;
}

void bind_window(py::module_ &m) {
    m.def("get_key", &py_get_key, py::arg("window"), py::arg("key"));
    py::class_<Window>(m, "Window")
        .def(py::init<int,int,const std::string&,int,int,bool,bool>(),
             py::arg("width")=800,
             py::arg("height")=600,
             py::arg("title")="GLUX",
             py::arg("gl_major")=3,
             py::arg("gl_minor")=3,
             py::arg("vsync")=true,
             py::arg("y_up")=true)

        .def("run", &Window::run)

        // Window state
        .def("get_size", &Window::get_size)
        .def("get_framebuffer_size", &Window::get_framebuffer_size)
        .def("get_position", &Window::get_position)
        .def("get_title", &Window::get_title)
        .def("is_y_up", &Window::is_y_up)
        .def("is_vsync", &Window::is_vsync)
        .def("is_fullscreen", &Window::is_fullscreen)
        .def("should_close", &Window::should_close)
        .def("screenshot", [](Window &w, bool flip_vertically) {
            auto vec = w.screenshot(flip_vertically);
            return py::bytes(reinterpret_cast<const char*>(vec.data()), vec.size());
        }, py::arg("flip_vertically")=true)

        // Mutators
        .def("set_size", &Window::set_size)
        .def("set_title", &Window::set_title)
        .def("set_vsync", &Window::set_vsync)
        .def("set_y_up", &Window::set_y_up)
        .def("set_position", &Window::set_position)
        .def("set_fullscreen", &Window::set_fullscreen)
        .def("set_icon", [](Window &w, py::bytes data, int width, int height) {
                std::string s = data;  // convert bytes to string buffer
                w.set_icon(width, height, reinterpret_cast<const unsigned char*>(s.data()));
            }, py::arg("data"), py::arg("width"), py::arg("height"))
        .def("close", &Window::close)

        // Cursor
        .def("set_cursor_visible", &Window::set_cursor_visible)
        .def("set_cursor_mode", &Window::set_cursor_mode)

        // Callbacks
        .def("set_events_callback", &Window::set_events_callback)
        .def("set_process_callback", &Window::set_process_callback)
        .def("set_render_callback", &Window::set_render_callback)
        .def("set_render_ui_callback", &Window::set_render_ui_callback);

    // Proper enum binding
    py::enum_<Window::CursorMode>(m, "CursorMode")
        .value("Normal", Window::CursorMode::Normal)
        .value("Hidden", Window::CursorMode::Hidden)
        .value("Disabled", Window::CursorMode::Disabled);
}
