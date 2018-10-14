/**
 * \file SecondOrderFilter.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/SecondOrderFilter.h>

#include "MainFilter.h"

using namespace ATK;

void populate_SecondOrderFilter(pybind11::module& m,
#if ATK_ENABLE_INSTANTIATION
  const pybind11::object& f1,
#endif
  const pybind11::object& f2)
{
#if ATK_ENABLE_INSTANTIATION
  populate_ndOrderCoefficients<SecondOrderBaseCoefficients<float>>(m, "FloatSecondOrderBaseCoefficients", f1);
#endif
  populate_ndOrderCoefficients<SecondOrderBaseCoefficients<double>>(m, "DoubleSecondOrderBaseCoefficients", f2);

#if ATK_ENABLE_INSTANTIATION
  populate_QCoefficients<SecondOrderBandPassCoefficients<float>>(m, "FloatSecondOrderBandPassCoefficients");
  populate_DirectCoefficients<SecondOrderLowPassCoefficients<float>>(m, "FloatSecondOrderLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderHighPassCoefficients<float>>(m, "FloatSecondOrderHighPassCoefficients");
  populate_QshelfCoefficients<SecondOrderBandPassPeakCoefficients<float>>(m, "FloatSecondOrderBandPassPeakCoefficients");
  populate_QCoefficients<SecondOrderAllPassCoefficients<float>>(m, "FloatSecondOrderAllPassCoefficients");
  populate_shelfCoefficients<SecondOrderLowShelvingCoefficients<float>>(m, "FloatSecondOrderLowShelvingCoefficients");
  populate_shelfCoefficients<SecondOrderHighShelvingCoefficients<float>>(m, "FloatSecondOrderHighShelvingCoefficients");
#endif
  populate_QCoefficients<SecondOrderBandPassCoefficients<double>>(m, "DoubleSecondOrderBandPassCoefficients");
  populate_DirectCoefficients<SecondOrderLowPassCoefficients<double>>(m, "DoubleSecondOrderLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderHighPassCoefficients<double>>(m, "DoubleSecondOrderHighPassCoefficients");
  populate_QshelfCoefficients<SecondOrderBandPassPeakCoefficients<double>>(m, "DoubleSecondOrderBandPassPeakCoefficients");
  populate_QCoefficients<SecondOrderAllPassCoefficients<double>>(m, "DoubleSecondOrderAllPassCoefficients");
  populate_shelfCoefficients<SecondOrderLowShelvingCoefficients<double>>(m, "DoubleSecondOrderLowShelvingCoefficients");
  populate_shelfCoefficients<SecondOrderHighShelvingCoefficients<double>>(m, "DoubleSecondOrderHighShelvingCoefficients");

#if ATK_ENABLE_INSTANTIATION
  populate_IIRFilter<SecondOrderBandPassCoefficients<float>>(m, "FloatSecondOrderBandPassFilter");
  populate_IIRFilter<SecondOrderLowPassCoefficients<float>>(m, "FloatSecondOrderLowPassFilter");
  populate_IIRFilter<SecondOrderHighPassCoefficients<float>>(m, "FloatSecondOrderHighPassFilter");
  populate_IIRFilter<SecondOrderBandPassPeakCoefficients<float>>(m, "FloatSecondOrderBandPassPeakFilter");
  populate_IIRFilter<SecondOrderAllPassCoefficients<float>>(m, "FloatSecondOrderAllPassFilter");
  populate_IIRFilter<SecondOrderLowShelvingCoefficients<float>>(m, "FloatSecondOrderLowShelvingFilter");
  populate_IIRFilter<SecondOrderHighShelvingCoefficients<float>>(m, "FloatSecondOrderHighShelvingFilter");
#endif
  populate_IIRFilter<SecondOrderBandPassCoefficients<double>>(m, "DoubleSecondOrderBandPassFilter");
  populate_IIRFilter<SecondOrderLowPassCoefficients<double>>(m, "DoubleSecondOrderLowPassFilter");
  populate_IIRFilter<SecondOrderHighPassCoefficients<double>>(m, "DoubleSecondOrderHighPassFilter");
  populate_IIRFilter<SecondOrderBandPassPeakCoefficients<double>>(m, "DoubleSecondOrderBandPassPeakFilter");
  populate_IIRFilter<SecondOrderAllPassCoefficients<double>>(m, "DoubleSecondOrderAllPassFilter");
  populate_IIRFilter<SecondOrderLowShelvingCoefficients<double>>(m, "DoubleSecondOrderLowShelvingFilter");
  populate_IIRFilter<SecondOrderHighShelvingCoefficients<double>>(m, "DoubleSecondOrderHighShelvingFilter");
}
