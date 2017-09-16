/**
* \file Special.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Special/ConvolutionFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType, typename T>
  void populate_ConvolutionFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<ConvolutionFilter<DataType>>(m, type, parent)
    .def(py::init<>())
    .def("set_impulse", &ConvolutionFilter<DataType>::set_impulse)
    .def("set_split_size", &ConvolutionFilter<DataType>::set_split_size)
    ;
  }
}
PYBIND11_MODULE(PythonSpecial) {
  py::module m("PythonSpecial", "Audio ToolKit Special module");

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");

  populate_ConvolutionFilter<double>(m, "DoubleConvolutionFilter", f2);
  
  return m.ptr();
}
