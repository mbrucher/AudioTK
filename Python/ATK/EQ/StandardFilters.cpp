/**
* \file StandardFilters.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/BesselFilter.h>
#include <ATK/EQ/ButterworthFilter.h>
#include <ATK/EQ/Chebyshev1Filter.h>
#include <ATK/EQ/Chebyshev2Filter.h>

#include "MainFilter.h"
#include "StandardFilters.h"

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename Coefficients, typename T>
  void populate_SingleCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("cut_frequency", &Coefficients::get_cut_frequency, &Coefficients::set_cut_frequency)
    .def_property("order", &Coefficients::get_order, &Coefficients::set_order);
  }
  
  template<typename Coefficients, typename T>
  void populate_DualCoefficients(py::module& m, const char* type, T& parent)
  {
    typedef typename Coefficients::DataType DataType;
    py::class_<Coefficients>(m, type, parent)
    .def_property("cut_frequencies", &Coefficients::get_cut_frequencies, [](Coefficients& instance, const std::pair<DataType, DataType> f){instance.set_cut_frequencies(f);})
    .def_property("order", &Coefficients::get_order, &Coefficients::set_order);
  }
  
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
  
  populate_SingleCoefficients_ripple<Chebyshev1LowPassCoefficients<float>>(m, "FloatChebyshev1LowPassCoefficients", f1);
  populate_SingleCoefficients_ripple<Chebyshev1LowPassCoefficients<double>>(m, "DoubleChebyshev1LowPassCoefficients", f2);
  populate_SingleCoefficients_ripple<Chebyshev1HighPassCoefficients<float>>(m, "FloatChebyshev1HighPassCoefficients", f1);
  populate_SingleCoefficients_ripple<Chebyshev1HighPassCoefficients<double>>(m, "DoubleChebyshev1HighPassCoefficients", f2);
  populate_DualCoefficients_ripple<Chebyshev1BandPassCoefficients<float>>(m, "FloatChebyshev1BandPassCoefficients", f1);
  populate_DualCoefficients_ripple<Chebyshev1BandPassCoefficients<double>>(m, "DoubleChebyshev1BandPassCoefficients", f2);
  populate_DualCoefficients_ripple<Chebyshev1BandStopCoefficients<float>>(m, "FloatChebyshev1BandStopCoefficients", f1);
  populate_DualCoefficients_ripple<Chebyshev1BandStopCoefficients<double>>(m, "DoubleChebyshev1BandStopCoefficients", f2);
  
  populate_IIRFilter<Chebyshev1LowPassCoefficients<float>>(m, "FloatChebyshev1LowPassFilter");
  populate_IIRFilter<Chebyshev1LowPassCoefficients<double>>(m, "DoubleChebyshev1LowPassFilter");
  populate_IIRFilter<Chebyshev1HighPassCoefficients<float>>(m, "FloatChebyshev1HighPassFilter");
  populate_IIRFilter<Chebyshev1HighPassCoefficients<double>>(m, "DoubleChebyshev1HighPassFilter");
  populate_IIRFilter<Chebyshev1BandPassCoefficients<float>>(m, "FloatChebyshev1BandPassFilter");
  populate_IIRFilter<Chebyshev1BandPassCoefficients<double>>(m, "DoubleChebyshev1BandPassFilter");
  populate_IIRFilter<Chebyshev1BandStopCoefficients<float>>(m, "FloatChebyshev1BandStopFilter");
  populate_IIRFilter<Chebyshev1BandStopCoefficients<double>>(m, "DoubleChebyshev1BandStopFilter");
  
  populate_SingleCoefficients_ripple<Chebyshev2LowPassCoefficients<float>>(m, "FloatChebyshev2LowPassCoefficients", f1);
  populate_SingleCoefficients_ripple<Chebyshev2LowPassCoefficients<double>>(m, "DoubleChebyshev2LowPassCoefficients", f2);
  populate_SingleCoefficients_ripple<Chebyshev2HighPassCoefficients<float>>(m, "FloatChebyshev2HighPassCoefficients", f1);
  populate_SingleCoefficients_ripple<Chebyshev2HighPassCoefficients<double>>(m, "DoubleChebyshev2HighPassCoefficients", f2);
  populate_DualCoefficients_ripple<Chebyshev2BandPassCoefficients<float>>(m, "FloatChebyshev2BandPassCoefficients", f1);
  populate_DualCoefficients_ripple<Chebyshev2BandPassCoefficients<double>>(m, "DoubleChebyshev2BandPassCoefficients", f2);
  populate_DualCoefficients_ripple<Chebyshev2BandStopCoefficients<float>>(m, "FloatChebyshev2BandStopCoefficients", f1);
  populate_DualCoefficients_ripple<Chebyshev2BandStopCoefficients<double>>(m, "DoubleChebyshev2BandStopCoefficients", f2);
  
  populate_IIRFilter<Chebyshev2LowPassCoefficients<float>>(m, "FloatChebyshev2LowPassFilter");
  populate_IIRFilter<Chebyshev2LowPassCoefficients<double>>(m, "DoubleChebyshev2LowPassFilter");
  populate_IIRFilter<Chebyshev2HighPassCoefficients<float>>(m, "FloatChebyshev2HighPassFilter");
  populate_IIRFilter<Chebyshev2HighPassCoefficients<double>>(m, "DoubleChebyshev2HighPassFilter");
  populate_IIRFilter<Chebyshev2BandPassCoefficients<float>>(m, "FloatChebyshev2BandPassFilter");
  populate_IIRFilter<Chebyshev2BandPassCoefficients<double>>(m, "DoubleChebyshev2BandPassFilter");
  populate_IIRFilter<Chebyshev2BandStopCoefficients<float>>(m, "FloatChebyshev2BandStopFilter");
  populate_IIRFilter<Chebyshev2BandStopCoefficients<double>>(m, "DoubleChebyshev2BandStopFilter");
}
