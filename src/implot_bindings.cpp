#include "implot_bindings.h"

#include <array>
#include <vector>
#include <string>
#include <tuple>
#include <cstring>
#include <cstdint>
#include <algorithm>

// =====================================================================================
// [SECTION] Enum binding macros
// =====================================================================================

#define ENUM_IM_AXIS(name)                        .value(#name, ImAxis_##name)
#define ENUM_IMPLOT_PROP(name)                    .value(#name, ImPlotProp_##name)
#define ENUM_IMPLOT_FLAGS(name)                   .value(#name, ImPlotFlags_##name)
#define ENUM_IMPLOT_AXIS_FLAGS(name)              .value(#name, ImPlotAxisFlags_##name)
#define ENUM_IMPLOT_SUBPLOT_FLAGS(name)           .value(#name, ImPlotSubplotFlags_##name)
#define ENUM_IMPLOT_LEGEND_FLAGS(name)            .value(#name, ImPlotLegendFlags_##name)
#define ENUM_IMPLOT_MOUSE_TEXT_FLAGS(name)        .value(#name, ImPlotMouseTextFlags_##name)
#define ENUM_IMPLOT_DRAG_TOOL_FLAGS(name)         .value(#name, ImPlotDragToolFlags_##name)
#define ENUM_IMPLOT_COLORMAP_SCALE_FLAGS(name)    .value(#name, ImPlotColormapScaleFlags_##name)
#define ENUM_IMPLOT_ITEM_FLAGS(name)              .value(#name, ImPlotItemFlags_##name)
#define ENUM_IMPLOT_LINE_FLAGS(name)              .value(#name, ImPlotLineFlags_##name)
#define ENUM_IMPLOT_SCATTER_FLAGS(name)           .value(#name, ImPlotScatterFlags_##name)
#define ENUM_IMPLOT_BUBBLES_FLAGS(name)           .value(#name, ImPlotBubblesFlags_##name)
#define ENUM_IMPLOT_POLYGON_FLAGS(name)           .value(#name, ImPlotPolygonFlags_##name)
#define ENUM_IMPLOT_STAIRS_FLAGS(name)            .value(#name, ImPlotStairsFlags_##name)
#define ENUM_IMPLOT_SHADED_FLAGS(name)            .value(#name, ImPlotShadedFlags_##name)
#define ENUM_IMPLOT_BARS_FLAGS(name)              .value(#name, ImPlotBarsFlags_##name)
#define ENUM_IMPLOT_BAR_GROUPS_FLAGS(name)        .value(#name, ImPlotBarGroupsFlags_##name)
#define ENUM_IMPLOT_ERROR_BARS_FLAGS(name)        .value(#name, ImPlotErrorBarsFlags_##name)
#define ENUM_IMPLOT_STEMS_FLAGS(name)             .value(#name, ImPlotStemsFlags_##name)
#define ENUM_IMPLOT_INF_LINES_FLAGS(name)         .value(#name, ImPlotInfLinesFlags_##name)
#define ENUM_IMPLOT_PIE_CHART_FLAGS(name)         .value(#name, ImPlotPieChartFlags_##name)
#define ENUM_IMPLOT_HEATMAP_FLAGS(name)           .value(#name, ImPlotHeatmapFlags_##name)
#define ENUM_IMPLOT_HISTOGRAM_FLAGS(name)         .value(#name, ImPlotHistogramFlags_##name)
#define ENUM_IMPLOT_DIGITAL_FLAGS(name)           .value(#name, ImPlotDigitalFlags_##name)
#define ENUM_IMPLOT_IMAGE_FLAGS(name)             .value(#name, ImPlotImageFlags_##name)
#define ENUM_IMPLOT_TEXT_FLAGS(name)              .value(#name, ImPlotTextFlags_##name)
#define ENUM_IMPLOT_DUMMY_FLAGS(name)             .value(#name, ImPlotDummyFlags_##name)
#define ENUM_IMPLOT_COND(name)                    .value(#name, ImPlotCond_##name)
#define ENUM_IMPLOT_COL(name)                     .value(#name, ImPlotCol_##name)
#define ENUM_IMPLOT_STYLE_VAR(name)               .value(#name, ImPlotStyleVar_##name)
#define ENUM_IMPLOT_SCALE(name)                   .value(#name, ImPlotScale_##name)
#define ENUM_IMPLOT_MARKER(name)                  .value(#name, ImPlotMarker_##name)
#define ENUM_IMPLOT_COLORMAP(name)                .value(#name, ImPlotColormap_##name)
#define ENUM_IMPLOT_LOCATION(name)                .value(#name, ImPlotLocation_##name)
#define ENUM_IMPLOT_BIN(name)                     .value(#name, ImPlotBin_##name)


// =====================================================================================
// [SECTION] Enums and Types
// =====================================================================================

void bind_implot_enums(py::module_& m) {
    // Axis indices.
    py::enum_<ImAxis_>(m, "Axis")
        ENUM_IM_AXIS(X1)
        ENUM_IM_AXIS(X2)
        ENUM_IM_AXIS(X3)
        ENUM_IM_AXIS(Y1)
        ENUM_IM_AXIS(Y2)
        ENUM_IM_AXIS(Y3)
        ENUM_IM_AXIS(COUNT)
        ;

    // ImPlotProp_ is a plain enum used as a property tag, not a bitmask — no py::arithmetic().
    py::enum_<ImPlotProp_>(m, "Prop")
        ENUM_IMPLOT_PROP(LineColor)
        ENUM_IMPLOT_PROP(LineColors)
        ENUM_IMPLOT_PROP(LineWeight)
        ENUM_IMPLOT_PROP(FillColor)
        ENUM_IMPLOT_PROP(FillColors)
        ENUM_IMPLOT_PROP(FillAlpha)
        ENUM_IMPLOT_PROP(Marker)
        ENUM_IMPLOT_PROP(MarkerSize)
        ENUM_IMPLOT_PROP(MarkerSizes)
        ENUM_IMPLOT_PROP(MarkerLineColor)
        ENUM_IMPLOT_PROP(MarkerLineColors)
        ENUM_IMPLOT_PROP(MarkerFillColor)
        ENUM_IMPLOT_PROP(MarkerFillColors)
        ENUM_IMPLOT_PROP(Size)
        ENUM_IMPLOT_PROP(Offset)
        ENUM_IMPLOT_PROP(Stride)
        ENUM_IMPLOT_PROP(Flags)
        ;

    py::enum_<ImPlotFlags_>(m, "Flags", py::arithmetic())
        .value("None_", ImPlotFlags_None)
        ENUM_IMPLOT_FLAGS(NoTitle)
        ENUM_IMPLOT_FLAGS(NoLegend)
        ENUM_IMPLOT_FLAGS(NoMouseText)
        ENUM_IMPLOT_FLAGS(NoInputs)
        ENUM_IMPLOT_FLAGS(NoMenus)
        ENUM_IMPLOT_FLAGS(NoBoxSelect)
        ENUM_IMPLOT_FLAGS(NoFrame)
        ENUM_IMPLOT_FLAGS(Equal)
        ENUM_IMPLOT_FLAGS(Crosshairs)
        ENUM_IMPLOT_FLAGS(CanvasOnly)
        ;

    py::enum_<ImPlotAxisFlags_>(m, "AxisFlags", py::arithmetic())
        .value("None_", ImPlotAxisFlags_None)
        ENUM_IMPLOT_AXIS_FLAGS(NoLabel)
        ENUM_IMPLOT_AXIS_FLAGS(NoGridLines)
        ENUM_IMPLOT_AXIS_FLAGS(NoTickMarks)
        ENUM_IMPLOT_AXIS_FLAGS(NoTickLabels)
        ENUM_IMPLOT_AXIS_FLAGS(NoInitialFit)
        ENUM_IMPLOT_AXIS_FLAGS(NoMenus)
        ENUM_IMPLOT_AXIS_FLAGS(NoSideSwitch)
        ENUM_IMPLOT_AXIS_FLAGS(NoHighlight)
        ENUM_IMPLOT_AXIS_FLAGS(Opposite)
        ENUM_IMPLOT_AXIS_FLAGS(Foreground)
        ENUM_IMPLOT_AXIS_FLAGS(Invert)
        ENUM_IMPLOT_AXIS_FLAGS(AutoFit)
        ENUM_IMPLOT_AXIS_FLAGS(RangeFit)
        ENUM_IMPLOT_AXIS_FLAGS(PanStretch)
        ENUM_IMPLOT_AXIS_FLAGS(LockMin)
        ENUM_IMPLOT_AXIS_FLAGS(LockMax)
        ENUM_IMPLOT_AXIS_FLAGS(Lock)
        ENUM_IMPLOT_AXIS_FLAGS(NoDecorations)
        ENUM_IMPLOT_AXIS_FLAGS(AuxDefault)
        ;

    py::enum_<ImPlotSubplotFlags_>(m, "SubplotFlags", py::arithmetic())
        .value("None_", ImPlotSubplotFlags_None)
        ENUM_IMPLOT_SUBPLOT_FLAGS(NoTitle)
        ENUM_IMPLOT_SUBPLOT_FLAGS(NoLegend)
        ENUM_IMPLOT_SUBPLOT_FLAGS(NoMenus)
        ENUM_IMPLOT_SUBPLOT_FLAGS(NoResize)
        ENUM_IMPLOT_SUBPLOT_FLAGS(NoAlign)
        ENUM_IMPLOT_SUBPLOT_FLAGS(ShareItems)
        ENUM_IMPLOT_SUBPLOT_FLAGS(LinkRows)
        ENUM_IMPLOT_SUBPLOT_FLAGS(LinkCols)
        ENUM_IMPLOT_SUBPLOT_FLAGS(LinkAllX)
        ENUM_IMPLOT_SUBPLOT_FLAGS(LinkAllY)
        ENUM_IMPLOT_SUBPLOT_FLAGS(ColMajor)
        ;

    py::enum_<ImPlotLegendFlags_>(m, "LegendFlags", py::arithmetic())
        .value("None_", ImPlotLegendFlags_None)
        ENUM_IMPLOT_LEGEND_FLAGS(NoButtons)
        ENUM_IMPLOT_LEGEND_FLAGS(NoHighlightItem)
        ENUM_IMPLOT_LEGEND_FLAGS(NoHighlightAxis)
        ENUM_IMPLOT_LEGEND_FLAGS(NoMenus)
        ENUM_IMPLOT_LEGEND_FLAGS(Outside)
        ENUM_IMPLOT_LEGEND_FLAGS(Horizontal)
        ENUM_IMPLOT_LEGEND_FLAGS(Sort)
        ENUM_IMPLOT_LEGEND_FLAGS(Reverse)
        ;

    py::enum_<ImPlotMouseTextFlags_>(m, "MouseTextFlags", py::arithmetic())
        .value("None_", ImPlotMouseTextFlags_None)
        ENUM_IMPLOT_MOUSE_TEXT_FLAGS(NoAuxAxes)
        ENUM_IMPLOT_MOUSE_TEXT_FLAGS(NoFormat)
        ENUM_IMPLOT_MOUSE_TEXT_FLAGS(ShowAlways)
        ;

    py::enum_<ImPlotDragToolFlags_>(m, "DragToolFlags", py::arithmetic())
        .value("None_", ImPlotDragToolFlags_None)
        ENUM_IMPLOT_DRAG_TOOL_FLAGS(NoCursors)
        ENUM_IMPLOT_DRAG_TOOL_FLAGS(NoFit)
        ENUM_IMPLOT_DRAG_TOOL_FLAGS(NoInputs)
        ENUM_IMPLOT_DRAG_TOOL_FLAGS(Delayed)
        ;

    py::enum_<ImPlotColormapScaleFlags_>(m, "ColormapScaleFlags", py::arithmetic())
        .value("None_", ImPlotColormapScaleFlags_None)
        ENUM_IMPLOT_COLORMAP_SCALE_FLAGS(NoLabel)
        ENUM_IMPLOT_COLORMAP_SCALE_FLAGS(Opposite)
        ENUM_IMPLOT_COLORMAP_SCALE_FLAGS(Invert)
        ;

    py::enum_<ImPlotItemFlags_>(m, "ItemFlags", py::arithmetic())
        .value("None_", ImPlotItemFlags_None)
        ENUM_IMPLOT_ITEM_FLAGS(NoLegend)
        ENUM_IMPLOT_ITEM_FLAGS(NoFit)
        ;

    py::enum_<ImPlotLineFlags_>(m, "LineFlags", py::arithmetic())
        .value("None_", ImPlotLineFlags_None)
        ENUM_IMPLOT_LINE_FLAGS(Segments)
        ENUM_IMPLOT_LINE_FLAGS(Loop)
        ENUM_IMPLOT_LINE_FLAGS(SkipNaN)
        ENUM_IMPLOT_LINE_FLAGS(NoClip)
        ENUM_IMPLOT_LINE_FLAGS(Shaded)
        ;

    py::enum_<ImPlotScatterFlags_>(m, "ScatterFlags", py::arithmetic())
        .value("None_", ImPlotScatterFlags_None)
        ENUM_IMPLOT_SCATTER_FLAGS(NoClip)
        ;

    py::enum_<ImPlotBubblesFlags_>(m, "BubblesFlags", py::arithmetic())
        .value("None_", ImPlotBubblesFlags_None)
        ;

    py::enum_<ImPlotPolygonFlags_>(m, "PolygonFlags", py::arithmetic())
        .value("None_", ImPlotPolygonFlags_None)
        ENUM_IMPLOT_POLYGON_FLAGS(Concave)
        ;

    py::enum_<ImPlotStairsFlags_>(m, "StairsFlags", py::arithmetic())
        .value("None_", ImPlotStairsFlags_None)
        ENUM_IMPLOT_STAIRS_FLAGS(PreStep)
        ENUM_IMPLOT_STAIRS_FLAGS(Shaded)
        ;

    py::enum_<ImPlotShadedFlags_>(m, "ShadedFlags", py::arithmetic())
        .value("None_", ImPlotShadedFlags_None)
        ;

    py::enum_<ImPlotBarsFlags_>(m, "BarsFlags", py::arithmetic())
        .value("None_", ImPlotBarsFlags_None)
        ENUM_IMPLOT_BARS_FLAGS(Horizontal)
        ;

    py::enum_<ImPlotBarGroupsFlags_>(m, "BarGroupsFlags", py::arithmetic())
        .value("None_", ImPlotBarGroupsFlags_None)
        ENUM_IMPLOT_BAR_GROUPS_FLAGS(Horizontal)
        ENUM_IMPLOT_BAR_GROUPS_FLAGS(Stacked)
        ;

    py::enum_<ImPlotErrorBarsFlags_>(m, "ErrorBarsFlags", py::arithmetic())
        .value("None_", ImPlotErrorBarsFlags_None)
        ENUM_IMPLOT_ERROR_BARS_FLAGS(Horizontal)
        ;

    py::enum_<ImPlotStemsFlags_>(m, "StemsFlags", py::arithmetic())
        .value("None_", ImPlotStemsFlags_None)
        ENUM_IMPLOT_STEMS_FLAGS(Horizontal)
        ;

    py::enum_<ImPlotInfLinesFlags_>(m, "InfLinesFlags", py::arithmetic())
        .value("None_", ImPlotInfLinesFlags_None)
        ENUM_IMPLOT_INF_LINES_FLAGS(Horizontal)
        ;

    py::enum_<ImPlotPieChartFlags_>(m, "PieChartFlags", py::arithmetic())
        .value("None_", ImPlotPieChartFlags_None)
        ENUM_IMPLOT_PIE_CHART_FLAGS(Normalize)
        ENUM_IMPLOT_PIE_CHART_FLAGS(IgnoreHidden)
        ENUM_IMPLOT_PIE_CHART_FLAGS(Exploding)
        ENUM_IMPLOT_PIE_CHART_FLAGS(NoSliceBorder)
        ;

    py::enum_<ImPlotHeatmapFlags_>(m, "HeatmapFlags", py::arithmetic())
        .value("None_", ImPlotHeatmapFlags_None)
        ENUM_IMPLOT_HEATMAP_FLAGS(ColMajor)
        ;

    py::enum_<ImPlotHistogramFlags_>(m, "HistogramFlags", py::arithmetic())
        .value("None_", ImPlotHistogramFlags_None)
        ENUM_IMPLOT_HISTOGRAM_FLAGS(Horizontal)
        ENUM_IMPLOT_HISTOGRAM_FLAGS(Cumulative)
        ENUM_IMPLOT_HISTOGRAM_FLAGS(Density)
        ENUM_IMPLOT_HISTOGRAM_FLAGS(NoOutliers)
        ENUM_IMPLOT_HISTOGRAM_FLAGS(ColMajor)
        ;

    py::enum_<ImPlotDigitalFlags_>(m, "DigitalFlags", py::arithmetic())
        .value("None_", ImPlotDigitalFlags_None)
        ;

    py::enum_<ImPlotImageFlags_>(m, "ImageFlags", py::arithmetic())
        .value("None_", ImPlotImageFlags_None)
        ;

    py::enum_<ImPlotTextFlags_>(m, "TextFlags", py::arithmetic())
        .value("None_", ImPlotTextFlags_None)
        ENUM_IMPLOT_TEXT_FLAGS(Vertical)
        ;

    py::enum_<ImPlotDummyFlags_>(m, "DummyFlags", py::arithmetic())
        .value("None_", ImPlotDummyFlags_None)
        ;

    // ImPlotCond_ values are mutually-exclusive conditions, not combined bitmasks — no py::arithmetic().
    py::enum_<ImPlotCond_>(m, "Cond")
        .value("None_", ImPlotCond_None)
        ENUM_IMPLOT_COND(Always)
        ENUM_IMPLOT_COND(Once)
        ;

    py::enum_<ImPlotCol_>(m, "Col", py::arithmetic())
        ENUM_IMPLOT_COL(FrameBg)
        ENUM_IMPLOT_COL(PlotBg)
        ENUM_IMPLOT_COL(PlotBorder)
        ENUM_IMPLOT_COL(LegendBg)
        ENUM_IMPLOT_COL(LegendBorder)
        ENUM_IMPLOT_COL(LegendText)
        ENUM_IMPLOT_COL(TitleText)
        ENUM_IMPLOT_COL(InlayText)
        ENUM_IMPLOT_COL(AxisText)
        ENUM_IMPLOT_COL(AxisGrid)
        ENUM_IMPLOT_COL(AxisTick)
        ENUM_IMPLOT_COL(AxisBg)
        ENUM_IMPLOT_COL(AxisBgHovered)
        ENUM_IMPLOT_COL(AxisBgActive)
        ENUM_IMPLOT_COL(Selection)
        ENUM_IMPLOT_COL(Crosshairs)
        ENUM_IMPLOT_COL(COUNT)
        ;

    py::enum_<ImPlotStyleVar_>(m, "StyleVar", py::arithmetic())
        ENUM_IMPLOT_STYLE_VAR(PlotDefaultSize)
        ENUM_IMPLOT_STYLE_VAR(PlotMinSize)
        ENUM_IMPLOT_STYLE_VAR(PlotBorderSize)
        ENUM_IMPLOT_STYLE_VAR(MinorAlpha)
        ENUM_IMPLOT_STYLE_VAR(MajorTickLen)
        ENUM_IMPLOT_STYLE_VAR(MinorTickLen)
        ENUM_IMPLOT_STYLE_VAR(MajorTickSize)
        ENUM_IMPLOT_STYLE_VAR(MinorTickSize)
        ENUM_IMPLOT_STYLE_VAR(MajorGridSize)
        ENUM_IMPLOT_STYLE_VAR(MinorGridSize)
        ENUM_IMPLOT_STYLE_VAR(PlotPadding)
        ENUM_IMPLOT_STYLE_VAR(LabelPadding)
        ENUM_IMPLOT_STYLE_VAR(LegendPadding)
        ENUM_IMPLOT_STYLE_VAR(LegendInnerPadding)
        ENUM_IMPLOT_STYLE_VAR(LegendSpacing)
        ENUM_IMPLOT_STYLE_VAR(MousePosPadding)
        ENUM_IMPLOT_STYLE_VAR(AnnotationPadding)
        ENUM_IMPLOT_STYLE_VAR(FitPadding)
        ENUM_IMPLOT_STYLE_VAR(DigitalPadding)
        ENUM_IMPLOT_STYLE_VAR(DigitalSpacing)
        ENUM_IMPLOT_STYLE_VAR(COUNT)
        ;

    // ImPlotScale_ selects one scale mode at a time — no py::arithmetic().
    py::enum_<ImPlotScale_>(m, "Scale")
        ENUM_IMPLOT_SCALE(Linear)
        ENUM_IMPLOT_SCALE(Time)
        ENUM_IMPLOT_SCALE(Log10)
        ENUM_IMPLOT_SCALE(SymLog)
        ;

    // ImPlotMarker_ selects one marker at a time — no py::arithmetic().
    py::enum_<ImPlotMarker_>(m, "Marker")
        ENUM_IMPLOT_MARKER(None)
        ENUM_IMPLOT_MARKER(Auto)
        ENUM_IMPLOT_MARKER(Circle)
        ENUM_IMPLOT_MARKER(Square)
        ENUM_IMPLOT_MARKER(Diamond)
        ENUM_IMPLOT_MARKER(Up)
        ENUM_IMPLOT_MARKER(Down)
        ENUM_IMPLOT_MARKER(Left)
        ENUM_IMPLOT_MARKER(Right)
        ENUM_IMPLOT_MARKER(Cross)
        ENUM_IMPLOT_MARKER(Plus)
        ENUM_IMPLOT_MARKER(Asterisk)
        ENUM_IMPLOT_MARKER(COUNT)
        ;

    // ImPlotColormap_ is an index enum, not a bitmask — no py::arithmetic().
    py::enum_<ImPlotColormap_>(m, "Colormap")
        ENUM_IMPLOT_COLORMAP(Deep)
        ENUM_IMPLOT_COLORMAP(Dark)
        ENUM_IMPLOT_COLORMAP(Pastel)
        ENUM_IMPLOT_COLORMAP(Paired)
        ENUM_IMPLOT_COLORMAP(Viridis)
        ENUM_IMPLOT_COLORMAP(Plasma)
        ENUM_IMPLOT_COLORMAP(Hot)
        ENUM_IMPLOT_COLORMAP(Cool)
        ENUM_IMPLOT_COLORMAP(Pink)
        ENUM_IMPLOT_COLORMAP(Jet)
        ENUM_IMPLOT_COLORMAP(Twilight)
        ENUM_IMPLOT_COLORMAP(RdBu)
        ENUM_IMPLOT_COLORMAP(BrBG)
        ENUM_IMPLOT_COLORMAP(PiYG)
        ENUM_IMPLOT_COLORMAP(Spectral)
        ENUM_IMPLOT_COLORMAP(Greys)
        ;

    py::enum_<ImPlotLocation_>(m, "Location", py::arithmetic())
        ENUM_IMPLOT_LOCATION(Center)
        ENUM_IMPLOT_LOCATION(North)
        ENUM_IMPLOT_LOCATION(South)
        ENUM_IMPLOT_LOCATION(West)
        ENUM_IMPLOT_LOCATION(East)
        ENUM_IMPLOT_LOCATION(NorthWest)
        ENUM_IMPLOT_LOCATION(NorthEast)
        ENUM_IMPLOT_LOCATION(SouthWest)
        ENUM_IMPLOT_LOCATION(SouthEast)
        ;

    // ImPlotBin_ values are special negative sentinels selecting a binning method — no py::arithmetic().
    py::enum_<ImPlotBin_>(m, "Bin")
        ENUM_IMPLOT_BIN(Sqrt)
        ENUM_IMPLOT_BIN(Sturges)
        ENUM_IMPLOT_BIN(Rice)
        ENUM_IMPLOT_BIN(Scott)
        ;
}

// =====================================================================================
// [SECTION] Structs
// =====================================================================================

void bind_implot_structs(py::module_& m) {
    // NOTE: ImPlotContext/ImGuiContext are forward-declared opaque structs (no
    // public definition), so they cannot be registered as py::class_ types.
    // Context handles are instead passed around as raw void* (see bind_implot_funcs).

    py::class_<ImPlotSpec>(m, "Spec")
        .def(py::init<>())
        .def_readwrite("line_color", &ImPlotSpec::LineColor)
        .def_readwrite("line_weight", &ImPlotSpec::LineWeight)
        .def_readwrite("fill_color", &ImPlotSpec::FillColor)
        .def_readwrite("fill_alpha", &ImPlotSpec::FillAlpha)
        .def_readwrite("marker", &ImPlotSpec::Marker)
        .def_readwrite("marker_size", &ImPlotSpec::MarkerSize)
        .def_readwrite("marker_line_color", &ImPlotSpec::MarkerLineColor)
        .def_readwrite("marker_fill_color", &ImPlotSpec::MarkerFillColor)
        .def_readwrite("size", &ImPlotSpec::Size)
        .def_readwrite("offset", &ImPlotSpec::Offset)
        .def_readwrite("stride", &ImPlotSpec::Stride)
        .def_readwrite("flags", &ImPlotSpec::Flags)
        ;

    py::class_<ImPlotPoint>(m, "Point")
        .def(py::init<double, double>(), py::arg("x") = 0.0, py::arg("y") = 0.0)
        .def(py::init<const ImVec2&>(), py::arg("p"))
        .def_readwrite("x", &ImPlotPoint::x)
        .def_readwrite("y", &ImPlotPoint::y)
        .def("__repr__", [](const ImPlotPoint& p) {
            return "Point(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
        })
        ;

    py::class_<ImPlotRange>(m, "Range")
        .def(py::init<double, double>(), py::arg("min") = 0.0, py::arg("max") = 0.0)
        .def_readwrite("min", &ImPlotRange::Min)
        .def_readwrite("max", &ImPlotRange::Max)
        .def("contains", &ImPlotRange::Contains, py::arg("value"))
        .def("size", &ImPlotRange::Size)
        .def("clamp", &ImPlotRange::Clamp, py::arg("value"))
        ;

    py::class_<ImPlotRect>(m, "Rect")
        .def(py::init<double, double, double, double>(),
             py::arg("x_min") = 0.0, py::arg("x_max") = 0.0,
             py::arg("y_min") = 0.0, py::arg("y_max") = 0.0)
        .def_readwrite("x", &ImPlotRect::X)
        .def_readwrite("y", &ImPlotRect::Y)
        .def("contains", [](const ImPlotRect& r, const ImPlotPoint& p) { return r.Contains(p); }, py::arg("p"))
        .def("contains_xy", [](const ImPlotRect& r, double x, double y) { return r.Contains(x, y); }, py::arg("x"), py::arg("y"))
        .def("size", &ImPlotRect::Size)
        .def("clamp", [](const ImPlotRect& r, const ImPlotPoint& p) { return r.Clamp(p); }, py::arg("p"))
        .def("clamp_xy", [](const ImPlotRect& r, double x, double y) { return r.Clamp(x, y); }, py::arg("x"), py::arg("y"))
        .def("min", &ImPlotRect::Min)
        .def("max", &ImPlotRect::Max)
        ;

    py::class_<ImPlotStyle>(m, "Style")
        .def(py::init<>())
        .def_readwrite("plot_default_size", &ImPlotStyle::PlotDefaultSize)
        .def_readwrite("plot_min_size", &ImPlotStyle::PlotMinSize)
        .def_readwrite("plot_border_size", &ImPlotStyle::PlotBorderSize)
        .def_readwrite("minor_alpha", &ImPlotStyle::MinorAlpha)
        .def_readwrite("major_tick_len", &ImPlotStyle::MajorTickLen)
        .def_readwrite("minor_tick_len", &ImPlotStyle::MinorTickLen)
        .def_readwrite("major_tick_size", &ImPlotStyle::MajorTickSize)
        .def_readwrite("minor_tick_size", &ImPlotStyle::MinorTickSize)
        .def_readwrite("major_grid_size", &ImPlotStyle::MajorGridSize)
        .def_readwrite("minor_grid_size", &ImPlotStyle::MinorGridSize)
        .def_readwrite("plot_padding", &ImPlotStyle::PlotPadding)
        .def_readwrite("label_padding", &ImPlotStyle::LabelPadding)
        .def_readwrite("legend_padding", &ImPlotStyle::LegendPadding)
        .def_readwrite("legend_inner_padding", &ImPlotStyle::LegendInnerPadding)
        .def_readwrite("legend_spacing", &ImPlotStyle::LegendSpacing)
        .def_readwrite("mouse_pos_padding", &ImPlotStyle::MousePosPadding)
        .def_readwrite("annotation_padding", &ImPlotStyle::AnnotationPadding)
        .def_readwrite("fit_padding", &ImPlotStyle::FitPadding)
        .def_readwrite("digital_padding", &ImPlotStyle::DigitalPadding)
        .def_readwrite("digital_spacing", &ImPlotStyle::DigitalSpacing)
        .def_readwrite("colormap", &ImPlotStyle::Colormap)
        .def_readwrite("use_local_time", &ImPlotStyle::UseLocalTime)
        .def_readwrite("use_iso8601", &ImPlotStyle::UseISO8601)
        .def_readwrite("use_24_hour_clock", &ImPlotStyle::Use24HourClock)
        .def_property("colors",
            [](ImPlotStyle& style) {
                return std::vector<ImVec4>(style.Colors, style.Colors + ImPlotCol_COUNT);
            },
            [](ImPlotStyle& style, const std::vector<ImVec4>& colors) {
                for (int i = 0; i < ImPlotCol_COUNT && i < (int)colors.size(); ++i)
                    style.Colors[i] = colors[i];
            })
        ;

    py::class_<ImPlotInputMap>(m, "InputMap")
        .def(py::init<>())
        .def_readwrite("pan", &ImPlotInputMap::Pan)
        .def_readwrite("pan_mod", &ImPlotInputMap::PanMod)
        .def_readwrite("fit", &ImPlotInputMap::Fit)
        .def_readwrite("select", &ImPlotInputMap::Select)
        .def_readwrite("select_cancel", &ImPlotInputMap::SelectCancel)
        .def_readwrite("select_mod", &ImPlotInputMap::SelectMod)
        .def_readwrite("select_horz_mod", &ImPlotInputMap::SelectHorzMod)
        .def_readwrite("select_vert_mod", &ImPlotInputMap::SelectVertMod)
        .def_readwrite("menu", &ImPlotInputMap::Menu)
        .def_readwrite("override_mod", &ImPlotInputMap::OverrideMod)
        .def_readwrite("zoom_mod", &ImPlotInputMap::ZoomMod)
        .def_readwrite("zoom_rate", &ImPlotInputMap::ZoomRate)
        ;
}

// =====================================================================================
// [SECTION] Helper utilities for function bindings
// =====================================================================================

namespace {

// Trampoline data/function used to call a Python callable as an ImPlotGetter.
// Only valid for the duration of a single synchronous PlotXG call.
struct PyGetterCtx {
    const py::function* fn;
};

ImPlotPoint py_getter_trampoline(int idx, void* user_data) {
    auto* ctx = reinterpret_cast<PyGetterCtx*>(user_data);
    py::gil_scoped_acquire acquire;
    py::object result = (*ctx->fn)(idx);
    auto t = result.cast<std::pair<double, double>>();
    return ImPlotPoint(t.first, t.second);
}

// Converts a vector<std::string> into a vector<const char*> valid for the
// lifetime of the owning std::vector<std::string>.
std::vector<const char*> to_cstr_array(const std::vector<std::string>& strs) {
    std::vector<const char*> out;
    out.reserve(strs.size());
    for (auto& s : strs) out.push_back(s.c_str());
    return out;
}

} // namespace

// =====================================================================================
// [SECTION] Functions
// =====================================================================================

void bind_implot_funcs(py::module_& m) {

    // ----- Contexts -----
    // ImPlotContext/ImGuiContext are opaque incomplete types, so handles are
    // passed to/from Python as raw void* rather than as registered py::class_ types.
    m.def("create_context",
        []() -> void* { return reinterpret_cast<void*>(ImPlot::CreateContext()); }
    );
    m.def("destroy_context",
        [](void* ctx) { ImPlot::DestroyContext(reinterpret_cast<ImPlotContext*>(ctx)); },
        py::arg("ctx") = nullptr
    );
    m.def("get_current_context",
        []() -> void* { return reinterpret_cast<void*>(ImPlot::GetCurrentContext()); }
    );
    m.def("set_current_context",
        [](void* ctx) { ImPlot::SetCurrentContext(reinterpret_cast<ImPlotContext*>(ctx)); },
        py::arg("ctx")
    );
    m.def("set_imgui_context",
        [](void* ctx) { ImPlot::SetImGuiContext(reinterpret_cast<ImGuiContext*>(ctx)); },
        py::arg("ctx")
    );

    // ----- Begin/End Plot -----
    m.def("begin_plot",
        [](const std::string& title_id, const ImVec2& size, ImPlotFlags flags) {
            return ImPlot::BeginPlot(title_id.c_str(), size, flags);
        },
        py::arg("title_id"), py::arg("size") = ImVec2(-1, 0), py::arg("flags") = ImPlotFlags_None
    );
    m.def("end_plot", &ImPlot::EndPlot);

    // ----- Begin/End Subplots -----
    m.def("begin_subplots",
        [](const std::string& title_id, int rows, int cols, const ImVec2& size,
           ImPlotSubplotFlags flags, std::vector<float> row_ratios, std::vector<float> col_ratios) {
            float* rr = row_ratios.empty() ? nullptr : row_ratios.data();
            float* cr = col_ratios.empty() ? nullptr : col_ratios.data();
            bool result = ImPlot::BeginSubplots(title_id.c_str(), rows, cols, size, flags, rr, cr);
            return std::make_tuple(result, row_ratios, col_ratios);
        },
        py::arg("title_id"), py::arg("rows"), py::arg("cols"), py::arg("size"),
        py::arg("flags") = ImPlotSubplotFlags_None,
        py::arg("row_ratios") = std::vector<float>{},
        py::arg("col_ratios") = std::vector<float>{}
    );
    m.def("end_subplots", &ImPlot::EndSubplots);

    // ----- Setup -----
    m.def("setup_axis",
        [](ImAxis axis, py::object label, ImPlotAxisFlags flags) {
            std::string s;
            const char* lbl = nullptr;
            if (!label.is_none()) { s = label.cast<std::string>(); lbl = s.c_str(); }
            ImPlot::SetupAxis(axis, lbl, flags);
        },
        py::arg("axis"), py::arg("label") = py::none(), py::arg("flags") = ImPlotAxisFlags_None
    );

    m.def("setup_axis_limits", &ImPlot::SetupAxisLimits,
        py::arg("axis"), py::arg("v_min"), py::arg("v_max"), py::arg("cond") = ImPlotCond_Once
    );

    // NOTE: SetupAxisLinks (external double* linkage) is not bound — it requires
    // pointer lifetimes to persist until EndPlot, which is not safely expressible
    // from Python. Use setup_axis_limits / get_plot_limits instead.

    m.def("setup_axis_format",
        [](ImAxis axis, const std::string& fmt) {
            ImPlot::SetupAxisFormat(axis, fmt.c_str());
        },
        py::arg("axis"), py::arg("fmt")
    );

    m.def("setup_axis_ticks",
        [](ImAxis axis, const std::vector<double>& values, std::vector<std::string> labels, bool keep_default) {
            std::vector<const char*> clabels = to_cstr_array(labels);
            ImPlot::SetupAxisTicks(axis, values.data(), (int)values.size(),
                                    clabels.empty() ? nullptr : clabels.data(), keep_default);
        },
        py::arg("axis"), py::arg("values"), py::arg("labels") = std::vector<std::string>{}, py::arg("keep_default") = false
    );

    m.def("setup_axis_ticks_range",
        [](ImAxis axis, double v_min, double v_max, int n_ticks, std::vector<std::string> labels, bool keep_default) {
            std::vector<const char*> clabels = to_cstr_array(labels);
            ImPlot::SetupAxisTicks(axis, v_min, v_max, n_ticks,
                                    clabels.empty() ? nullptr : clabels.data(), keep_default);
        },
        py::arg("axis"), py::arg("v_min"), py::arg("v_max"), py::arg("n_ticks"),
        py::arg("labels") = std::vector<std::string>{}, py::arg("keep_default") = false
    );

    m.def("setup_axis_scale",
        [](ImAxis axis, ImPlotScale scale) { ImPlot::SetupAxisScale(axis, scale); },
        py::arg("axis"), py::arg("scale")
    );

    // NOTE: The SetupAxisScale overload taking custom forward/inverse transform
    // callbacks is not bound in this pass.

    m.def("setup_axis_limits_constraints", &ImPlot::SetupAxisLimitsConstraints,
        py::arg("axis"), py::arg("v_min"), py::arg("v_max")
    );
    m.def("setup_axis_zoom_constraints", &ImPlot::SetupAxisZoomConstraints,
        py::arg("axis"), py::arg("z_min"), py::arg("z_max")
    );

    m.def("setup_axes",
        [](py::object x_label, py::object y_label, ImPlotAxisFlags x_flags, ImPlotAxisFlags y_flags) {
            std::string xs, ys;
            const char* xl = nullptr;
            const char* yl = nullptr;
            if (!x_label.is_none()) { xs = x_label.cast<std::string>(); xl = xs.c_str(); }
            if (!y_label.is_none()) { ys = y_label.cast<std::string>(); yl = ys.c_str(); }
            ImPlot::SetupAxes(xl, yl, x_flags, y_flags);
        },
        py::arg("x_label") = py::none(), py::arg("y_label") = py::none(),
        py::arg("x_flags") = ImPlotAxisFlags_None, py::arg("y_flags") = ImPlotAxisFlags_None
    );

    m.def("setup_axes_limits", &ImPlot::SetupAxesLimits,
        py::arg("x_min"), py::arg("x_max"), py::arg("y_min"), py::arg("y_max"), py::arg("cond") = ImPlotCond_Once
    );

    m.def("setup_legend", &ImPlot::SetupLegend,
        py::arg("location"), py::arg("flags") = ImPlotLegendFlags_None
    );
    m.def("setup_mouse_text", &ImPlot::SetupMouseText,
        py::arg("location"), py::arg("flags") = ImPlotMouseTextFlags_None
    );
    m.def("setup_finish", &ImPlot::SetupFinish);

    // ----- SetNext -----
    m.def("set_next_axis_limits", &ImPlot::SetNextAxisLimits,
        py::arg("axis"), py::arg("v_min"), py::arg("v_max"), py::arg("cond") = ImPlotCond_Once
    );

    // NOTE: SetNextAxisLinks is not bound — see note on setup_axis_links above.

    m.def("set_next_axis_to_fit", &ImPlot::SetNextAxisToFit, py::arg("axis"));
    m.def("set_next_axes_limits", &ImPlot::SetNextAxesLimits,
        py::arg("x_min"), py::arg("x_max"), py::arg("y_min"), py::arg("y_max"), py::arg("cond") = ImPlotCond_Once
    );
    m.def("set_next_axes_to_fit", &ImPlot::SetNextAxesToFit);

    // ----- Plot Items -----

    // PlotLine
    m.def("plot_line",
        [](const std::string& label_id, const std::vector<double>& values, double xscale, double xstart, const ImPlotSpec& spec) {
            ImPlot::PlotLine<double>(label_id.c_str(), values.data(), (int)values.size(), xscale, xstart, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("xscale") = 1.0, py::arg("xstart") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_line_xy",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotLine<double>(label_id.c_str(), xs.data(), ys.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_line_g",
        [](const std::string& label_id, const py::function& getter, int count, const ImPlotSpec& spec) {
            PyGetterCtx ctx{ &getter };
            ImPlot::PlotLineG(label_id.c_str(), py_getter_trampoline, &ctx, count, spec);
        },
        py::arg("label_id"), py::arg("getter"), py::arg("count"), py::arg("spec") = ImPlotSpec()
    );

    // PlotScatter
    m.def("plot_scatter",
        [](const std::string& label_id, const std::vector<double>& values, double xscale, double xstart, const ImPlotSpec& spec) {
            ImPlot::PlotScatter<double>(label_id.c_str(), values.data(), (int)values.size(), xscale, xstart, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("xscale") = 1.0, py::arg("xstart") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_scatter_xy",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotScatter<double>(label_id.c_str(), xs.data(), ys.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_scatter_g",
        [](const std::string& label_id, const py::function& getter, int count, const ImPlotSpec& spec) {
            PyGetterCtx ctx{ &getter };
            ImPlot::PlotScatterG(label_id.c_str(), py_getter_trampoline, &ctx, count, spec);
        },
        py::arg("label_id"), py::arg("getter"), py::arg("count"), py::arg("spec") = ImPlotSpec()
    );

    // PlotBubbles
    m.def("plot_bubbles",
        [](const std::string& label_id, const std::vector<double>& values, const std::vector<double>& szs,
           double xscale, double xstart, const ImPlotSpec& spec) {
            int count = (int)std::min(values.size(), szs.size());
            ImPlot::PlotBubbles<double>(label_id.c_str(), values.data(), szs.data(), count, xscale, xstart, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("szs"), py::arg("xscale") = 1.0, py::arg("xstart") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_bubbles_xy",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, const std::vector<double>& szs, const ImPlotSpec& spec) {
            int count = (int)std::min({ xs.size(), ys.size(), szs.size() });
            ImPlot::PlotBubbles<double>(label_id.c_str(), xs.data(), ys.data(), szs.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("szs"), py::arg("spec") = ImPlotSpec()
    );

    // PlotPolygon
    m.def("plot_polygon",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotPolygon<double>(label_id.c_str(), xs.data(), ys.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("spec") = ImPlotSpec()
    );

    // PlotStairs
    m.def("plot_stairs",
        [](const std::string& label_id, const std::vector<double>& values, double xscale, double xstart, const ImPlotSpec& spec) {
            ImPlot::PlotStairs<double>(label_id.c_str(), values.data(), (int)values.size(), xscale, xstart, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("xscale") = 1.0, py::arg("xstart") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_stairs_xy",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotStairs<double>(label_id.c_str(), xs.data(), ys.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_stairs_g",
        [](const std::string& label_id, const py::function& getter, int count, const ImPlotSpec& spec) {
            PyGetterCtx ctx{ &getter };
            ImPlot::PlotStairsG(label_id.c_str(), py_getter_trampoline, &ctx, count, spec);
        },
        py::arg("label_id"), py::arg("getter"), py::arg("count"), py::arg("spec") = ImPlotSpec()
    );

    // PlotShaded
    m.def("plot_shaded",
        [](const std::string& label_id, const std::vector<double>& values, double yref, double xscale, double xstart, const ImPlotSpec& spec) {
            ImPlot::PlotShaded<double>(label_id.c_str(), values.data(), (int)values.size(), yref, xscale, xstart, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("yref") = 0.0, py::arg("xscale") = 1.0, py::arg("xstart") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_shaded_xy",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, double yref, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotShaded<double>(label_id.c_str(), xs.data(), ys.data(), count, yref, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("yref") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_shaded_range",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys1, const std::vector<double>& ys2, const ImPlotSpec& spec) {
            int count = (int)std::min({ xs.size(), ys1.size(), ys2.size() });
            ImPlot::PlotShaded<double>(label_id.c_str(), xs.data(), ys1.data(), ys2.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys1"), py::arg("ys2"), py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_shaded_g",
        [](const std::string& label_id, const py::function& getter1, const py::function& getter2, int count, const ImPlotSpec& spec) {
            PyGetterCtx ctx1{ &getter1 };
            PyGetterCtx ctx2{ &getter2 };
            ImPlot::PlotShadedG(label_id.c_str(), py_getter_trampoline, &ctx1, py_getter_trampoline, &ctx2, count, spec);
        },
        py::arg("label_id"), py::arg("getter1"), py::arg("getter2"), py::arg("count"), py::arg("spec") = ImPlotSpec()
    );

    // PlotBars
    m.def("plot_bars",
        [](const std::string& label_id, const std::vector<double>& values, double bar_size, double shift, const ImPlotSpec& spec) {
            ImPlot::PlotBars<double>(label_id.c_str(), values.data(), (int)values.size(), bar_size, shift, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("bar_size") = 0.67, py::arg("shift") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_bars_xy",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, double bar_size, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotBars<double>(label_id.c_str(), xs.data(), ys.data(), count, bar_size, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("bar_size"), py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_bars_g",
        [](const std::string& label_id, const py::function& getter, int count, double bar_size, const ImPlotSpec& spec) {
            PyGetterCtx ctx{ &getter };
            ImPlot::PlotBarsG(label_id.c_str(), py_getter_trampoline, &ctx, count, bar_size, spec);
        },
        py::arg("label_id"), py::arg("getter"), py::arg("count"), py::arg("bar_size"), py::arg("spec") = ImPlotSpec()
    );

    // PlotBarGroups
    m.def("plot_bar_groups",
        [](const std::vector<std::string>& label_ids, const std::vector<double>& values,
           int item_count, int group_count, double group_size, double shift, const ImPlotSpec& spec) {
            std::vector<const char*> clabels = to_cstr_array(label_ids);
            ImPlot::PlotBarGroups<double>(clabels.data(), values.data(), item_count, group_count, group_size, shift, spec);
        },
        py::arg("label_ids"), py::arg("values"), py::arg("item_count"), py::arg("group_count"),
        py::arg("group_size") = 0.67, py::arg("shift") = 0.0, py::arg("spec") = ImPlotSpec()
    );

    // PlotErrorBars
    m.def("plot_error_bars",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, const std::vector<double>& err, const ImPlotSpec& spec) {
            int count = (int)std::min({ xs.size(), ys.size(), err.size() });
            ImPlot::PlotErrorBars<double>(label_id.c_str(), xs.data(), ys.data(), err.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("err"), py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_error_bars_asym",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys,
           const std::vector<double>& neg, const std::vector<double>& pos, const ImPlotSpec& spec) {
            int count = (int)std::min({ xs.size(), ys.size(), neg.size(), pos.size() });
            ImPlot::PlotErrorBars<double>(label_id.c_str(), xs.data(), ys.data(), neg.data(), pos.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("neg"), py::arg("pos"), py::arg("spec") = ImPlotSpec()
    );

    // PlotStems
    m.def("plot_stems",
        [](const std::string& label_id, const std::vector<double>& values, double ref, double scale, double start, const ImPlotSpec& spec) {
            ImPlot::PlotStems<double>(label_id.c_str(), values.data(), (int)values.size(), ref, scale, start, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("ref") = 0.0, py::arg("scale") = 1.0, py::arg("start") = 0.0, py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_stems_xy",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, double ref, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotStems<double>(label_id.c_str(), xs.data(), ys.data(), count, ref, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("ref") = 0.0, py::arg("spec") = ImPlotSpec()
    );

    // PlotInfLines
    m.def("plot_inf_lines",
        [](const std::string& label_id, const std::vector<double>& values, const ImPlotSpec& spec) {
            ImPlot::PlotInfLines<double>(label_id.c_str(), values.data(), (int)values.size(), spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("spec") = ImPlotSpec()
    );

    // PlotPieChart (label_fmt string variant only)
    m.def("plot_pie_chart",
        [](const std::vector<std::string>& label_ids, const std::vector<double>& values,
           double x, double y, double radius, const std::string& label_fmt, double angle0, const ImPlotSpec& spec) {
            std::vector<const char*> clabels = to_cstr_array(label_ids);
            int count = (int)std::min(label_ids.size(), values.size());
            ImPlot::PlotPieChart<double>(clabels.data(), values.data(), count, x, y, radius, label_fmt.c_str(), angle0, spec);
        },
        py::arg("label_ids"), py::arg("values"), py::arg("x"), py::arg("y"), py::arg("radius"),
        py::arg("label_fmt") = "%.1f", py::arg("angle0") = 90.0, py::arg("spec") = ImPlotSpec()
    );

    // PlotHeatmap
    m.def("plot_heatmap",
        [](const std::string& label_id, const std::vector<double>& values, int rows, int cols,
           double scale_min, double scale_max, const std::string& label_fmt,
           const ImPlotPoint& bounds_min, const ImPlotPoint& bounds_max, const ImPlotSpec& spec) {
            ImPlot::PlotHeatmap<double>(label_id.c_str(), values.data(), rows, cols, scale_min, scale_max,
                                         label_fmt.c_str(), bounds_min, bounds_max, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("rows"), py::arg("cols"),
        py::arg("scale_min") = 0.0, py::arg("scale_max") = 0.0, py::arg("label_fmt") = "%.1f",
        py::arg("bounds_min") = ImPlotPoint(0, 0), py::arg("bounds_max") = ImPlotPoint(1, 1), py::arg("spec") = ImPlotSpec()
    );

    // PlotHistogram
    m.def("plot_histogram",
        [](const std::string& label_id, const std::vector<double>& values, int bins, double bar_scale, ImPlotRange range, const ImPlotSpec& spec) {
            return ImPlot::PlotHistogram<double>(label_id.c_str(), values.data(), (int)values.size(), bins, bar_scale, range, spec);
        },
        py::arg("label_id"), py::arg("values"), py::arg("bins") = ImPlotBin_Sturges,
        py::arg("bar_scale") = 1.0, py::arg("range") = ImPlotRange(), py::arg("spec") = ImPlotSpec()
    );

    // PlotHistogram2D
    m.def("plot_histogram2d",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys,
           int x_bins, int y_bins, ImPlotRect range, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            return ImPlot::PlotHistogram2D<double>(label_id.c_str(), xs.data(), ys.data(), count, x_bins, y_bins, range, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"),
        py::arg("x_bins") = ImPlotBin_Sturges, py::arg("y_bins") = ImPlotBin_Sturges,
        py::arg("range") = ImPlotRect(), py::arg("spec") = ImPlotSpec()
    );

    // PlotDigital
    m.def("plot_digital",
        [](const std::string& label_id, const std::vector<double>& xs, const std::vector<double>& ys, const ImPlotSpec& spec) {
            int count = (int)std::min(xs.size(), ys.size());
            ImPlot::PlotDigital<double>(label_id.c_str(), xs.data(), ys.data(), count, spec);
        },
        py::arg("label_id"), py::arg("xs"), py::arg("ys"), py::arg("spec") = ImPlotSpec()
    );
    m.def("plot_digital_g",
        [](const std::string& label_id, const py::function& getter, int count, const ImPlotSpec& spec) {
            PyGetterCtx ctx{ &getter };
            ImPlot::PlotDigitalG(label_id.c_str(), py_getter_trampoline, &ctx, count, spec);
        },
        py::arg("label_id"), py::arg("getter"), py::arg("count"), py::arg("spec") = ImPlotSpec()
    );

    // PlotImage
    m.def("plot_image",
        [](const std::string& label_id,
#ifdef IMGUI_HAS_TEXTURES
           ImTextureRef tex_ref,
#else
           ImTextureID tex_ref,
#endif
           const ImPlotPoint& bounds_min, const ImPlotPoint& bounds_max,
           const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImPlotSpec& spec) {
            ImPlot::PlotImage(label_id.c_str(), tex_ref, bounds_min, bounds_max, uv0, uv1, tint_col, spec);
        },
        py::arg("label_id"), py::arg("tex_ref"), py::arg("bounds_min"), py::arg("bounds_max"),
        py::arg("uv0") = ImVec2(0, 0), py::arg("uv1") = ImVec2(1, 1),
        py::arg("tint_col") = ImVec4(1, 1, 1, 1), py::arg("spec") = ImPlotSpec()
    );

    // PlotText
    m.def("plot_text",
        [](const std::string& text, double x, double y, const ImVec2& pix_offset, const ImPlotSpec& spec) {
            ImPlot::PlotText(text.c_str(), x, y, pix_offset, spec);
        },
        py::arg("text"), py::arg("x"), py::arg("y"), py::arg("pix_offset") = ImVec2(0, 0), py::arg("spec") = ImPlotSpec()
    );

    // PlotDummy
    m.def("plot_dummy",
        [](const std::string& label_id, const ImPlotSpec& spec) {
            ImPlot::PlotDummy(label_id.c_str(), spec);
        },
        py::arg("label_id"), py::arg("spec") = ImPlotSpec()
    );

    // ----- Plot Tools -----
    m.def("drag_point",
        [](int id, double x, double y, const ImVec4& col, float size, ImPlotDragToolFlags flags) {
            bool clicked = false, hovered = false, held = false;
            bool changed = ImPlot::DragPoint(id, &x, &y, col, size, flags, &clicked, &hovered, &held);
            return std::make_tuple(changed, x, y, clicked, hovered, held);
        },
        py::arg("id"), py::arg("x"), py::arg("y"), py::arg("col"), py::arg("size") = 4.0f, py::arg("flags") = ImPlotDragToolFlags_None
    );

    m.def("drag_line_x",
        [](int id, double x, const ImVec4& col, float thickness, ImPlotDragToolFlags flags) {
            bool clicked = false, hovered = false, held = false;
            bool changed = ImPlot::DragLineX(id, &x, col, thickness, flags, &clicked, &hovered, &held);
            return std::make_tuple(changed, x, clicked, hovered, held);
        },
        py::arg("id"), py::arg("x"), py::arg("col"), py::arg("thickness") = 1.0f, py::arg("flags") = ImPlotDragToolFlags_None
    );

    m.def("drag_line_y",
        [](int id, double y, const ImVec4& col, float thickness, ImPlotDragToolFlags flags) {
            bool clicked = false, hovered = false, held = false;
            bool changed = ImPlot::DragLineY(id, &y, col, thickness, flags, &clicked, &hovered, &held);
            return std::make_tuple(changed, y, clicked, hovered, held);
        },
        py::arg("id"), py::arg("y"), py::arg("col"), py::arg("thickness") = 1.0f, py::arg("flags") = ImPlotDragToolFlags_None
    );

    m.def("drag_rect",
        [](int id, double x1, double y1, double x2, double y2, const ImVec4& col, ImPlotDragToolFlags flags) {
            bool clicked = false, hovered = false, held = false;
            bool changed = ImPlot::DragRect(id, &x1, &y1, &x2, &y2, col, flags, &clicked, &hovered, &held);
            return std::make_tuple(changed, x1, y1, x2, y2, clicked, hovered, held);
        },
        py::arg("id"), py::arg("x1"), py::arg("y1"), py::arg("x2"), py::arg("y2"), py::arg("col"), py::arg("flags") = ImPlotDragToolFlags_None
    );

    m.def("annotation",
        [](double x, double y, const ImVec4& col, const ImVec2& pix_offset, bool clamp, bool round) {
            ImPlot::Annotation(x, y, col, pix_offset, clamp, round);
        },
        py::arg("x"), py::arg("y"), py::arg("col"), py::arg("pix_offset"), py::arg("clamp"), py::arg("round") = false
    );
    m.def("annotation_text",
        [](double x, double y, const ImVec4& col, const ImVec2& pix_offset, bool clamp, const std::string& text) {
            ImPlot::Annotation(x, y, col, pix_offset, clamp, "%s", text.c_str());
        },
        py::arg("x"), py::arg("y"), py::arg("col"), py::arg("pix_offset"), py::arg("clamp"), py::arg("text")
    );

    m.def("tag_x",
        [](double x, const ImVec4& col, bool round) { ImPlot::TagX(x, col, round); },
        py::arg("x"), py::arg("col"), py::arg("round") = false
    );
    m.def("tag_x_text",
        [](double x, const ImVec4& col, const std::string& text) { ImPlot::TagX(x, col, "%s", text.c_str()); },
        py::arg("x"), py::arg("col"), py::arg("text")
    );

    m.def("tag_y",
        [](double y, const ImVec4& col, bool round) { ImPlot::TagY(y, col, round); },
        py::arg("y"), py::arg("col"), py::arg("round") = false
    );
    m.def("tag_y_text",
        [](double y, const ImVec4& col, const std::string& text) { ImPlot::TagY(y, col, "%s", text.c_str()); },
        py::arg("y"), py::arg("col"), py::arg("text")
    );

    // ----- Plot Utils -----
    m.def("set_axis", &ImPlot::SetAxis, py::arg("axis"));
    m.def("set_axes", &ImPlot::SetAxes, py::arg("x_axis"), py::arg("y_axis"));

    m.def("pixels_to_plot",
        [](const ImVec2& pix, ImAxis x_axis, ImAxis y_axis) { return ImPlot::PixelsToPlot(pix, x_axis, y_axis); },
        py::arg("pix"), py::arg("x_axis") = IMPLOT_AUTO, py::arg("y_axis") = IMPLOT_AUTO
    );
    m.def("pixels_to_plot_xy",
        [](float x, float y, ImAxis x_axis, ImAxis y_axis) { return ImPlot::PixelsToPlot(x, y, x_axis, y_axis); },
        py::arg("x"), py::arg("y"), py::arg("x_axis") = IMPLOT_AUTO, py::arg("y_axis") = IMPLOT_AUTO
    );

    m.def("plot_to_pixels",
        [](const ImPlotPoint& plt, ImAxis x_axis, ImAxis y_axis) { return ImPlot::PlotToPixels(plt, x_axis, y_axis); },
        py::arg("plt"), py::arg("x_axis") = IMPLOT_AUTO, py::arg("y_axis") = IMPLOT_AUTO
    );
    m.def("plot_to_pixels_xy",
        [](double x, double y, ImAxis x_axis, ImAxis y_axis) { return ImPlot::PlotToPixels(x, y, x_axis, y_axis); },
        py::arg("x"), py::arg("y"), py::arg("x_axis") = IMPLOT_AUTO, py::arg("y_axis") = IMPLOT_AUTO
    );

    m.def("get_plot_pos", &ImPlot::GetPlotPos);
    m.def("get_plot_size", &ImPlot::GetPlotSize);

    m.def("get_plot_mouse_pos",
        [](ImAxis x_axis, ImAxis y_axis) { return ImPlot::GetPlotMousePos(x_axis, y_axis); },
        py::arg("x_axis") = IMPLOT_AUTO, py::arg("y_axis") = IMPLOT_AUTO
    );
    m.def("get_plot_limits",
        [](ImAxis x_axis, ImAxis y_axis) { return ImPlot::GetPlotLimits(x_axis, y_axis); },
        py::arg("x_axis") = IMPLOT_AUTO, py::arg("y_axis") = IMPLOT_AUTO
    );

    m.def("is_plot_hovered", &ImPlot::IsPlotHovered);
    m.def("is_axis_hovered", &ImPlot::IsAxisHovered, py::arg("axis"));
    m.def("is_subplots_hovered", &ImPlot::IsSubplotsHovered);

    m.def("is_plot_selected", &ImPlot::IsPlotSelected);
    m.def("get_plot_selection",
        [](ImAxis x_axis, ImAxis y_axis) { return ImPlot::GetPlotSelection(x_axis, y_axis); },
        py::arg("x_axis") = IMPLOT_AUTO, py::arg("y_axis") = IMPLOT_AUTO
    );
    m.def("cancel_plot_selection", &ImPlot::CancelPlotSelection);

    m.def("hide_next_item", &ImPlot::HideNextItem, py::arg("hidden") = true, py::arg("cond") = ImPlotCond_Once);

    m.def("begin_aligned_plots",
        [](const std::string& group_id, bool vertical) { return ImPlot::BeginAlignedPlots(group_id.c_str(), vertical); },
        py::arg("group_id"), py::arg("vertical") = true
    );
    m.def("end_aligned_plots", &ImPlot::EndAlignedPlots);

    // ----- Legend Utils -----
    m.def("begin_legend_popup",
        [](const std::string& label_id, ImGuiMouseButton mouse_button) { return ImPlot::BeginLegendPopup(label_id.c_str(), mouse_button); },
        py::arg("label_id"), py::arg("mouse_button") = 1
    );
    m.def("end_legend_popup", &ImPlot::EndLegendPopup);
    m.def("is_legend_entry_hovered",
        [](const std::string& label_id) { return ImPlot::IsLegendEntryHovered(label_id.c_str()); },
        py::arg("label_id")
    );

    // ----- Drag and Drop -----
    m.def("begin_drag_drop_target_plot", &ImPlot::BeginDragDropTargetPlot);
    m.def("begin_drag_drop_target_axis", &ImPlot::BeginDragDropTargetAxis, py::arg("axis"));
    m.def("begin_drag_drop_target_legend", &ImPlot::BeginDragDropTargetLegend);
    m.def("end_drag_drop_target", &ImPlot::EndDragDropTarget);

    m.def("begin_drag_drop_source_plot", &ImPlot::BeginDragDropSourcePlot, py::arg("flags") = ImGuiDragDropFlags_None);
    m.def("begin_drag_drop_source_axis", &ImPlot::BeginDragDropSourceAxis, py::arg("axis"), py::arg("flags") = ImGuiDragDropFlags_None);
    m.def("begin_drag_drop_source_item",
        [](const std::string& label_id, ImGuiDragDropFlags flags) { return ImPlot::BeginDragDropSourceItem(label_id.c_str(), flags); },
        py::arg("label_id"), py::arg("flags") = ImGuiDragDropFlags_None
    );
    m.def("end_drag_drop_source", &ImPlot::EndDragDropSource);

    // ----- Styling -----
    m.def("get_style", &ImPlot::GetStyle, py::return_value_policy::reference);

    m.def("style_colors_auto",
        [](py::object dst) { ImPlot::StyleColorsAuto(dst.is_none() ? nullptr : &dst.cast<ImPlotStyle&>()); },
        py::arg("dst") = py::none()
    );
    m.def("style_colors_classic",
        [](py::object dst) { ImPlot::StyleColorsClassic(dst.is_none() ? nullptr : &dst.cast<ImPlotStyle&>()); },
        py::arg("dst") = py::none()
    );
    m.def("style_colors_dark",
        [](py::object dst) { ImPlot::StyleColorsDark(dst.is_none() ? nullptr : &dst.cast<ImPlotStyle&>()); },
        py::arg("dst") = py::none()
    );
    m.def("style_colors_light",
        [](py::object dst) { ImPlot::StyleColorsLight(dst.is_none() ? nullptr : &dst.cast<ImPlotStyle&>()); },
        py::arg("dst") = py::none()
    );

    m.def("push_style_color",
        [](ImPlotCol idx, const ImVec4& col) { ImPlot::PushStyleColor(idx, col); },
        py::arg("idx"), py::arg("col")
    );
    m.def("push_style_color_u32",
        [](ImPlotCol idx, ImU32 col) { ImPlot::PushStyleColor(idx, col); },
        py::arg("idx"), py::arg("col")
    );
    m.def("pop_style_color", &ImPlot::PopStyleColor, py::arg("count") = 1);

    m.def("push_style_var_float",
        [](ImPlotStyleVar idx, float val) { ImPlot::PushStyleVar(idx, val); },
        py::arg("idx"), py::arg("value")
    );
    m.def("push_style_var_int",
        [](ImPlotStyleVar idx, int val) { ImPlot::PushStyleVar(idx, val); },
        py::arg("idx"), py::arg("value")
    );
    m.def("push_style_var_vec2",
        [](ImPlotStyleVar idx, const ImVec2& val) { ImPlot::PushStyleVar(idx, val); },
        py::arg("idx"), py::arg("value")
    );
    m.def("pop_style_var", &ImPlot::PopStyleVar, py::arg("count") = 1);

    m.def("get_last_item_color", &ImPlot::GetLastItemColor);
    m.def("get_style_color_name",
        [](ImPlotCol idx) { return std::string(ImPlot::GetStyleColorName(idx)); },
        py::arg("idx")
    );
    m.def("get_marker_name",
        [](ImPlotMarker idx) { return std::string(ImPlot::GetMarkerName(idx)); },
        py::arg("idx")
    );
    m.def("next_marker", &ImPlot::NextMarker);

    // ----- Colormaps -----
    m.def("add_colormap",
        [](const std::string& name, const std::vector<ImVec4>& cols, bool qual) {
            return ImPlot::AddColormap(name.c_str(), cols.data(), (int)cols.size(), qual);
        },
        py::arg("name"), py::arg("cols"), py::arg("qual") = true
    );
    m.def("add_colormap_u32",
        [](const std::string& name, const std::vector<ImU32>& cols, bool qual) {
            return ImPlot::AddColormap(name.c_str(), cols.data(), (int)cols.size(), qual);
        },
        py::arg("name"), py::arg("cols"), py::arg("qual") = true
    );

    m.def("get_colormap_count", &ImPlot::GetColormapCount);
    m.def("get_colormap_name",
        [](ImPlotColormap cmap) -> py::object {
            const char* name = ImPlot::GetColormapName(cmap);
            return name ? py::object(py::str(name)) : py::object(py::none());
        },
        py::arg("cmap")
    );
    m.def("get_colormap_index",
        [](const std::string& name) { return ImPlot::GetColormapIndex(name.c_str()); },
        py::arg("name")
    );

    m.def("push_colormap",
        [](ImPlotColormap cmap) { ImPlot::PushColormap(cmap); },
        py::arg("cmap")
    );
    m.def("push_colormap_by_name",
        [](const std::string& name) { ImPlot::PushColormap(name.c_str()); },
        py::arg("name")
    );
    m.def("pop_colormap", &ImPlot::PopColormap, py::arg("count") = 1);

    m.def("next_colormap_color", &ImPlot::NextColormapColor);

    m.def("get_colormap_size", &ImPlot::GetColormapSize, py::arg("cmap") = IMPLOT_AUTO);
    m.def("get_colormap_color", &ImPlot::GetColormapColor, py::arg("idx"), py::arg("cmap") = IMPLOT_AUTO);
    m.def("sample_colormap", &ImPlot::SampleColormap, py::arg("t"), py::arg("cmap") = IMPLOT_AUTO);

    m.def("colormap_scale",
        [](const std::string& label, double scale_min, double scale_max, const ImVec2& size,
           const std::string& format, ImPlotColormapScaleFlags flags, ImPlotColormap cmap) {
            ImPlot::ColormapScale(label.c_str(), scale_min, scale_max, size, format.c_str(), flags, cmap);
        },
        py::arg("label"), py::arg("scale_min"), py::arg("scale_max"), py::arg("size") = ImVec2(0, 0),
        py::arg("format") = "%g", py::arg("flags") = ImPlotColormapScaleFlags_None, py::arg("cmap") = IMPLOT_AUTO
    );

    m.def("colormap_slider",
        [](const std::string& label, float t, const std::string& format, ImPlotColormap cmap) {
            ImVec4 out(0, 0, 0, 0);
            bool changed = ImPlot::ColormapSlider(label.c_str(), &t, &out, format.c_str(), cmap);
            return std::make_tuple(changed, t, out);
        },
        py::arg("label"), py::arg("t"), py::arg("format") = "", py::arg("cmap") = IMPLOT_AUTO
    );

    m.def("colormap_button",
        [](const std::string& label, const ImVec2& size, ImPlotColormap cmap) {
            return ImPlot::ColormapButton(label.c_str(), size, cmap);
        },
        py::arg("label"), py::arg("size") = ImVec2(0, 0), py::arg("cmap") = IMPLOT_AUTO
    );

    m.def("bust_color_cache",
        [](const std::string& plot_title_id) {
            ImPlot::BustColorCache(plot_title_id.empty() ? nullptr : plot_title_id.c_str());
        },
        py::arg("plot_title_id") = ""
    );

    // ----- Input Mapping -----
    m.def("get_input_map", &ImPlot::GetInputMap, py::return_value_policy::reference);
    m.def("map_input_default",
        [](py::object dst) { ImPlot::MapInputDefault(dst.is_none() ? nullptr : &dst.cast<ImPlotInputMap&>()); },
        py::arg("dst") = py::none()
    );
    m.def("map_input_reverse",
        [](py::object dst) { ImPlot::MapInputReverse(dst.is_none() ? nullptr : &dst.cast<ImPlotInputMap&>()); },
        py::arg("dst") = py::none()
    );

    // ----- Miscellaneous -----
    m.def("item_icon",
        [](const ImVec4& col) { ImPlot::ItemIcon(col); },
        py::arg("col")
    );
    m.def("item_icon_u32",
        [](ImU32 col) { ImPlot::ItemIcon(col); },
        py::arg("col")
    );
    m.def("colormap_icon", &ImPlot::ColormapIcon, py::arg("cmap"));

    m.def("get_plot_draw_list", &ImPlot::GetPlotDrawList, py::return_value_policy::reference);
    m.def("push_plot_clip_rect", &ImPlot::PushPlotClipRect, py::arg("expand") = 0.0f);
    m.def("pop_plot_clip_rect", &ImPlot::PopPlotClipRect);

    m.def("show_style_selector",
        [](const std::string& label) { return ImPlot::ShowStyleSelector(label.c_str()); },
        py::arg("label")
    );
    m.def("show_colormap_selector",
        [](const std::string& label) { return ImPlot::ShowColormapSelector(label.c_str()); },
        py::arg("label")
    );
    m.def("show_input_map_selector",
        [](const std::string& label) { return ImPlot::ShowInputMapSelector(label.c_str()); },
        py::arg("label")
    );
    m.def("show_style_editor",
        [](py::object ref) { ImPlot::ShowStyleEditor(ref.is_none() ? nullptr : &ref.cast<ImPlotStyle&>()); },
        py::arg("ref") = py::none()
    );
    m.def("show_user_guide", &ImPlot::ShowUserGuide);
    m.def("show_metrics_window",
        [](py::object p_popen) {
            if (p_popen.is_none()) {
                ImPlot::ShowMetricsWindow(nullptr);
                return py::object(py::none());
            }
            bool open = p_popen.cast<bool>();
            ImPlot::ShowMetricsWindow(&open);
            return py::object(py::bool_(open));
        },
        py::arg("p_popen") = py::none()
    );

    // ----- Demo -----
    m.def("show_demo_window",
        [](py::object p_open) {
            if (p_open.is_none()) {
                ImPlot::ShowDemoWindow(nullptr);
                return py::object(py::none());
            }
            bool open = p_open.cast<bool>();
            ImPlot::ShowDemoWindow(&open);
            return py::object(py::bool_(open));
        },
        py::arg("p_open") = py::none()
    );
}

// =====================================================================================
// [SECTION] Entry point
// =====================================================================================

void bind_implot(py::module_& m) {
    bind_implot_enums(m);
    bind_implot_structs(m);
    bind_implot_funcs(m);
}