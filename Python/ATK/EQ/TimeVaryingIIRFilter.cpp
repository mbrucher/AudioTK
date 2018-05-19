/**
 * \file TimeVaryingIIRFilters.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/TimeVaryingSecondOrderFilter.h>
#include <ATK/EQ/TimeVaryingIIRFilter.h>

#include "MainFilter.h"

using namespace ATK;

namespace
{
  template<typename Coefficients, typename T>
  void populate_TimeVaryingCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("min_frequency", &Coefficients::get_min_frequency, &Coefficients::set_min_frequency)
    .def_property("max_frequency", &Coefficients::get_max_frequency, &Coefficients::set_max_frequency)
    .def_property("number_of_steps", &Coefficients::get_number_of_steps, &Coefficients::set_number_of_steps)
    .def_property("memory", &Coefficients::get_memory, &Coefficients::set_memory);
  }
  
  template<typename Coefficients>
  void populate_TimeVaryingIIRFilter(py::module& m, const char* type)
  {
    py::class_<TimeVaryingIIRFilter<Coefficients>, Coefficients>(m, type)
    .def(py::init<>());
  }
}

void populate_TimeVaryingIIRFilters(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2)
{
  populate_TimeVaryingCoefficients<TimeVaryingBaseSecondOrderCoefficients<float>>(m, "FloatTimeVaryingBaseSecondOrderCoefficients", f1);
  populate_TimeVaryingCoefficients<TimeVaryingBaseSecondOrderCoefficients<double>>(m, "DoubleTimeVaryingBaseSecondOrderCoefficients", f1);
  
  populate_QCoefficients<TimeVaryingBandPassCoefficients<float>>(m, "FloatTimeVaryingBandPassCoefficients");
  populate_QCoefficients<TimeVaryingBandPassCoefficients<double>>(m, "DoubleTimeVaryingBandPassCoefficients");
  populate_DirectCoefficients<TimeVaryingLowPassCoefficients<float>>(m, "FloatTimeVaryingLowPassCoefficients");
  populate_DirectCoefficients<TimeVaryingLowPassCoefficients<double>>(m, "DoubleTimeVaryingLowPassCoefficients");
  populate_DirectCoefficients<TimeVaryingHighPassCoefficients<float>>(m, "FloatTimeVaryingHighPassCoefficients");
  populate_DirectCoefficients<TimeVaryingHighPassCoefficients<double>>(m, "DoubleTimeVaryingHighPassCoefficients");
  populate_QshelfCoefficients<TimeVaryingBandPassPeakCoefficients<float>>(m, "FloatTimeVaryingBandPassPeakCoefficients");
  populate_QshelfCoefficients<TimeVaryingBandPassPeakCoefficients<double>>(m, "DoubleTimeVaryingBandPassPeakCoefficients");
  populate_QCoefficients<TimeVaryingAllPassCoefficients<float>>(m, "FloatTimeVaryingAllPassCoefficients");
  populate_QCoefficients<TimeVaryingAllPassCoefficients<double>>(m, "DoubleTimeVaryingAllPassCoefficients");
  populate_shelfCoefficients<TimeVaryingLowShelvingCoefficients<float>>(m, "FloatTimeVaryingLowShelvingCoefficients");
  populate_shelfCoefficients<TimeVaryingLowShelvingCoefficients<double>>(m, "DoubleTimeVaryingLowShelvingCoefficients");
  populate_shelfCoefficients<TimeVaryingHighShelvingCoefficients<float>>(m, "FloatTimeVaryingHighShelvingCoefficients");
  populate_shelfCoefficients<TimeVaryingHighShelvingCoefficients<double>>(m, "DoubleTimeVaryingHighShelvingCoefficients");
  
  populate_TimeVaryingIIRFilter<TimeVaryingBandPassCoefficients<float>>(m, "FloatTimeVaryingBandPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingBandPassCoefficients<double>>(m, "DoubleTimeVaryingBandPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingLowPassCoefficients<float>>(m, "FloatTimeVaryingLowPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingLowPassCoefficients<double>>(m, "DoubleTimeVaryingLowPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingHighPassCoefficients<float>>(m, "FloatTimeVaryingHighPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingHighPassCoefficients<double>>(m, "DoubleTimeVaryingHighPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingBandPassPeakCoefficients<float>>(m, "FloatTimeVaryingBandPassPeakFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingBandPassPeakCoefficients<double>>(m, "DoubleTimeVaryingBandPassPeakFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingAllPassCoefficients<float>>(m, "FloatTimeVaryingAllPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingAllPassCoefficients<double>>(m, "DoubleTimeVaryingAllPassFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingLowShelvingCoefficients<float>>(m, "FloatTimeVaryingLowShelvingFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingLowShelvingCoefficients<double>>(m, "DoubleTimeVaryingLowShelvingFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingHighShelvingCoefficients<float>>(m, "FloatTimeVaryingHighShelvingFilter");
  populate_TimeVaryingIIRFilter<TimeVaryingHighShelvingCoefficients<double>>(m, "DoubleTimeVaryingHighShelvingFilter");
}
