/**
* \file EQ.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/BesselFilter.h>
#include <ATK/EQ/ButterworthFilter.h>
#include <ATK/EQ/Chebyshev1Filter.h>
#include <ATK/EQ/Chebyshev2Filter.h>
#include <ATK/EQ/CustomIIRFilter.h>
#include <ATK/EQ/FourthOrderFilter.h>
#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/LinkwitzRileyFilter.h>
#include <ATK/EQ/PedalToneStackFilter.h>
#include <ATK/EQ/RIAAFilter.h>
#include <ATK/EQ/RobertBristowJohnsonFilter.h>
#include <ATK/EQ/SecondOrderFilter.h>
#include <ATK/EQ/ToneStackFilter.h>

#include <ATK/EQ/CustomFIRFilter.h>
#include <ATK/EQ/FIRFilter.h>

#include <ATK/EQ/SecondOrderSVFFilter.h>

#include <ATK/EQ/TimeVaryingIIRFilter.h>
#include <ATK/EQ/TimeVaryingSecondOrderFilter.h>
#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.h>

namespace py = pybind11;

using namespace ATK;
using namespace py::literals;

namespace
{
  template<typename Coefficients>
  void populate_FIRFilter(py::module& m, const char* type)
  {
    py::class_<FIRFilter<Coefficients>, Coefficients>(m, type)
    .def(py::init<std::size_t>(), "nb_channels"_a = 1)
    .def_property_readonly("coefficients_in", &FIRFilter<Coefficients>::get_coefficients_in);
  }
  
  template<typename DataType, typename T>
  void populate_CustomFIR(py::module& m, const char* type, T& parent)
  {
    py::class_<CustomFIRCoefficients<DataType>>(m, type, parent)
    .def("set_coefficients_in", &CustomFIRCoefficients<DataType>::set_coefficients_in);
  }

  template<typename Coefficients>
  void populate_IIRFilter(py::module& m, const char* type)
  {
    py::class_<IIRFilter<Coefficients>, Coefficients>(m, type)
      .def(py::init<std::size_t>(), "nb_channels"_a = 1)
      .def_property_readonly("coefficients_in", &IIRFilter<Coefficients>::get_coefficients_in)
      .def_property_readonly("coefficients_out", &IIRFilter<Coefficients>::get_coefficients_out);
  }
  
  template<typename DataType, typename T>
  void populate_CustomIIR(py::module& m, const char* type, T& parent)
  {
    py::class_<CustomIIRCoefficients<DataType>>(m, type, parent)
    .def("set_coefficients_in", &CustomIIRCoefficients<DataType>::set_coefficients_in)
    .def("set_coefficients_out", &CustomIIRCoefficients<DataType>::set_coefficients_out);
  }

  template<typename Coefficients, typename T>
  void populate_EmptyCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent);
  }

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

  template<typename Coefficients, typename T>
  void populate_ndOrderCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("cut_frequency", &Coefficients::get_cut_frequency, &Coefficients::set_cut_frequency);
  }

  template<typename Coefficients>
  void populate_DirectCoefficients(py::module& m, const char* type)
  {
    py::class_<Coefficients, typename Coefficients::Parent>(m, type);
  }

  template<typename Coefficients>
  void populate_QCoefficients(py::module& m, const char* type)
  {
    py::class_<Coefficients, typename Coefficients::Parent>(m, type)
    .def_property("Q", &Coefficients::get_Q, &Coefficients::set_Q);
  }
  
  template<typename Coefficients>
  void populate_shelfCoefficients(py::module& m, const char* type)
  {
    py::class_<Coefficients, typename Coefficients::Parent>(m, type)
    .def_property("gain", &Coefficients::get_gain, &Coefficients::set_gain);
  }
  
  template<typename Coefficients>
  void populate_QshelfCoefficients(py::module& m, const char* type)
  {
    py::class_<Coefficients, typename Coefficients::Parent>(m, type)
    .def_property("Q", &Coefficients::get_Q, &Coefficients::set_Q)
    .def_property("gain", &Coefficients::get_gain, &Coefficients::set_gain);
  }
  
  template<typename Coefficients, typename T>
  void populate_PedalCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("tone", &Coefficients::get_tone, &Coefficients::set_tone);
  }
  
  template<typename Coefficients, typename T>
  void populate_StackCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("low", &Coefficients::get_low, &Coefficients::set_low)
    .def_property("middle", &Coefficients::get_middle, &Coefficients::set_middle)
    .def_property("high", &Coefficients::get_high, &Coefficients::set_high);
  }
  
  template<typename Coefficients>
  void populate_StackFilter(py::module& m, const char* type)
  {
    py::class_<IIRFilter<Coefficients>, Coefficients>(m, type)
    .def_property_readonly("coefficients_in", &IIRFilter<Coefficients>::get_coefficients_in)
    .def_property_readonly("coefficients_out", &IIRFilter<Coefficients>::get_coefficients_out)
    .def_static("build_Bassman_stack", &Coefficients::buildBassmanStack)
    .def_static("build_JCM800_stack", &Coefficients::buildJCM800Stack);
  }
  
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
    .def(py::init<std::size_t>(), "nb_channels"_a = 1);
  }
}

PYBIND11_PLUGIN(PythonEQ) {
  py::module m("PythonEQ", "Audio ToolKit EQ module");

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");

  populate_CustomFIR<float>(m, "FloatCustomFIRCoefficients", f1);
  populate_CustomFIR<double>(m, "DoubleCustomFIRCoefficients", f2);
  
  populate_FIRFilter<CustomFIRCoefficients<float>>(m, "FloatCustomFIRFilter");
  populate_FIRFilter<CustomFIRCoefficients<double>>(m, "DoubleCustomFIRFilter");

  populate_CustomIIR<float>(m, "FloatCustomIIRCoefficients", f1);
  populate_CustomIIR<double>(m, "DoubleCustomIIRCoefficients", f2);
  
  populate_IIRFilter<CustomIIRCoefficients<float>>(m, "FloatCustomIIRFilter");
  populate_IIRFilter<CustomIIRCoefficients<double>>(m, "DoubleCustomIIRFilter");

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

  populate_ndOrderCoefficients<SecondOrderBaseCoefficients<float>>(m, "FloatSecondOrderBaseCoefficients", f1);
  populate_ndOrderCoefficients<SecondOrderBaseCoefficients<double>>(m, "DoubleSecondOrderBaseCoefficients", f2);
  populate_ndOrderCoefficients<FourthOrderBaseCoefficients<float>>(m, "FloatFourthOrderBaseCoefficients", f1);
  populate_ndOrderCoefficients<FourthOrderBaseCoefficients<double>>(m, "DoubleFourthOrderBaseCoefficients", f2);

  populate_DirectCoefficients<LinkwitzRileyLowPassCoefficients<float>>(m, "FloatLinkwitzRileyLowPassCoefficients");
  populate_DirectCoefficients<LinkwitzRileyLowPassCoefficients<double>>(m, "DoubleLinkwitzRileyLowPassCoefficients");
  populate_DirectCoefficients<LinkwitzRileyHighPassCoefficients<float>>(m, "FloatLinkwitzRileyHighPassCoefficients");
  populate_DirectCoefficients<LinkwitzRileyHighPassCoefficients<double>>(m, "DoubleLinkwitzRileyHighPassCoefficients");
  populate_DirectCoefficients<LinkwitzRiley4LowPassCoefficients<float>>(m, "FloatLinkwitzRiley4LowPassCoefficients");
  populate_DirectCoefficients<LinkwitzRiley4LowPassCoefficients<double>>(m, "DoubleLinkwitzRiley4LowPassCoefficients");
  populate_DirectCoefficients<LinkwitzRiley4HighPassCoefficients<float>>(m, "FloatLinkwitzRiley4HighPassCoefficients");
  populate_DirectCoefficients<LinkwitzRiley4HighPassCoefficients<double>>(m, "DoubleLinkwitzRiley4HighPassCoefficients");

  populate_IIRFilter<LinkwitzRileyLowPassCoefficients<float>>(m, "FloatLinkwitzRileyLowPassFilter");
  populate_IIRFilter<LinkwitzRileyLowPassCoefficients<double>>(m, "DoubleLinkwitzRileyLowPassFilter");
  populate_IIRFilter<LinkwitzRileyHighPassCoefficients<float>>(m, "FloatLinkwitzRileyHighPasssFilter");
  populate_IIRFilter<LinkwitzRileyHighPassCoefficients<double>>(m, "DoubleLinkwitzRileyHighPassFilter");
  populate_IIRFilter<LinkwitzRiley4LowPassCoefficients<float>>(m, "FloatLinkwitzRiley4LowPassFilter");
  populate_IIRFilter<LinkwitzRiley4LowPassCoefficients<double>>(m, "DoubleLinkwitzRiley4LowPassFilter");
  populate_IIRFilter<LinkwitzRiley4HighPassCoefficients<float>>(m, "FloatLinkwitzRiley4HighPasssFilter");
  populate_IIRFilter<LinkwitzRiley4HighPassCoefficients<double>>(m, "DoubleLinkwitzRiley4HighPassFilter");

  populate_EmptyCoefficients<RIAACoefficients<float>>(m, "FloatRIAACoefficients", f1);
  populate_EmptyCoefficients<RIAACoefficients<double>>(m, "DoubleRIAACoefficients", f2);
  populate_EmptyCoefficients<InverseRIAACoefficients<float>>(m, "FloatInverseRIAACoefficients", f1);
  populate_EmptyCoefficients<InverseRIAACoefficients<double>>(m, "DoubleInverseRIAACoefficients", f2);

  populate_IIRFilter<RIAACoefficients<float>>(m, "FloatRIAAFilter");
  populate_IIRFilter<RIAACoefficients<double>>(m, "DoubleRIAAFilter");
  populate_IIRFilter<InverseRIAACoefficients<float>>(m, "FloatInverseRIAAFilter");
  populate_IIRFilter<InverseRIAACoefficients<double>>(m, "DoubleInverseRIAAFilter");

  populate_QCoefficients<RobertBristowJohnsonLowPassCoefficients<float>>(m, "FloatRobertBristowJohnsonLowPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonLowPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonHighPassCoefficients<float>>(m, "FloatRobertBristowJohnsonHighPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonHighPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPassCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPass2Coefficients<float>>(m, "FloatRobertBristowJohnsonBandPass2Coefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPass2Coefficients<double>>(m, "DoubleRobertBristowJohnsonBandPass2Coefficients");
  populate_QCoefficients<RobertBristowJohnsonBandStopCoefficients<float>>(m, "FloatRobertBristowJohnsonBandStopCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandStopCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandStopCoefficients");
  populate_QCoefficients<RobertBristowJohnsonAllPassCoefficients<float>>(m, "FloatRobertBristowJohnsonAllPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonAllPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonAllPassCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonBandPassPeakCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassPeakCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonBandPassPeakCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassPeakCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonLowShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonLowShelvingCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonLowShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowShelvingCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonHighShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonHighShelvingCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonHighShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighShelvingCoefficients");

  populate_IIRFilter<RobertBristowJohnsonLowPassCoefficients<float>>(m, "FloatRobertBristowJohnsonLowPassFilter");
  populate_IIRFilter<RobertBristowJohnsonLowPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowPassFilter");
  populate_IIRFilter<RobertBristowJohnsonHighPassCoefficients<float>>(m, "FloatRobertBristowJohnsonHighPassFilter");
  populate_IIRFilter<RobertBristowJohnsonHighPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPass2Coefficients<float>>(m, "FloatRobertBristowJohnsonBandPass2Filter");
  populate_IIRFilter<RobertBristowJohnsonBandPass2Coefficients<double>>(m, "DoubleRobertBristowJohnsonBandPass2Filter");
  populate_IIRFilter<RobertBristowJohnsonBandStopCoefficients<float>>(m, "FloatRobertBristowJohnsonBandStopFilter");
  populate_IIRFilter<RobertBristowJohnsonBandStopCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandStopFilter");
  populate_IIRFilter<RobertBristowJohnsonAllPassCoefficients<float>>(m, "FloatRobertBristowJohnsonAllPassFilter");
  populate_IIRFilter<RobertBristowJohnsonAllPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonAllPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassPeakFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassPeakFilter");
  populate_IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonLowShelvingFilter");
  populate_IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowShelvingkFilter");
  populate_IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonHighShelvingFilter");
  populate_IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighShelvingFilter");

  populate_QCoefficients<SecondOrderBandPassCoefficients<float>>(m, "FloatSecondOrderBandPassCoefficients");
  populate_QCoefficients<SecondOrderBandPassCoefficients<double>>(m, "DoubleSecondOrderBandPassCoefficients");
  populate_DirectCoefficients<SecondOrderLowPassCoefficients<float>>(m, "FloatSecondOrderLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderLowPassCoefficients<double>>(m, "DoubleSecondOrderLowPassCoefficients");
  populate_DirectCoefficients<SecondOrderHighPassCoefficients<float>>(m, "FloatSecondOrderHighPassCoefficients");
  populate_DirectCoefficients<SecondOrderHighPassCoefficients<double>>(m, "DoubleSecondOrderHighPassCoefficients");
  populate_QshelfCoefficients<SecondOrderBandPassPeakCoefficients<float>>(m, "FloatSecondOrderBandPassPeakCoefficients");
  populate_QshelfCoefficients<SecondOrderBandPassPeakCoefficients<double>>(m, "DoubleSecondOrderBandPassPeakCoefficients");
  populate_QCoefficients<SecondOrderAllPassCoefficients<float>>(m, "FloatSecondOrderAllPassCoefficients");
  populate_QCoefficients<SecondOrderAllPassCoefficients<double>>(m, "DoubleSecondOrderAllPassCoefficients");
  populate_shelfCoefficients<SecondOrderLowShelvingCoefficients<float>>(m, "FloatSecondOrderLowShelvingCoefficients");
  populate_shelfCoefficients<SecondOrderLowShelvingCoefficients<double>>(m, "DoubleSecondOrderLowShelvingCoefficients");
  populate_shelfCoefficients<SecondOrderHighShelvingCoefficients<float>>(m, "FloatSecondOrderHighShelvingCoefficients");
  populate_shelfCoefficients<SecondOrderHighShelvingCoefficients<double>>(m, "DoubleSecondOrderHighShelvingCoefficients");

  populate_IIRFilter<SecondOrderBandPassCoefficients<float>>(m, "FloatSecondOrderBandPassFilter");
  populate_IIRFilter<SecondOrderBandPassCoefficients<double>>(m, "DoubleSecondOrderBandPassFilter");
  populate_IIRFilter<SecondOrderLowPassCoefficients<float>>(m, "FloatSecondOrderLowPassFilter");
  populate_IIRFilter<SecondOrderLowPassCoefficients<double>>(m, "DoubleSecondOrderLowPassFilter");
  populate_IIRFilter<SecondOrderHighPassCoefficients<float>>(m, "FloatSecondOrderHighPassFilter");
  populate_IIRFilter<SecondOrderHighPassCoefficients<double>>(m, "DoubleSecondOrderHighPassFilter");
  populate_IIRFilter<SecondOrderBandPassPeakCoefficients<float>>(m, "FloatSecondOrderBandPassPeakFilter");
  populate_IIRFilter<SecondOrderBandPassPeakCoefficients<double>>(m, "DoubleSecondOrderBandPassPeakFilter");
  populate_IIRFilter<SecondOrderAllPassCoefficients<float>>(m, "FloatSecondOrderAllPassFilter");
  populate_IIRFilter<SecondOrderAllPassCoefficients<double>>(m, "DoubleSecondOrderAllPassFilter");
  populate_IIRFilter<SecondOrderLowShelvingCoefficients<float>>(m, "FloatSecondOrderLowShelvingFilter");
  populate_IIRFilter<SecondOrderLowShelvingCoefficients<double>>(m, "DoubleSecondOrderLowShelvingFilter");
  populate_IIRFilter<SecondOrderHighShelvingCoefficients<float>>(m, "FloatSecondOrderHighShelvingFilter");
  populate_IIRFilter<SecondOrderHighShelvingCoefficients<double>>(m, "DoubleSecondOrderHighShelvingFilter");

  populate_PedalCoefficients<SD1ToneCoefficients<float>>(m, "FloatSD1ToneCoefficients", f1);
  populate_PedalCoefficients<SD1ToneCoefficients<double>>(m, "DoubleSD1ToneCoefficients", f2);
  populate_PedalCoefficients<TS9ToneCoefficients<float>>(m, "FloatTS9ToneCoefficients", f1);
  populate_PedalCoefficients<TS9ToneCoefficients<double>>(m, "DoubleTS9ToneCoefficients", f2);

  populate_IIRFilter<SD1ToneCoefficients<float>>(m, "FloatSD1ToneFilter");
  populate_IIRFilter<SD1ToneCoefficients<double>>(m, "DoubleSD1ToneFilter");
  populate_IIRFilter<TS9ToneCoefficients<float>>(m, "FloatTS9ToneFilter");
  populate_IIRFilter<TS9ToneCoefficients<double>>(m, "DoubleTS9ToneFilter");

  populate_StackCoefficients<ToneStackCoefficients<float>>(m, "FloatStackToneCoefficients", f1);
  populate_StackCoefficients<ToneStackCoefficients<double>>(m, "DoubleStackToneCoefficients", f2);

  populate_StackFilter<ToneStackCoefficients<float>>(m, "FloatStackToneFilter");
  populate_StackFilter<ToneStackCoefficients<double>>(m, "DoubleStackToneFilter");

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

  populate_TimeVaryingSVFCoefficients<TimeVaryingSecondOrderSVFBaseCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBaseCoefficients", f1);
  populate_TimeVaryingSVFCoefficients<TimeVaryingSecondOrderSVFBaseCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBaseCoefficients", f1);

  populate_DirectCoefficients<TimeVaryingSecondOrderSVFLowPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFLowPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFBandPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFBandPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBandPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFHighPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFHighPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighPassCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFNotchCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFNotchCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFNotchCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFPeakCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFPeakCoefficients");
  populate_DirectCoefficients<TimeVaryingSecondOrderSVFPeakCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFPeakCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFBellCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFBellCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBellCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFLowShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowSheldCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowShelfCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFHighShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighShelfCoefficients");
  populate_shelfCoefficients<TimeVaryingSecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighShelfCoefficients");
  
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBandPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBandPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighPassFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFNotchFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFNotchFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFPeakFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFPeakFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFBellFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFBellFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFLowSheldFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFLowShelfFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<float>>(m, "FloatTimeVaryingSecondOrderSVFHighShelfFilter");
  populate_TimeVaryingSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<double>>(m, "DoubleTimeVaryingSecondOrderSVFHighShelfFilter");

  return m.ptr();
}
