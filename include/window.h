#pragma once

#include <string>
#include <functional>
#include <utility>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

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

    void run();

    std::pair<int,int> get_size() const;
    std::pair<int,int> get_framebuffer_size() const;
    std::pair<int,int> get_position() const;
    GLFWwindow* get_glfw_window() const { return window_; }

    const std::string& get_title() const { return title_; }
    bool is_y_up() const { return y_up_; }
    bool is_vsync() const { return vsync_; }
    bool is_fullscreen() const { return fullscreen_; }
    bool should_close() const;

    void set_size(int width, int height);
    void set_title(const std::string& title);
    void set_vsync(bool enabled);
    void set_y_up(bool y_up);
    void set_position(int x, int y);
    void set_fullscreen(bool enabled);
    void set_opacity(float alpha);
    void set_resizable(bool);
    void set_decorated(bool);
    void set_floating(bool);
    void set_icon(int width, int height, const unsigned char* pixels);
    void close();

    std::vector<unsigned char> screenshot() const;

    enum class CursorMode { Normal, Hidden, Disabled };
    void set_cursor_visible(bool visible);
    void set_cursor_mode(CursorMode mode);
    void set_cursor_position(float x, float y);

    void set_events_callback(Callback cb) { events_fn_ = std::move(cb); }
    void set_process_callback(Callback cb) { process_fn_ = std::move(cb); }
    void set_render_callback(Callback cb) { render_fn_ = std::move(cb); }
    void set_render_ui_callback(Callback cb) { render_ui_fn_ = std::move(cb); }

private:
    GLFWwindow* window_ = nullptr;
    GLFWmonitor* monitor_ = nullptr;
    int width_ = 0, height_ = 0;
    std::string title_;
    int gl_major_ = 3, gl_minor_ = 3;
    bool vsync_ = true;
    bool y_up_ = true;
    bool fullscreen_ = false;

    Callback events_fn_;
    Callback process_fn_;
    Callback render_fn_;
    Callback render_ui_fn_;

    void init_glfw();
    void init_imgui();
    void cleanup();

    static void framebuffer_size_callback(GLFWwindow* win, int w, int h);
    static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);
    static void cursor_position_callback(GLFWwindow* win, double xpos, double ypos);
    static void cursor_enter_callback(GLFWwindow* win, int entered);
};

extern Window* g_window;

namespace py = pybind11;

bool get_kstate(int key);
bool get_mstate(int button);

void bind_window(py::module_ &m);
