/**
 * \file SecondOrderSVFFilter.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/SecondOrderSVFFilter.h>

#include "MainFilter.h"

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename Coefficients, typename T>
  void populate_SVFCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("cut_frequency", &Coefficients::get_cut_frequency, &Coefficients::set_cut_frequency)
    .def_property("Q", &Coefficients::get_Q, &Coefficients::set_Q);
  }
  
  template<typename Coefficients>
  void populate_SVFFilter(py::module& m, const char* type)
  {
    py::class_<SecondOrderSVFFilter<Coefficients>, Coefficients>(m, type)
    .def(py::init<std::size_t>(), "nb_channels"_a = 1);
  }
}

void populate_SecondOrderSVFFilter(py::module& m, const py::object& f1, const py::object& f2)
{
  populate_SVFCoefficients<SecondOrderSVFBaseCoefficients<float>>(m, "FloatSecondOrderSVFBaseCoefficients", f1);
  populate_SVFCoefficients<SecondOrderSVFBaseCoefficients<double>>(m, "DoubleSecondOrderSVFBaseCoefficients", f2);
  
  populate_DirectCoefficients<SecondOrderSVFLowPassCoefficients<float>>(m, "FloatSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFLowPassCoefficients<double>>(m, "DoubleSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFBandPassCoefficients<float>>(m, "FloatSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFBandPassCoefficients<double>>(m, "DoubleSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFHighPassCoefficients<float>>(m, "FloatSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFHighPassCoefficients<double>>(m, "DoubleSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFNotchCoefficients<float>>(m, "FloatSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<SecondOrderSVFNotchCoefficients<double>>(m, "DoubleSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<SecondOrderSVFPeakCoefficients<float>>(m, "FloatSecondOrderSVFPeakCoefficients");
  populate_DirectCoefficients<SecondOrderSVFPeakCoefficients<double>>(m, "DoubleSecondOrderSVFPeakCoefficients");
  populate_DirectCoefficients<SecondOrderSVFBellCoefficients<float>>(m, "FloatSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<SecondOrderSVFBellCoefficients<double>>(m, "DoubleSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<SecondOrderSVFLowShelfCoefficients<float>>(m, "FloatSecondOrderSVFLowShelfCoefficients");
  populate_shelfCoefficients<SecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleSecondOrderSVFLowShelfCoefficients");
  populate_shelfCoefficients<SecondOrderSVFHighShelfCoefficients<float>>(m, "FloatSecondOrderSVFHighShelfCoefficients");
  populate_shelfCoefficients<SecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleSecondOrderSVFHighShelfCoefficients");
  
  populate_SVFFilter<SecondOrderSVFLowPassCoefficients<float>>(m, "FloatSecondOrderSVFLowPassFilter");
  populate_SVFFilter<SecondOrderSVFLowPassCoefficients<double>>(m, "DoubleSecondOrderSVFLowPassFilter");
  populate_SVFFilter<SecondOrderSVFBandPassCoefficients<float>>(m, "FloatSecondOrderSVFBandPassFilter");
  populate_SVFFilter<SecondOrderSVFBandPassCoefficients<double>>(m, "DoubleSecondOrderSVFBandPassFilter");
  populate_SVFFilter<SecondOrderSVFHighPassCoefficients<float>>(m, "FloatSecondOrderSVFHighPassFilter");
  populate_SVFFilter<SecondOrderSVFHighPassCoefficients<double>>(m, "DoubleSecondOrderSVFHighPassFilter");
  populate_SVFFilter<SecondOrderSVFNotchCoefficients<float>>(m, "FloatSecondOrderSVFNotchFilter");
  populate_SVFFilter<SecondOrderSVFNotchCoefficients<double>>(m, "DoubleSecondOrderSVFNotchFilter");
  populate_SVFFilter<SecondOrderSVFPeakCoefficients<float>>(m, "FloatSecondOrderSVFPeakFilter");
  populate_SVFFilter<SecondOrderSVFPeakCoefficients<double>>(m, "DoubleSecondOrderSVFPeakFilter");
  populate_SVFFilter<SecondOrderSVFBellCoefficients<float>>(m, "FloatSecondOrderSVFBellFilter");
  populate_SVFFilter<SecondOrderSVFBellCoefficients<double>>(m, "DoubleSecondOrderSVFBellFilter");
  populate_SVFFilter<SecondOrderSVFLowShelfCoefficients<float>>(m, "FloatSecondOrderSVFLowShelfFilter");
  populate_SVFFilter<SecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleSecondOrderSVFLowShelfFilter");
  populate_SVFFilter<SecondOrderSVFHighShelfCoefficients<float>>(m, "FloatSecondOrderSVFHighShelfFilter");
  populate_SVFFilter<SecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleSecondOrderSVFHighShelfFilter");
}
