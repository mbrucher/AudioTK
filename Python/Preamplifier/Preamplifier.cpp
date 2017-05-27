/**
* \file Preamplifier.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonPreamplifier) {
  py::module m("PythonPreamplifier", "Audio ToolKit Preamplifier module");


  return m.ptr();
}
