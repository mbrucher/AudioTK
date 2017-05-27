/**
* \file Distortion.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonDistortion) {
  py::module m("PythonDistortion", "Audio ToolKit Distortion module");


  return m.ptr();
}
