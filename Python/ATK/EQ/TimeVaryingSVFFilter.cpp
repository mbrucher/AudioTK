/**
 * \file TimeVaryingSVFFilters.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.h>

#include "MainFilter.h"

using namespace ATK;

namespace
{
  template<typename Coefficients, typename T>
  void populate_TimeVaryingSVFCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("Q", &Coefficients::get_Q, &Coefficients::set_Q);
  }
  
  template<typename Coefficients>
  void populate_TimeVaryingSVFFilter(py::module& m, const char* type)
  {
    py::class_<TimeVaryingSecondOrderSVFFilter<Coefficients>, Coefficients>(m, type)
    .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }
}

void populate_TimeVaryingSVFFilters(pybind11::module& m,
#if ATK_ENABLE_INSTANTIATION
  const pybind11::object& f1,
#endif
  const pybind11::object& f2)
{
#if ATK_ENABLE_INSTANTIATION
  populate_TimeVaryingSVFCoefficients<TimeVaryingSecondOrderSVFBaseCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBaseCoefficients", f1);
#endif
  populate_TimeVaryingSVFCoefficients<TimeVaryingSecondOrderSVFBaseCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBaseCoefficients", f2);
  
#if ATK_ENABLE_INSTANTIATION
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFLowPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFBandPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFHighPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFNotchCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFPeakCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFPeakCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFBellCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFLowShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowSheldCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFHighShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighShelfCoefficients");
#endif
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFLowPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFBandPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFHighPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFNotchCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFPeakCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFPeakCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFBellCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowShelfCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighShelfCoefficients");

#if ATK_ENABLE_INSTANTIATION
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBandPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFNotchFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFPeakFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBellFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowSheldFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighShelfFilter");
#endif
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBandPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFNotchFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFPeakFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBellFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowShelfFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighShelfFilter");
}
