/**
* \file Delay.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonDelay) {
  py::module m("PythonDelay", "Audio ToolKit Delay module");


  return m.ptr();
}
