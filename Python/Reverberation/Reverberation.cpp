/**
* \file Reverberation.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>

namespace py = pybind11;

using namespace ATK;

PYBIND11_PLUGIN(PythonReverberation) {
  py::module m("PythonReverberation", "Audio ToolKit Reverberation module");


  return m.ptr();
}
