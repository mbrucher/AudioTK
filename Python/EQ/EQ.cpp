/**
* \file EQ.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/SecondOrderFilter.h>

namespace py = pybind11;

using namespace ATK;
using namespace py::literals;

namespace
{
  template<typename Coefficients>
  void populate_IIRFilter(py::module& m, const char* type)
  {
    typedef typename Coefficients::DataType DataType;
    py::class_<IIRFilter<Coefficients>, Coefficients>(m, type)
      .def(py::init<std::size_t>(), "nb_channels"_a = 1)
      .def_property_readonly("coefficients_in", &IIRFilter<Coefficients>::get_coefficients_in)
      .def_property_readonly("coefficients_out", &IIRFilter<Coefficients>::get_coefficients_out);
  }

  template<typename Coefficients>
  void populate_2ndOrderCoefficients(py::module& m, const char* type)
  {
    typedef typename Coefficients::DataType DataType;
    py::class_<Coefficients, TypedBaseFilter<DataType>>(m, type)
      .def_property("cut_frequency", &Coefficients::get_cut_frequency, &Coefficients::set_cut_frequency);
  }

  template<typename Coefficients>
  void populate_SecondOrderBandPassCoefficients(py::module& m, const char* type)
  {
    py::class_<Coefficients, typename Coefficients::Parent>(m, type)
    .def_property("Q", &Coefficients::get_Q, &Coefficients::set_Q);
  }
}

PYBIND11_PLUGIN(PythonEQ) {
  py::module m("PythonEQ", "Audio ToolKit EQ module");

  populate_2ndOrderCoefficients<SecondOrderBaseCoefficients<float>>(m, "FloatSecondOrderBaseCoefficients");
  populate_2ndOrderCoefficients<SecondOrderBaseCoefficients<double>>(m, "DoubleSecondOrderBaseCoefficients");

  populate_SecondOrderBandPassCoefficients<SecondOrderBandPassCoefficients<float>>(m, "FloatSecondOrderBandPassCoefficients");
  populate_SecondOrderBandPassCoefficients<SecondOrderBandPassCoefficients<double>>(m, "DoubleSecondOrderBandPassCoefficients");

  populate_IIRFilter<SecondOrderBandPassCoefficients<float>>(m, "FloatSecondOrderBandPassFilter");
  populate_IIRFilter<SecondOrderBandPassCoefficients<double>>(m, "DoubleSecondOrderBandPassFilter");

  return m.ptr();
}
