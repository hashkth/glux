
#include "imgui_bindings.h"

#include <array>
#include <vector>
#include <string>
#include <tuple>
#include <cstring>
#include <algorithm>

// ----------------------
// Helper utilities
// ----------------------

// Wrap scalar inputs (bool, int, float) that pass a pointer to ImGui and return (changed, value).
template <typename T, typename F>
static inline auto wrap_scalar_input(const std::string& label, T value, F&& func) {
    T v = value;
    bool changed = func(label.c_str(), &v);
    return std::make_tuple(changed, v);
}

// Wrap N-element numeric array inputs (e.g., DragFloat3, DragInt2) and return (changed, array)
template <typename T, size_t N, typename F>
static inline auto wrap_array_input(const std::string& label, const std::array<T, N>& value, F&& func) {
    T v[N];
    for (size_t i = 0; i < N; ++i) v[i] = value[i];
    bool changed = func(label.c_str(), v);
    std::array<T, N> out{};
    for (size_t i = 0; i < N; ++i) out[i] = v[i];
    return std::make_tuple(changed, out);
}

// Convert ImVec4 -> float[3] (drop alpha), and float[3] -> ImVec4 (preserve old alpha)
static inline void vec4_to_float3(const ImVec4& c, float out[3]) {
    out[0] = c.x; out[1] = c.y; out[2] = c.z;
}
static inline ImVec4 float3_to_vec4(const float in[3], float alpha) {
    return ImVec4(in[0], in[1], in[2], alpha);
}

// Convert ImVec4 <-> float[4]
static inline void vec4_to_float4(const ImVec4& c, float out[4]) {
    out[0] = c.x; out[1] = c.y; out[2] = c.z; out[3] = c.w;
}
static inline ImVec4 float4_to_vec4(const float in[4]) {
    return ImVec4(in[0], in[1], in[2], in[3]);
}

// InputText helper used by both single-line and multiline variants.
// Keeps the same behavior as your original (heap string with resize callback).
struct InputTextUserData { std::string* str; };

static int input_text_resize_callback(ImGuiInputTextCallbackData* data) {
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
        auto* user = reinterpret_cast<InputTextUserData*>(data->UserData);
        user->str->resize(static_cast<size_t>(data->BufTextLen) + 1);
        data->Buf = user->str->data();
    }
    return 0;
}

static inline auto do_input_text_single(const std::string& label,
                                        const std::string& text,
                                        ImGuiInputTextFlags flags) {
    std::string buffer = text;
    buffer.resize(std::max<size_t>(buffer.size() + 32, 64));
    InputTextUserData user_data{ &buffer };
    bool changed = ImGui::InputText(
        label.c_str(),
        buffer.data(),
        buffer.size(),  // must be size(), not capacity() — ImGui writes up to (buf_size-1) bytes
        flags | ImGuiInputTextFlags_CallbackResize,
        input_text_resize_callback,
        &user_data
    );
    buffer.resize(std::strlen(buffer.c_str()));
    return std::make_tuple(changed, buffer);
}

static inline auto do_input_text_with_hint_single(const std::string& label,
                                        const std::string& hint,
                                        const std::string& text,
                                        ImGuiInputTextFlags flags) {
    std::string buffer = text;
    buffer.resize(std::max<size_t>(buffer.size() + 32, 64));
    InputTextUserData user_data{ &buffer };
    bool changed = ImGui::InputTextWithHint(
        label.c_str(),
        hint.c_str(),
        buffer.data(),
        buffer.size(),  // must be size(), not capacity()
        flags | ImGuiInputTextFlags_CallbackResize,
        input_text_resize_callback,
        &user_data
    );
    buffer.resize(std::strlen(buffer.c_str()));
    return std::make_tuple(changed, buffer);
}

static inline auto do_input_text_multiline(const std::string& label,
                                           const std::string& text,
                                           const ImVec2& size,
                                           ImGuiInputTextFlags flags) {
    std::string buffer = text;
    buffer.resize(std::max<size_t>(buffer.size() + 32, 64));
    InputTextUserData user_data{ &buffer };
    bool changed = ImGui::InputTextMultiline(
        label.c_str(),
        buffer.data(),
        buffer.size(),  // must be size(), not capacity()
        size,
        flags | ImGuiInputTextFlags_CallbackResize,
        input_text_resize_callback,
        &user_data
    );
    buffer.resize(std::strlen(buffer.c_str()));
    return std::make_tuple(changed, buffer);
}

void bind_imgui_funcs(py::module_& m) {
    // ----- Core windowing -----

    m.def("begin",
        [](const std::string& name, py::object p_open, ImGuiWindowFlags flags) {
            if (p_open.is_none()) {
                // No close button: pass nullptr, return only visible flag
                bool visible = ImGui::Begin(name.c_str(), nullptr, flags);
                return std::make_tuple(visible, py::object(py::none()));
            }
            bool open = p_open.cast<bool>();
            bool visible = ImGui::Begin(name.c_str(), &open, flags);
            return std::make_tuple(visible, py::object(py::bool_(open)));
        },
        py::arg("name"),
        py::arg("p_open") = py::none(),
        py::arg("flags") = ImGuiWindowFlags_None
    );

    m.def("end", &ImGui::End);

    // ----- Text -----
    m.def("text",
        [](const std::string& text) {
            ImGui::Text("%s", text.c_str());
        },
        py::arg("text")
    );

    m.def("text_colored",
        [](const ImVec4& color, const std::string& text) {
            ImGui::TextColored(color, "%s", text.c_str());
        },
        py::arg("color"), py::arg("text")
    );

    // ----- Styling -----
    m.def("push_style_color",
        [](ImGuiCol idx, const ImVec4& color) {
            ImGui::PushStyleColor(idx, color);
        },
        py::arg("idx"), py::arg("color")
    );

    m.def("push_style_var_float",
        [](ImGuiStyleVar idx, float val) {
            ImGui::PushStyleVar(idx, val);
        },
        py::arg("idx"), py::arg("value")
    );

    m.def("push_style_var_vec2",
        [](ImGuiStyleVar idx, const ImVec2& val) {
            ImGui::PushStyleVar(idx, val);
        },
        py::arg("idx"), py::arg("value")
    );

    m.def("pop_style_var", &ImGui::PopStyleVar, py::arg("count") = 1);
    m.def("pop_style_color", &ImGui::PopStyleColor, py::arg("count") = 1);
    m.def("push_item_width", &ImGui::PushItemWidth, py::arg("width"));
    m.def("pop_item_width", &ImGui::PopItemWidth);
    m.def("set_next_item_width", &ImGui::SetNextItemWidth, py::arg("width"));
    m.def("indent",   &ImGui::Indent,   py::arg("indent_w") = 0.0f);
    m.def("unindent", &ImGui::Unindent, py::arg("indent_w") = 0.0f);
    m.def("begin_group", &ImGui::BeginGroup);
    m.def("end_group", &ImGui::EndGroup);    

    // ----- Layout / Spacing -----
    m.def("same_line", &ImGui::SameLine,
        py::arg("offset_from_start_x") = 0.0f,
        py::arg("spacing") = -1.0f
    );

    m.def("dummy", [](ImVec2 size) { ImGui::Dummy(size); },
        py::arg("size")
    );

    m.def("separator", &ImGui::Separator);
    m.def("spacing", &ImGui::Spacing);

    // ----- Next window setup -----
    m.def("set_next_window_pos", &ImGui::SetNextWindowPos,
        py::arg("pos"),
        py::arg("cond") = ImGuiCond_None,
        py::arg("pivot") = ImVec2(0.0f, 0.0f)
    );

    m.def("set_next_window_size", &ImGui::SetNextWindowSize,
        py::arg("size"),
        py::arg("cond") = ImGuiCond_None
    );

    m.def("set_next_window_size_constraints",
        [](const ImVec2& min, const ImVec2& max) {
            ImGui::SetNextWindowSizeConstraints(min, max, nullptr, nullptr);
        },
        py::arg("size_min"), py::arg("size_max")
    );

    m.def("set_next_window_content_size", &ImGui::SetNextWindowContentSize,
        py::arg("size")
    );

    m.def("set_next_window_collapsed", &ImGui::SetNextWindowCollapsed,
        py::arg("collapsed"),
        py::arg("cond") = ImGuiCond_None
    );

    m.def("set_next_window_focus", &ImGui::SetNextWindowFocus);

    // ----- Cursor / Item focus -----
    m.def("set_cursor_pos", &ImGui::SetCursorPos, py::arg("local_pos"));
    m.def("set_cursor_screen_pos", &ImGui::SetCursorScreenPos, py::arg("screen_pos"));
    m.def("set_item_default_focus", &ImGui::SetItemDefaultFocus);

    // ----- Basic widgets -----
    m.def("button",
        [](const std::string& label, const ImVec2& size) {
            return ImGui::Button(label.c_str(), size);
        },
        py::arg("label"), py::arg("size") = ImVec2(0.0f, 0.0f)
    );

    m.def("color_button",
        [](const std::string& desc_id, const ImVec4& color, ImGuiColorEditFlags flags, const ImVec2& size) {
            return ImGui::ColorButton(desc_id.c_str(), color, flags, size);
        },
        py::arg("desc_id"), py::arg("color"),
        py::arg("flags") = ImGuiColorEditFlags_None, py::arg("size") = ImVec2(0.0f, 0.0f)
    );

    m.def("small_button",
        [](const std::string& label) {
            return ImGui::SmallButton(label.c_str());
        },
        py::arg("label")
    );

    m.def("arrow_button",
        [](const std::string& str_id, ImGuiDir dir) {
            return ImGui::ArrowButton(str_id.c_str(), dir);
        },
        py::arg("str_id"), py::arg("dir")
    );

    m.def("invisible_button",
        [](const std::string& str_id, const ImVec2& size, ImGuiButtonFlags flags) {
            return ImGui::InvisibleButton(str_id.c_str(), size, flags);
        },
        py::arg("str_id"), py::arg("size"), py::arg("flags") = ImGuiButtonFlags_None
    );

    m.def("checkbox",
        [](const std::string& label, bool value) {
            return wrap_scalar_input<bool>(label, value,
                [](const char* l, bool* v) { return ImGui::Checkbox(l, v); });
        },
        py::arg("label"), py::arg("value")
    );

    m.def("radio_button",
        [](const std::string& label, int current_value, int button_value) {
            bool changed = ImGui::RadioButton(label.c_str(), current_value == button_value);
            if (changed) return std::make_tuple(true, button_value);
            return std::make_tuple(false, current_value);
        },
        py::arg("label"), py::arg("current_value"), py::arg("button_value")
    );

    // ----- Text inputs -----
    m.def("input_text",
        [](const std::string& label, const std::string& text, ImGuiInputTextFlags flags) {
            return do_input_text_single(label, text, flags);
        },
        py::arg("label"), py::arg("text"), py::arg("flags") = ImGuiInputTextFlags_None
    );

    m.def("input_text_with_hint",
        [](const std::string& label, std::string& hint, const std::string& text, ImGuiInputTextFlags flags) {
            return do_input_text_with_hint_single(label, hint, text, flags);
        },
        py::arg("label"), py::arg("hint"), py::arg("text"), py::arg("flags") = ImGuiInputTextFlags_None
    );

    m.def("input_text_multiline",
        [](const std::string& label, const std::string& text, const ImVec2& size, ImGuiInputTextFlags flags) {
            return do_input_text_multiline(label, text, size, flags);
        },
        py::arg("label"), py::arg("text"), py::arg("size") = ImVec2(0.0f, 0.0f),
        py::arg("flags") = ImGuiInputTextFlags_None
    );

    // ----- Numeric inputs -----
    m.def("input_float",
        [](const std::string& label, float value, float step, float step_fast,
           const std::string& format, ImGuiInputTextFlags flags) {
            return wrap_scalar_input<float>(label, value,
                [&](const char* l, float* v) {
                    return ImGui::InputFloat(l, v, step, step_fast, format.c_str(), flags);
                });
        },
        py::arg("label"), py::arg("value"),
        py::arg("step") = 0.0f, py::arg("step_fast") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("flags") = ImGuiInputTextFlags_None
    );

    m.def("input_int",
        [](const std::string& label, int value, int step, int step_fast,
           ImGuiInputTextFlags flags) {
            return wrap_scalar_input<int>(label, value,
                [&](const char* l, int* v) {
                    return ImGui::InputInt(l, v, step, step_fast, flags);
                });
        },
        py::arg("label"), py::arg("value"),
        py::arg("step") = 1, py::arg("step_fast") = 100,
        py::arg("flags") = ImGuiInputTextFlags_None
    );

    // ----- Sliders -----
    m.def("slider_float",
        [](const std::string& label, float value, float min, float max,
           const std::string& format, ImGuiSliderFlags flags) {
            return wrap_scalar_input<float>(label, value,
                [&](const char* l, float* v) {
                    return ImGui::SliderFloat(l, v, min, max, format.c_str(), flags);
                });
        },
        py::arg("label"), py::arg("value"), py::arg("min"), py::arg("max"),
        py::arg("format") = "%.3f",
        py::arg("flags") = ImGuiSliderFlags_None
    );

    m.def("slider_int",
        [](const std::string& label, int value, int min, int max,
           const std::string& format, ImGuiSliderFlags flags) {
            return wrap_scalar_input<int>(label, value,
                [&](const char* l, int* v) {
                    return ImGui::SliderInt(l, v, min, max, format.c_str(), flags);
                });
        },
        py::arg("label"), py::arg("value"), py::arg("min"), py::arg("max"),
        py::arg("format") = "%d",
        py::arg("flags") = ImGuiSliderFlags_None
    );

    // ----- Drag floats -----
    m.def("drag_float",
        [](const std::string& label, float value, float speed, float min, float max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_scalar_input<float>(label, value,
                [&](const char* l, float* v) { return ImGui::DragFloat(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f,
        py::arg("format") = "%.3f", py::arg("flags") = ImGuiSliderFlags_None
    );

    m.def("drag_float2",
        [](const std::string& label, const std::array<float, 2>& value, float speed, float min, float max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_array_input<float, 2>(label, value,
                [&](const char* l, float v[2]) { return ImGui::DragFloat2(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f,
        py::arg("format") = "%.3f", py::arg("flags") = ImGuiSliderFlags_None
    );

    m.def("drag_float3",
        [](const std::string& label, const std::array<float, 3>& value, float speed, float min, float max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_array_input<float, 3>(label, value,
                [&](const char* l, float v[3]) { return ImGui::DragFloat3(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f,
        py::arg("format") = "%.3f", py::arg("flags") = ImGuiSliderFlags_None
    );

    m.def("drag_float4",
        [](const std::string& label, const std::array<float, 4>& value, float speed, float min, float max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_array_input<float, 4>(label, value,
                [&](const char* l, float v[4]) { return ImGui::DragFloat4(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f,
        py::arg("format") = "%.3f", py::arg("flags") = ImGuiSliderFlags_None
    );

    // ----- Drag ints -----
    m.def("drag_int",
        [](const std::string& label, int value, float speed, int min, int max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_scalar_input<int>(label, value,
                [&](const char* l, int* v) { return ImGui::DragInt(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0,
        py::arg("format") = "%d", py::arg("flags") = ImGuiSliderFlags_None
    );

    m.def("drag_int2",
        [](const std::string& label, const std::array<int, 2>& value, float speed, int min, int max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_array_input<int, 2>(label, value,
                [&](const char* l, int v[2]) { return ImGui::DragInt2(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0,
        py::arg("format") = "%d", py::arg("flags") = ImGuiSliderFlags_None
    );

    m.def("drag_int3",
        [](const std::string& label, const std::array<int, 3>& value, float speed, int min, int max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_array_input<int, 3>(label, value,
                [&](const char* l, int v[3]) { return ImGui::DragInt3(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0,
        py::arg("format") = "%d", py::arg("flags") = ImGuiSliderFlags_None
    );

    m.def("drag_int4",
        [](const std::string& label, const std::array<int, 4>& value, float speed, int min, int max, const std::string& format, ImGuiSliderFlags flags) {
            return wrap_array_input<int, 4>(label, value,
                [&](const char* l, int v[4]) { return ImGui::DragInt4(l, v, speed, min, max, format.c_str(), flags); });
        },
        py::arg("label"), py::arg("value"),
        py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0,
        py::arg("format") = "%d", py::arg("flags") = ImGuiSliderFlags_None
    );

    // ----- Combo -----
    m.def("combo",
        [](const std::string& label, int current_item, const std::vector<std::string>& items) {
            std::vector<const char*> c_items;
            c_items.reserve(items.size());
            for (const auto& s : items) c_items.push_back(s.c_str());
            int v = current_item;
            bool changed = ImGui::Combo(label.c_str(), &v, c_items.data(), static_cast<int>(c_items.size()));
            return std::make_tuple(changed, v);
        },
        py::arg("label"), py::arg("current_item"), py::arg("items")
    );

    // ----- Colors -----
    m.def("color_edit3",
        [](const std::string& label, const ImVec4& color, ImGuiColorEditFlags flags) {
            float col[3]; vec4_to_float3(color, col);
            bool changed = ImGui::ColorEdit3(label.c_str(), col, flags);
            ImVec4 out = float3_to_vec4(col, color.w); // preserve original alpha
            return std::make_tuple(changed, out);
        },
        py::arg("label"), py::arg("color"),
        py::arg("flags") = ImGuiColorEditFlags_None
    );

    m.def("color_edit4",
        [](const std::string& label, const ImVec4& color, ImGuiColorEditFlags flags) {
            float col[4]; vec4_to_float4(color, col);
            bool changed = ImGui::ColorEdit4(label.c_str(), col, flags);
            ImVec4 out = float4_to_vec4(col);
            return std::make_tuple(changed, out);
        },
        py::arg("label"), py::arg("color"), py::arg("flags") = ImGuiColorEditFlags_None
    );

    m.def("color_picker3",
        [](const std::string& label, const ImVec4& color, ImGuiColorEditFlags flags) {
            float col[3]; vec4_to_float3(color, col);
            bool changed = ImGui::ColorPicker3(label.c_str(), col, flags);
            ImVec4 out = float3_to_vec4(col, color.w);
            return std::make_tuple(changed, out);
        },
        py::arg("label"), py::arg("color"), py::arg("flags") = ImGuiColorEditFlags_None
    );

    m.def("color_picker4",
        [](const std::string& label, const ImVec4& color, ImGuiColorEditFlags flags) {
            float col[4]; vec4_to_float4(color, col);
            bool changed = ImGui::ColorPicker4(label.c_str(), col, flags);
            ImVec4 out = float4_to_vec4(col);
            return std::make_tuple(changed, out);
        },
        py::arg("label"), py::arg("color"), py::arg("flags") = ImGuiColorEditFlags_None
    );

    // ----- Drawing / Viewport -----
    // NOTE: These return raw pointers tied to the current ImGui context. Python must not outlive the context.
    m.def("get_window_draw_list", &ImGui::GetWindowDrawList, py::return_value_policy::reference);
    m.def("get_background_draw_list", &ImGui::GetBackgroundDrawList, py::return_value_policy::reference);
    m.def("get_foreground_draw_list", &ImGui::GetForegroundDrawList, py::return_value_policy::reference);

    m.def("get_main_viewport",
        []() -> ImGuiViewport* { return ImGui::GetMainViewport(); },
        py::return_value_policy::reference
    );

    m.def("image",
        [](ImTextureID texture_id, const ImVec2& image_size,
           const ImVec2& uv0, const ImVec2& uv1,
           const ImVec4& tint_col, const ImVec4& border_col) {
            ImGui::Image(texture_id, image_size, uv0, uv1, tint_col, border_col);
        },
        py::arg("texture_id"), py::arg("image_size"),
        py::arg("uv0")        = ImVec2(0.0f, 0.0f),
        py::arg("uv1")        = ImVec2(1.0f, 1.0f),
        py::arg("tint_col")   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
        py::arg("border_col") = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
    );

    m.def("calc_text_size",
        [](const std::string& text) {
            ImVec2 size = ImGui::CalcTextSize(text.c_str());
            return std::make_tuple(size.x, size.y);
        }
    );

    m.def("get_available_region",
        []() {
            ImVec2 size = ImGui::GetContentRegionAvail();
            return std::make_tuple(size.x, size.y);
        }
    );

    // ----- Fonts / Glyph ranges -----
    // Glyph range helpers: route through the current context's font atlas so they
    // work as zero-argument free functions from Python.  The returned ImWchar*
    // pointer is owned by the atlas and remains valid for the lifetime of the context.
    m.def("get_glyph_ranges_default",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesDefault(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_greek",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesGreek(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_korean",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesKorean(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_japanese",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesJapanese(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_chinese_full",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesChineseFull(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_chinese_simplified_common",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_cyrillic",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesCyrillic(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_thai",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesThai(); },
        py::return_value_policy::reference);
    m.def("get_glyph_ranges_vietnamese",
        []() { return ImGui::GetIO().Fonts->GetGlyphRangesVietnamese(); },
        py::return_value_policy::reference);

    m.def("push_font",
        [](ImFont* font) { ImGui::PushFont(font); },
        py::arg("font")
    );
    m.def("pop_font", &ImGui::PopFont);

    // ----- Tables -----
    m.def("begin_table",
        [](const std::string& str_id, int column_count, ImGuiTableFlags flags,
           const ImVec2& outer_size, float inner_width) {
            return ImGui::BeginTable(str_id.c_str(), column_count, flags, outer_size, inner_width);
        },
        py::arg("str_id"), py::arg("column_count"),
        py::arg("flags") = ImGuiTableFlags_None,
        py::arg("outer_size") = ImVec2(0.0f, 0.0f),
        py::arg("inner_width") = 0.0f
    );

    m.def("end_table", &ImGui::EndTable);

    m.def("table_next_row", &ImGui::TableNextRow,
        py::arg("row_flags") = ImGuiTableRowFlags_None,
        py::arg("min_row_height") = 0.0f
    );

    m.def("table_next_column", &ImGui::TableNextColumn);

    m.def("table_set_column_index", &ImGui::TableSetColumnIndex,
        py::arg("column_n")
    );

    m.def("table_setup_column",
        [](const std::string& label, ImGuiTableColumnFlags flags,
           float init_width_or_weight, ImGuiID user_id) {
            ImGui::TableSetupColumn(label.c_str(), flags, init_width_or_weight, user_id);
        },
        py::arg("label"),
        py::arg("flags") = ImGuiTableColumnFlags_None,
        py::arg("init_width_or_weight") = 0.0f,
        py::arg("user_id") = 0
    );

    m.def("table_setup_scroll_freeze", &ImGui::TableSetupScrollFreeze,
        py::arg("cols"), py::arg("rows")
    );

    m.def("table_headers_row", &ImGui::TableHeadersRow);

    m.def("table_header",
        [](const std::string& label) { ImGui::TableHeader(label.c_str()); },
        py::arg("label")
    );

    m.def("table_get_sort_specs",
        []() {
            ImGuiTableSortSpecs* specs = ImGui::TableGetSortSpecs();
            if (!specs || specs->SpecsCount == 0)
                return std::vector<std::tuple<int,int,int>>{};

            std::vector<std::tuple<int,int,int>> out;
            out.reserve(specs->SpecsCount);
            for (int i = 0; i < specs->SpecsCount; i++) {
                const ImGuiTableColumnSortSpecs& s = specs->Specs[i];
                out.emplace_back(s.ColumnIndex, s.SortOrder, static_cast<int>(s.SortDirection));
            }
            // Must clear the dirty flag after reading; otherwise ImGui re-sorts every frame.
            specs->SpecsDirty = false;
            return out;
        },
        "Return current table sort specs as a list of (column_index, sort_order, sort_direction) tuples, "
        "then clear the dirty flag.  Only call when TableGetSortSpecs() is non-null."
    );

    m.def("table_get_column_count", &ImGui::TableGetColumnCount);
    m.def("table_get_column_index", &ImGui::TableGetColumnIndex);
    m.def("table_get_row_index", &ImGui::TableGetRowIndex);
    m.def("table_get_column_flags", &ImGui::TableGetColumnFlags,
        py::arg("column_n") = -1
    );

    m.def("table_set_column_enabled", &ImGui::TableSetColumnEnabled,
        py::arg("column_n"), py::arg("enabled")
    );

    m.def("table_set_bg_color", &ImGui::TableSetBgColor,
        py::arg("target"), py::arg("color"), py::arg("column_n") = -1
    );

    // ----- Tree / Collapsing Headers -----
    m.def("tree_node",
        [](const std::string& label) {
            return ImGui::TreeNode(label.c_str());
        },
        py::arg("label")
    );

    m.def("tree_node_ex",
        [](const std::string& label, ImGuiTreeNodeFlags flags) {
            return ImGui::TreeNodeEx(label.c_str(), flags);
        },
        py::arg("label"), py::arg("flags") = ImGuiTreeNodeFlags_None
    );

    m.def("tree_pop", &ImGui::TreePop);

    m.def("collapsing_header",
        [](const std::string& label, ImGuiTreeNodeFlags flags) {
            return ImGui::CollapsingHeader(label.c_str(), flags);
        },
        py::arg("label"), py::arg("flags") = ImGuiTreeNodeFlags_None
    );

    m.def("set_next_item_open", &ImGui::SetNextItemOpen,
        py::arg("is_open"), py::arg("cond") = ImGuiCond_None
    );

    m.def("tree_push",
        [](const std::string& str_id) {
            ImGui::TreePush(str_id.c_str());
        },
        py::arg("str_id")
    );

    m.def("get_tree_node_to_label_spacing", &ImGui::GetTreeNodeToLabelSpacing);

    // ----- Menus & Popups -----
    m.def("begin_menu_bar", &ImGui::BeginMenuBar);
    m.def("end_menu_bar", &ImGui::EndMenuBar);

    m.def("begin_main_menu_bar", &ImGui::BeginMainMenuBar);
    m.def("end_main_menu_bar", &ImGui::EndMainMenuBar);

    m.def("begin_menu",
        [](const std::string& label, bool enabled) {
            return ImGui::BeginMenu(label.c_str(), enabled);
        },
        py::arg("label"), py::arg("enabled") = true
    );

    m.def("end_menu", &ImGui::EndMenu);

    m.def("menu_item",
        [](const std::string& label, const std::string& shortcut, bool selected, bool enabled) {
            return ImGui::MenuItem(label.c_str(),
                                   shortcut.empty() ? nullptr : shortcut.c_str(),
                                   selected, enabled);
        },
        py::arg("label"), py::arg("shortcut") = "",
        py::arg("selected") = false, py::arg("enabled") = true
    );

    // Popups
    m.def("open_popup",
        [](const std::string& str_id, ImGuiPopupFlags flags) {
            ImGui::OpenPopup(str_id.c_str(), flags);
        },
        py::arg("str_id"), py::arg("flags") = ImGuiPopupFlags_None
    );

    m.def("begin_popup",
        [](const std::string& str_id, ImGuiWindowFlags flags) {
            return ImGui::BeginPopup(str_id.c_str(), flags);
        },
        py::arg("str_id"), py::arg("flags") = ImGuiWindowFlags_None
    );

    m.def("begin_popup_modal",
        [](const std::string& name, py::object p_open, ImGuiWindowFlags flags) {
            if (p_open.is_none()) {
                bool visible = ImGui::BeginPopupModal(name.c_str(), nullptr, flags);
                return std::make_tuple(visible, py::object(py::none()));
            }
            bool open = p_open.cast<bool>();
            bool visible = ImGui::BeginPopupModal(name.c_str(), &open, flags);
            return std::make_tuple(visible, py::object(py::bool_(open)));
        },
        py::arg("name"),
        py::arg("p_open") = py::none(),
        py::arg("flags") = ImGuiWindowFlags_None
    );

    m.def("end_popup", &ImGui::EndPopup);

    m.def("begin_popup_context_item",
        [](const std::string& str_id, ImGuiPopupFlags flags) {
            return ImGui::BeginPopupContextItem(str_id.empty() ? nullptr : str_id.c_str(), flags);
        },
        py::arg("str_id") = "", py::arg("flags") = ImGuiPopupFlags_MouseButtonRight
    );

    m.def("begin_popup_context_window",
        [](const std::string& str_id, ImGuiPopupFlags flags) {
            return ImGui::BeginPopupContextWindow(str_id.empty() ? nullptr : str_id.c_str(), flags);
        },
        py::arg("str_id") = "", py::arg("flags") = ImGuiPopupFlags_MouseButtonRight
    );

    m.def("begin_popup_context_void",
        [](const std::string& str_id, ImGuiPopupFlags flags) {
            return ImGui::BeginPopupContextVoid(str_id.empty() ? nullptr : str_id.c_str(), flags);
        },
        py::arg("str_id") = "", py::arg("flags") = ImGuiPopupFlags_MouseButtonRight
    );

    m.def("is_popup_open",
        [](const std::string& str_id, ImGuiPopupFlags flags) {
            return ImGui::IsPopupOpen(str_id.c_str(), flags);
        },
        py::arg("str_id"), py::arg("flags") = ImGuiPopupFlags_None
    );

    // Selectables (often used inside popups and menus)
    m.def("selectable",
        [](const std::string& label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size) {
            return ImGui::Selectable(label.c_str(), selected, flags, size);
        },
        py::arg("label"), py::arg("selected") = false,
        py::arg("flags") = ImGuiSelectableFlags_None,
        py::arg("size") = ImVec2(0.0f, 0.0f)
    );

    // ----- Input / State Queries -----

    // Item queries
    m.def("is_item_hovered", &ImGui::IsItemHovered,
        py::arg("flags") = ImGuiHoveredFlags_None
    );
    m.def("is_item_active", &ImGui::IsItemActive);
    m.def("is_item_focused", &ImGui::IsItemFocused);
    m.def("is_item_clicked",
        [](ImGuiMouseButton mouse_button) { return ImGui::IsItemClicked(mouse_button); },
        py::arg("mouse_button") = ImGuiMouseButton_Left
    );
    m.def("is_item_visible", &ImGui::IsItemVisible);
    m.def("is_item_edited", &ImGui::IsItemEdited);
    m.def("is_item_activated", &ImGui::IsItemActivated);
    m.def("is_item_deactivated", &ImGui::IsItemDeactivated);
    m.def("is_item_deactivated_after_edit", &ImGui::IsItemDeactivatedAfterEdit);
    m.def("is_item_toggled_open", &ImGui::IsItemToggledOpen);
    m.def("get_item_rect_min",
        []() { ImVec2 v = ImGui::GetItemRectMin(); return std::make_tuple(v.x, v.y); }
    );
    m.def("get_item_rect_max",
        []() { ImVec2 v = ImGui::GetItemRectMax(); return std::make_tuple(v.x, v.y); }
    );
    m.def("get_item_rect_size",
        []() { ImVec2 v = ImGui::GetItemRectSize(); return std::make_tuple(v.x, v.y); }
    );

    // Window queries
    m.def("is_window_focused",
        &ImGui::IsWindowFocused, py::arg("flags") = ImGuiFocusedFlags_None
    );
    m.def("is_window_hovered",
        &ImGui::IsWindowHovered, py::arg("flags") = ImGuiHoveredFlags_None
    );

    // Mouse
    m.def("is_mouse_down",
        [](ImGuiMouseButton button) { return ImGui::IsMouseDown(button); },
        py::arg("button") = ImGuiMouseButton_Left
    );
    m.def("is_mouse_clicked",
        [](ImGuiMouseButton button, bool repeat) { return ImGui::IsMouseClicked(button, repeat); },
        py::arg("button") = ImGuiMouseButton_Left, py::arg("repeat") = false
    );
    m.def("is_mouse_released",
        [](ImGuiMouseButton button) { return ImGui::IsMouseReleased(button); },
        py::arg("button") = ImGuiMouseButton_Left
    );
    m.def("is_mouse_double_clicked",
        [](ImGuiMouseButton button) { return ImGui::IsMouseDoubleClicked(button); },
        py::arg("button") = ImGuiMouseButton_Left
    );
    m.def("get_mouse_pos",
        []() { ImVec2 v = ImGui::GetMousePos(); return std::make_tuple(v.x, v.y); }
    );
    // Older versions: MouseDelta is in IO, not ImGui::GetMouseDelta
    m.def("get_mouse_delta",
        []() {
            ImVec2 v = ImGui::GetIO().MouseDelta;
            return std::make_tuple(v.x, v.y);
        }
    );
    m.def("get_mouse_drag_delta",
        [](ImGuiMouseButton button, float lock_threshold) {
            ImVec2 v = ImGui::GetMouseDragDelta(button, lock_threshold);
            return std::make_tuple(v.x, v.y);
        },
        py::arg("button") = ImGuiMouseButton_Left, py::arg("lock_threshold") = -1.0f
    );
    m.def("reset_mouse_drag_delta",
        [](ImGuiMouseButton button) { ImGui::ResetMouseDragDelta(button); },
        py::arg("button") = ImGuiMouseButton_Left
    );
    m.def("is_mouse_hovering_rect",
        [](const ImVec2& min, const ImVec2& max, bool clip) {
            return ImGui::IsMouseHoveringRect(min, max, clip);
        },
        py::arg("min"), py::arg("max"), py::arg("clip") = true
    );
    m.def("is_mouse_pos_valid",
        [](py::object pos) {
            if (pos.is_none())
                return ImGui::IsMousePosValid(nullptr);
            auto t = pos.cast<std::tuple<float,float>>();
            ImVec2 v(std::get<0>(t), std::get<1>(t));
            return ImGui::IsMousePosValid(&v);
        },
        py::arg("pos") = py::none()
    );

    // Keyboard (use ImGuiKey with explicit cast)
    m.def("is_key_down",
        [](int key) { return ImGui::IsKeyDown(static_cast<ImGuiKey>(key)); },
        py::arg("key")
    );
    m.def("is_key_pressed",
        [](int key, bool repeat) { return ImGui::IsKeyPressed(static_cast<ImGuiKey>(key), repeat); },
        py::arg("key"), py::arg("repeat") = true
    );
    m.def("is_key_released",
        [](int key) { return ImGui::IsKeyReleased(static_cast<ImGuiKey>(key)); },
        py::arg("key")
    );
    m.def("get_key_pressed_amount",
        [](int key, float repeat_delay, float rate) {
            return ImGui::GetKeyPressedAmount(static_cast<ImGuiKey>(key), repeat_delay, rate);
        },
        py::arg("key"), py::arg("repeat_delay"), py::arg("rate")
    );

    // Focus / Nav
    m.def("set_keyboard_focus_here",
        [](int offset) { ImGui::SetKeyboardFocusHere(offset); },
        py::arg("offset") = 0
    );


    // ----- Misc Utilities -----

    // Time & frame info
    m.def("get_time", &ImGui::GetTime);
    m.def("get_frame_count", &ImGui::GetFrameCount);

    // Frame dimensions
    m.def("get_frame_height", &ImGui::GetFrameHeight);
    m.def("get_frame_height_with_spacing", &ImGui::GetFrameHeightWithSpacing);

    // Display size
    m.def("get_display_size",
        []() {
            ImVec2 v = ImGui::GetIO().DisplaySize;
            return std::make_tuple(v.x, v.y);
        }
    );
    m.def("get_display_framebuffer_scale",
        []() {
            ImVec2 v = ImGui::GetIO().DisplayFramebufferScale;
            return std::make_tuple(v.x, v.y);
        }
    );

    // Cursor / line height
    m.def("get_cursor_pos",
        []() { ImVec2 v = ImGui::GetCursorPos(); return std::make_tuple(v.x, v.y); }
    );
    m.def("get_cursor_start_pos",
        []() { ImVec2 v = ImGui::GetCursorStartPos(); return std::make_tuple(v.x, v.y); }
    );
    m.def("get_cursor_screen_pos",
        []() { ImVec2 v = ImGui::GetCursorScreenPos(); return std::make_tuple(v.x, v.y); }
    );
    m.def("get_text_line_height", &ImGui::GetTextLineHeight);
    m.def("get_text_line_height_with_spacing", &ImGui::GetTextLineHeightWithSpacing);

    // Colors
    m.def("get_color_u32",
        [](const ImVec4& col) { return ImGui::GetColorU32(col); },
        py::arg("col")
    );
    m.def("get_color_u32_indexed",
        [](ImGuiCol idx, float alpha_mul) { return ImGui::GetColorU32(idx, alpha_mul); },
        py::arg("idx"), py::arg("alpha_mul") = 1.0f
    );

    // Fonts & style access
    m.def("get_font_size", &ImGui::GetFontSize);
    m.def("get_font_tex_uv_white_pixel",
        []() {
            ImVec2 v = ImGui::GetFontTexUvWhitePixel();
            return std::make_tuple(v.x, v.y);
        }
    );
    m.def("get_style", &ImGui::GetStyle, py::return_value_policy::reference);

    // Clipboard
    m.def("get_clipboard_text",
        []() {
            const char* text = ImGui::GetClipboardText();
            return text ? std::string(text) : std::string();
        }
    );
    m.def("set_clipboard_text",
        [](const std::string& text) { ImGui::SetClipboardText(text.c_str()); },
        py::arg("text")
    );



    // ----- Drawing API (ImDrawList) -----
    // Note: these functions operate on ImDrawList*, which you obtain from
    // get_window_draw_list(), get_foreground_draw_list(), or get_background_draw_list().

    m.def("drawlist_add_line",
        [](ImDrawList* dl, const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness) {
            dl->AddLine(p1, p2, col, thickness);
        },
        py::arg("drawlist"), py::arg("p1"), py::arg("p2"),
        py::arg("col"), py::arg("thickness") = 1.0f
    );

    m.def("drawlist_add_rect",
        [](ImDrawList* dl, const ImVec2& p_min, const ImVec2& p_max,
           ImU32 col, float rounding, ImDrawFlags flags, float thickness) {
            dl->AddRect(p_min, p_max, col, rounding, flags, thickness);
        },
        py::arg("drawlist"), py::arg("p_min"), py::arg("p_max"),
        py::arg("col"), py::arg("rounding") = 0.0f,
        py::arg("flags") = ImDrawFlags_None,
        py::arg("thickness") = 1.0f
    );

    m.def("drawlist_add_rect_filled",
        [](ImDrawList* dl, const ImVec2& p_min, const ImVec2& p_max,
           ImU32 col, float rounding, ImDrawFlags flags) {
            dl->AddRectFilled(p_min, p_max, col, rounding, flags);
        },
        py::arg("drawlist"), py::arg("p_min"), py::arg("p_max"),
        py::arg("col"), py::arg("rounding") = 0.0f,
        py::arg("flags") = ImDrawFlags_None
    );

    m.def("drawlist_add_circle",
        [](ImDrawList* dl, const ImVec2& center, float radius, ImU32 col,
           int num_segments, float thickness) {
            dl->AddCircle(center, radius, col, num_segments, thickness);
        },
        py::arg("drawlist"), py::arg("center"), py::arg("radius"),
        py::arg("col"), py::arg("num_segments") = 0,
        py::arg("thickness") = 1.0f
    );

    m.def("drawlist_add_circle_filled",
        [](ImDrawList* dl, const ImVec2& center, float radius, ImU32 col, int num_segments) {
            dl->AddCircleFilled(center, radius, col, num_segments);
        },
        py::arg("drawlist"), py::arg("center"), py::arg("radius"),
        py::arg("col"), py::arg("num_segments") = 0
    );

    m.def("drawlist_add_text",
        [](ImDrawList* dl, const ImVec2& pos, ImU32 col, const std::string& text) {
            dl->AddText(pos, col, text.c_str());
        },
        py::arg("drawlist"), py::arg("pos"), py::arg("col"), py::arg("text")
    );

    m.def("drawlist_add_triangle",
        [](ImDrawList* dl, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3,
           ImU32 col, float thickness) {
            dl->AddTriangle(p1, p2, p3, col, thickness);
        },
        py::arg("drawlist"), py::arg("p1"), py::arg("p2"), py::arg("p3"),
        py::arg("col"), py::arg("thickness") = 1.0f
    );

    m.def("drawlist_add_triangle_filled",
        [](ImDrawList* dl, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col) {
            dl->AddTriangleFilled(p1, p2, p3, col);
        },
        py::arg("drawlist"), py::arg("p1"), py::arg("p2"), py::arg("p3"),
        py::arg("col")
    );

    m.def("drawlist_add_image",
        [](ImDrawList* dl, ImTextureID texture_id, const ImVec2& p_min, const ImVec2& p_max,
           const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col) {
            dl->AddImage(texture_id, p_min, p_max, uv_min, uv_max, col);
        },
        py::arg("drawlist"), py::arg("texture_id"),
        py::arg("p_min"), py::arg("p_max"),
        py::arg("uv_min") = ImVec2(0.0f, 0.0f),
        py::arg("uv_max") = ImVec2(1.0f, 1.0f),
        py::arg("col") = IM_COL32_WHITE
    );

}