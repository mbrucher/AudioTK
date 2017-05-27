/**
* \file Special.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonSpecial) {
  py::module m("PythonSpecial", "Audio ToolKit Special module");


  return m.ptr();
}
