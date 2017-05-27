/**
* \file Tools.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonTools) {
  py::module m("PythonTools", "Audio ToolKit Tools module");

  return m.ptr();
}
