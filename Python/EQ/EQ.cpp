/**
* \file EQ.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonEQ) {
  py::module m("PythonEQ", "Audio ToolKit EQ module");


  return m.ptr();
}
