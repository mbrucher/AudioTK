/**
* \file StandardFilters.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/BesselFilter.h>
#include <ATK/EQ/ButterworthFilter.h>

#include "MainFilter.h"
#include "StandardFilters.h"

namespace py = pybind11;

using namespace ATK;

namespace
{  
  template<typename Coefficients, typename T>
  void populate_SingleCoefficients_ripple(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("cut_frequency", &Coefficients::get_cut_frequency, &Coefficients::set_cut_frequency)
    .def_property("ripple", &Coefficients::get_ripple, &Coefficients::set_ripple)
    .def_property("order", &Coefficients::get_order, &Coefficients::set_order);
  }
  
  template<typename Coefficients, typename T>
  void populate_DualCoefficients_ripple(py::module& m, const char* type, T& parent)
  {
    typedef typename Coefficients::DataType DataType;
    py::class_<Coefficients>(m, type, parent)
    .def_property("cut_frequencies", &Coefficients::get_cut_frequencies, [](Coefficients& instance, const std::pair<DataType, DataType> f){instance.set_cut_frequencies(f);})
    .def_property("ripple", &Coefficients::get_ripple, &Coefficients::set_ripple)
    .def_property("order", &Coefficients::get_order, &Coefficients::set_order);
  }
}

void populate_StandardFilters(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2)
{
  populate_SingleCoefficients<BesselLowPassCoefficients<float>>(m, "FloatBesselLowPassCoefficients", f1);
  populate_SingleCoefficients<BesselLowPassCoefficients<double>>(m, "DoubleBesselLowPassCoefficients", f2);
  populate_SingleCoefficients<BesselHighPassCoefficients<float>>(m, "FloatBesselHighPassCoefficients", f1);
  populate_SingleCoefficients<BesselHighPassCoefficients<double>>(m, "DoubleBesselHighPassCoefficients", f2);
  populate_DualCoefficients<BesselBandPassCoefficients<float>>(m, "FloatBesselBandPassCoefficients", f1);
  populate_DualCoefficients<BesselBandPassCoefficients<double>>(m, "DoubleBesselBandPassCoefficients", f2);
  populate_DualCoefficients<BesselBandStopCoefficients<float>>(m, "FloatBesselBandStopCoefficients", f1);
  populate_DualCoefficients<BesselBandStopCoefficients<double>>(m, "DoubleBesselBandStopCoefficients", f2);
  
  populate_IIRFilter<BesselLowPassCoefficients<float>>(m, "FloatBesselLowPassFilter");
  populate_IIRFilter<BesselLowPassCoefficients<double>>(m, "DoubleBesselLowPassFilter");
  populate_IIRFilter<BesselHighPassCoefficients<float>>(m, "FloatBesselHighPassFilter");
  populate_IIRFilter<BesselHighPassCoefficients<double>>(m, "DoubleBesselHighPassFilter");
  populate_IIRFilter<BesselBandPassCoefficients<float>>(m, "FloatBesselBandPassFilter");
  populate_IIRFilter<BesselBandPassCoefficients<double>>(m, "DoubleBesselBandPassFilter");
  populate_IIRFilter<BesselBandStopCoefficients<float>>(m, "FloatBesselBandStopFilter");
  populate_IIRFilter<BesselBandStopCoefficients<double>>(m, "DoubleBesselBandStopFilter");
  
  populate_SingleCoefficients<ButterworthLowPassCoefficients<float>>(m, "FloatButterworthLowPassCoefficients", f1);
  populate_SingleCoefficients<ButterworthLowPassCoefficients<double>>(m, "DoubleButterworthLowPassCoefficients", f2);
  populate_SingleCoefficients<ButterworthHighPassCoefficients<float>>(m, "FloatButterworthHighPassCoefficients", f1);
  populate_SingleCoefficients<ButterworthHighPassCoefficients<double>>(m, "DoubleButterworthHighPassCoefficients", f2);
  populate_DualCoefficients<ButterworthBandPassCoefficients<float>>(m, "FloatButterworthBandPassCoefficients", f1);
  populate_DualCoefficients<ButterworthBandPassCoefficients<double>>(m, "DoubleButterworthBandPassCoefficients", f2);
  populate_DualCoefficients<ButterworthBandStopCoefficients<float>>(m, "FloatButterworthBandStopCoefficients", f1);
  populate_DualCoefficients<ButterworthBandStopCoefficients<double>>(m, "DoubleButterworthBandStopCoefficients", f2);
  
  populate_IIRFilter<ButterworthLowPassCoefficients<float>>(m, "FloatButterworthLowPassFilter");
  populate_IIRFilter<ButterworthLowPassCoefficients<double>>(m, "DoubleButterworthLowPassFilter");
  populate_IIRFilter<ButterworthHighPassCoefficients<float>>(m, "FloatButterworthHighPassFilter");
  populate_IIRFilter<ButterworthHighPassCoefficients<double>>(m, "DoubleButterworthHighPassFilter");
  populate_IIRFilter<ButterworthBandPassCoefficients<float>>(m, "FloatButterworthBandPassFilter");
  populate_IIRFilter<ButterworthBandPassCoefficients<double>>(m, "DoubleButterworthBandPassFilter");
  populate_IIRFilter<ButterworthBandStopCoefficients<float>>(m, "FloatButterworthBandStopFilter");
  populate_IIRFilter<ButterworthBandStopCoefficients<double>>(m, "DoubleButterworthBandStopFilter");
}
