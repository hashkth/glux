#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "imgui.h"
#include "implot.h"

namespace py = pybind11;

// Binds all ImPlot enums/flags (ImAxis_, ImPlotFlags_, ImPlotCol_, etc.)
void bind_implot_enums(py::module_& m);

// Binds all ImPlot plain-data structs (ImPlotPoint, ImPlotRange, ImPlotRect,
// ImPlotSpec, ImPlotStyle, ImPlotInputMap, ImPlotContext).
void bind_implot_structs(py::module_& m);

// Binds all free ImPlot functions (Begin/EndPlot, Setup*, Plot*, styling, colormaps, etc.).
void bind_implot_funcs(py::module_& m);

// Convenience helper that calls all of the above in the correct order.
void bind_implot(py::module_& m);