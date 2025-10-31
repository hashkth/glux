
import glux
from glux import imgui
import moderngl as mgl
import tkinter as tk
from tkinter import filedialog
import os

os.environ["ALSOFT_CONF"] = "alsoft.ini"

root = tk.Tk()
root.withdraw()

class App:

    def __init__(self):
        self.window = glux.Window(1280, 720, "Demo")
        self.ctx = mgl.create_context()
        self.io = imgui.get_io()
        self.io.font_global_scale = 2.5
        self.oal_ctx = glux.oal.Context()
        
        self.debug = True
        self.magic = 0
        self.check = False
        self.radio_items = ['A', 'B', 'C']
        self.radio_select = 0
        self.line = ""
        self.line_with_hint = ""
        self.para = ""
        self.in_float = 1
        self.combo_items = ['1', '2', '3']
        self.combo_select = 0
        self.selected_row = None
        self.filepath = "No file loaded"
        self.source = self.oal_ctx.source()
        self.buffer = None
        self.stream = self.oal_ctx.stream()

        self.style = imgui.get_style()
        self.style.window_rounding = 10

        colors = self.style.colors
        colors[imgui.Col.TitleBg] = imgui.Vec4(0.8, 0, 1, 0.3)
        self.style.colors = colors

        self.window.set_events_callback(self.events)
        self.window.set_process_callback(self.process)
        self.window.set_render_callback(self.render)
        self.window.set_render_ui_callback(self.render_ui)
        self.window.run()

    def events(self):
        pass

    def process(self):
        self.stream.update()

    def render(self):
        self.ctx.clear(0.0, 0.0, 0.0, 1.0)

    def render_ui(self):
        imgui.push_style_color(imgui.Col.TitleBgActive, imgui.Vec4(0.8, 0, 1, 0.6))
        if self.debug:
            _, self.debug = imgui.begin("Debug", self.debug)
            imgui.text("Hello, World!")
            imgui.text_colored(imgui.Vec4(0, 1, 0, 1), "Hello, Green World!")
            imgui.text("Text"); imgui.same_line(); imgui.text("Same Line")
            [imgui.spacing() for _ in range(3)]; imgui.separator()
            imgui.text("Separated")
            imgui.separator(); [imgui.spacing() for _ in range(3)]
            imgui.button("Button", imgui.Vec2(200, 50))
            imgui.arrow_button("##right", imgui.Dir.Right)
            imgui.text("Click for Magic++ -->"); imgui.same_line()
            if imgui.invisible_button("##invisible", imgui.Vec2(400, 100)): self.magic += 1
            imgui.separator()
            imgui.text("Magic: " + str(self.magic))
            imgui.separator()
            _, self.check = imgui.checkbox("Checkbox", self.check)
            for i, label in enumerate(self.radio_items):
                changed, result = imgui.radio_button(label+' ', self.radio_select, i)
                if changed:
                    self.radio_select = result
                imgui.same_line()
            imgui.spacing()
            _, self.line = imgui.input_text("Input Text", self.line)
            _, self.line_with_hint = imgui.input_text_with_hint("Input Text With Hint", "Hint...", self.line_with_hint)
            _, self.para = imgui.input_text_multiline("Input Text Multiline", self.para, imgui.Vec2(800, 100))
            _, self.combo_select = imgui.combo("Combo", self.combo_select, self.combo_items)            
            imgui.end()

        imgui.push_style_var_vec2(imgui.StyleVar.WindowPadding, imgui.Vec2(20, 20))
        imgui.begin("Table")
        if imgui.begin_table("MyTable", 3, imgui.TableFlags.Borders | imgui.TableFlags.RowBg):
        
            # Set up columns (optional labels)
            imgui.table_setup_column("ID")
            imgui.table_setup_column("Name")
            imgui.table_setup_column("Value")
            imgui.table_headers_row()

            # Add rows
            for i in range(5):
                imgui.table_next_row()
                imgui.table_set_column_index(0)
                imgui.text(str(i))

                imgui.table_set_column_index(1)
                pos = imgui.get_cursor_pos()
                imgui.text(f"Item {i}")
                dims = imgui.get_item_rect_size()
                imgui.set_cursor_pos(imgui.Vec2(pos[0], pos[1]))
                if imgui.invisible_button(f"##Item {i}", imgui.Vec2(dims[0], dims[1])):
                    self.selected_row = i

                imgui.table_set_column_index(2)
                imgui.text(f"{i * 10}")
            imgui.end_table()
            if self.selected_row != None:
                imgui.text(f"Item {self.selected_row} selected")
        imgui.end()
        imgui.pop_style_var()

        imgui.begin("Tree")
        if imgui.tree_node("Root Node"):
            imgui.text("Child 1")
            imgui.tree_push("Subtree")
            if imgui.tree_node("Child 2"):
                imgui.text("Grandchild")
                imgui.tree_pop()
            imgui.tree_pop()
            imgui.tree_pop()
        imgui.set_next_item_open(True, imgui.Cond.Once)
        if imgui.collapsing_header("Header"):
            imgui.text("Pre-Opened Header Text!")

        imgui.end()

        imgui.begin("Audio")
        if imgui.button("Load a file..."):
            temp = self.filepath
            self.filepath = filedialog.askopenfilename(
                title="Load a file...",
                filetypes=[("Audio files", (".wav", ".ogg", ".mp3"))]
            )
            if self.filepath:
                self.buffer = self.oal_ctx.buffer(self.filepath)
            else:
                self.filepath = temp
        if self.filepath == "No file loaded":
            imgui.text(self.filepath)
        else:
            imgui.text("Playing: " + self.filepath.split("/")[-1])
            imgui.text(str(self.buffer.data().duration / 60))
        if imgui.button("Play Source"):
            self.source.play(self.buffer)
        if imgui.button("Play Stream"):
            self.stream.play(self.filepath, loop=True)
        if imgui.button("Stop"):
            self.source.stop()
            self.stream.stop()
        imgui.end()

        imgui.pop_style_color()

App()