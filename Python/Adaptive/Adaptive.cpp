/**
 * \file Adaptive.cpp
 */

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonAdaptive) {
  py::module m("PythonAdaptive", "Audio ToolKit Adaptive module");


  return m.ptr();
}
