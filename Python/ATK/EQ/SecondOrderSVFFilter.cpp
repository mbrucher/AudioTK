/**
 * \file SecondOrderSVFFilter.cpp
*/

#include <gsl/gsl>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/SecondOrderSVFFilter.h>

#include "MainFilter.h"

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
    .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }
}

void populate_SecondOrderSVFFilter(pybind11::module& m,
#if ATK_ENABLE_INSTANTIATION
  const pybind11::object& f1,
#endif
  const pybind11::object& f2)
{
#if ATK_ENABLE_INSTANTIATION
  populate_SVFCoefficients<SecondOrderSVFBaseCoefficients<float>>(m, "FloatSecondOrderSVFBaseCoefficients", f1);
#endif
  populate_SVFCoefficients<SecondOrderSVFBaseCoefficients<double>>(m, "DoubleSecondOrderSVFBaseCoefficients", f2);
  
#if ATK_ENABLE_INSTANTIATION
  populate_DirectCoefficients<SecondOrderSVFLowPassCoefficients<float>>(m, "FloatSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFBandPassCoefficients<float>>(m, "FloatSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFHighPassCoefficients<float>>(m, "FloatSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFNotchCoefficients<float>>(m, "FloatSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<SecondOrderSVFPeakCoefficients<float>>(m, "FloatSecondOrderSVFPeakCoefficients");
  populate_DirectCoefficients<SecondOrderSVFBellCoefficients<float>>(m, "FloatSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<SecondOrderSVFLowShelfCoefficients<float>>(m, "FloatSecondOrderSVFLowShelfCoefficients");
  populate_shelfCoefficients<SecondOrderSVFHighShelfCoefficients<float>>(m, "FloatSecondOrderSVFHighShelfCoefficients");
#endif
  populate_DirectCoefficients<SecondOrderSVFLowPassCoefficients<double>>(m, "DoubleSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFBandPassCoefficients<double>>(m, "DoubleSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFHighPassCoefficients<double>>(m, "DoubleSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<SecondOrderSVFNotchCoefficients<double>>(m, "DoubleSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<SecondOrderSVFPeakCoefficients<double>>(m, "DoubleSecondOrderSVFPeakCoefficients");
  populate_shelfCoefficients<SecondOrderSVFBellCoefficients<double>>(m, "DoubleSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<SecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleSecondOrderSVFLowShelfCoefficients");
  populate_shelfCoefficients<SecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleSecondOrderSVFHighShelfCoefficients");

#if ATK_ENABLE_INSTANTIATION
  populate_SVFFilter<SecondOrderSVFLowPassCoefficients<float>>(m, "FloatSecondOrderSVFLowPassFilter");
  populate_SVFFilter<SecondOrderSVFBandPassCoefficients<float>>(m, "FloatSecondOrderSVFBandPassFilter");
  populate_SVFFilter<SecondOrderSVFHighPassCoefficients<float>>(m, "FloatSecondOrderSVFHighPassFilter");
  populate_SVFFilter<SecondOrderSVFNotchCoefficients<float>>(m, "FloatSecondOrderSVFNotchFilter");
  populate_SVFFilter<SecondOrderSVFPeakCoefficients<float>>(m, "FloatSecondOrderSVFPeakFilter");
  populate_SVFFilter<SecondOrderSVFBellCoefficients<float>>(m, "FloatSecondOrderSVFBellFilter");
  populate_SVFFilter<SecondOrderSVFLowShelfCoefficients<float>>(m, "FloatSecondOrderSVFLowShelfFilter");
  populate_SVFFilter<SecondOrderSVFHighShelfCoefficients<float>>(m, "FloatSecondOrderSVFHighShelfFilter");
#endif
  populate_SVFFilter<SecondOrderSVFLowPassCoefficients<double>>(m, "DoubleSecondOrderSVFLowPassFilter");
  populate_SVFFilter<SecondOrderSVFBandPassCoefficients<double>>(m, "DoubleSecondOrderSVFBandPassFilter");
  populate_SVFFilter<SecondOrderSVFHighPassCoefficients<double>>(m, "DoubleSecondOrderSVFHighPassFilter");
  populate_SVFFilter<SecondOrderSVFNotchCoefficients<double>>(m, "DoubleSecondOrderSVFNotchFilter");
  populate_SVFFilter<SecondOrderSVFPeakCoefficients<double>>(m, "DoubleSecondOrderSVFPeakFilter");
  populate_SVFFilter<SecondOrderSVFBellCoefficients<double>>(m, "DoubleSecondOrderSVFBellFilter");
  populate_SVFFilter<SecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleSecondOrderSVFLowShelfFilter");
  populate_SVFFilter<SecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleSecondOrderSVFHighShelfFilter");
}
