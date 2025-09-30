#pragma once

#include <string>
#include <functional>
#include <utility>
#include <iostream>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Window {
public:
    using Callback = std::function<void()>;

    Window(int width = 800,
           int height = 600,
           const std::string& title = "GLUX",
           int gl_major = 3,
           int gl_minor = 3,
           bool vsync = true,
           bool y_up = true);

    ~Window();

    // Non-copyable
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Movable
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

    void run();

    // --- Core Window State ---
    std::pair<int,int> get_size() const;
    std::pair<int,int> get_framebuffer_size() const;
    std::pair<int,int> get_position() const;

    const std::string& get_title() const { return title_; }
    bool is_y_up() const { return y_up_; }
    bool is_vsync() const { return vsync_; }
    bool is_fullscreen() const { return fullscreen_; }
    bool should_close() const;

    // --- Setters ---
    void set_size(int width, int height);
    void set_title(const std::string& title);
    void set_vsync(bool enabled);
    void set_y_up(bool y_up);
    void set_position(int x, int y);
    void set_fullscreen(bool enabled);
    void set_icon(int width, int height, const unsigned char* pixels);
    void close();

    // Screenshot of the current framebuffer
    // Returns a vector of RGBA8 bytes (width * height * 4)
    std::vector<unsigned char> screenshot(bool flip_vertically = true) const;

    // --- Cursor Control ---
    enum class CursorMode { Normal, Hidden, Disabled };
    void set_cursor_visible(bool visible);
    void set_cursor_mode(CursorMode mode);

    // --- User Callbacks ---
    void set_events_callback(Callback cb) { events_fn_ = std::move(cb); }
    void set_process_callback(Callback cb) { process_fn_ = std::move(cb); }
    void set_render_callback(Callback cb) { render_fn_ = std::move(cb); }
    void set_render_ui_callback(Callback cb) { render_ui_fn_ = std::move(cb); }

private:
    GLFWwindow* window_ = nullptr;
    GLFWmonitor* monitor_ = nullptr;
    int width_, height_;
    std::string title_;
    int gl_major_, gl_minor_;
    bool vsync_;
    bool y_up_;
    bool fullscreen_ = false;
    
    Callback events_fn_;
    Callback process_fn_;
    Callback render_fn_;
    Callback render_ui_fn_;
    
    void init_glfw();
    void init_imgui();
    void cleanup();
    GLFWwindow* get_glfw_window() const;
    friend int py_get_key(const Window&, int);
    
    // Static callbacks that forward to this instance
    static void framebuffer_size_callback(GLFWwindow* win, int w, int h);
    static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);
    static void cursor_position_callback(GLFWwindow* win, double xpos, double ypos);
};

namespace py = pybind11;

void bind_window(py::module_ &m);