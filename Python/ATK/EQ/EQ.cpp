/**
* \file EQ.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/ChamberlinFilter.h>

#include <ATK/EQ/CustomIIRFilter.h>
#include <ATK/EQ/FourthOrderFilter.h>
#include <ATK/EQ/LinkwitzRileyFilter.h>
#include <ATK/EQ/PedalToneStackFilter.h>
#include <ATK/EQ/RIAAFilter.h>
#include <ATK/EQ/RobertBristowJohnsonFilter.h>
#include <ATK/EQ/SecondOrderFilter.h>
#include <ATK/EQ/ToneStackFilter.h>

#include <ATK/EQ/CustomFIRFilter.h>
#include <ATK/EQ/FIRFilter.h>

#include <ATK/EQ/SecondOrderSVFFilter.h>

#include "MainFilter.h"
#include "StandardFilters.h"
#include "TimeVaryingIIRFilter.h"
#include "TimeVaryingSVFFilter.h"

namespace py = pybind11;

using namespace ATK;
using namespace py::literals;

namespace
{
  template<typename DataType, typename T>
  void populate_ChamberlinFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<ChamberlinFilter<DataType>>(m, type, parent)
      .def(py::init<>())
      .def_property("cut_frequency", &ChamberlinFilter<DataType>::get_cut_frequency, &ChamberlinFilter<DataType>::set_cut_frequency)
      .def_property("attenuation", &ChamberlinFilter<DataType>::get_attenuation, &ChamberlinFilter<DataType>::set_attenuation)
      .def_property("selected", &ChamberlinFilter<DataType>::get_selected, &ChamberlinFilter<DataType>::select);
  }

  template<typename Coefficients>
  void populate_FIRFilter(py::module& m, const char* type)
  {
    typedef typename Coefficients::DataType DataType;
    py::class_<FIRFilter<Coefficients>, Coefficients>(m, type)
    .def(py::init<std::size_t>(), "nb_channels"_a = 1)
    .def_property_readonly("coefficients_in", [](const FIRFilter<Coefficients>& instance)
    {
      return py::array_t<DataType>(instance.get_coefficients_in().size(), instance.get_coefficients_in().data());
    });
  }
  
  template<typename DataType, typename T>
  void populate_CustomFIR(py::module& m, const char* type, T& parent)
  {
    py::class_<FIRFilter<CustomFIRCoefficients<DataType>>>(m, type, parent)
      .def(py::init<std::size_t>(), "nb_channels"_a = 1)
      .def_property("coefficients_in", [](const FIRFilter<CustomFIRCoefficients<DataType>>& instance)
    {
      return py::array_t<DataType>(instance.get_coefficients_in().size(), instance.get_coefficients_in().data());
    },
        [](FIRFilter<CustomFIRCoefficients<DataType>>& instance, const py::array_t<DataType>& array)
    {
      if(array.ndim() != 1 || array.shape()[0] == 0)
      {
        throw std::length_error("Wrong size for input coefficients, must be of dimension 1 and not empty");
      }
      instance.set_coefficients_in(std::vector<DataType>(array.data(), array.data() + array.size()));
    });
  }
  
  template<typename DataType, typename T>
  void populate_CustomIIR(py::module& m, const char* type, T& parent)
  {
    py::class_<IIRFilter<CustomIIRCoefficients<DataType>>>(m, type, parent)
      .def(py::init<std::size_t>(), "nb_channels"_a = 1)
      .def_property("coefficients_in", [](const IIRFilter<CustomIIRCoefficients<DataType>>& instance)
    {
      return py::array_t<DataType>(instance.get_coefficients_in().size(), instance.get_coefficients_in().data());
    },
        [](IIRFilter<CustomIIRCoefficients<DataType>>& instance, const py::array_t<DataType>& array)
    {
      if(array.ndim() != 1 || array.shape()[0] == 0)
      {
        throw std::length_error("Wrong size for input coefficients, must be of dimension 1 and not empty");
      }
      instance.set_coefficients_in(std::vector<DataType>(array.data(), array.data() + array.size()));
    })
      .def_property("coefficients_out", [](const IIRFilter<CustomIIRCoefficients<DataType>>& instance)
    {
      return py::array_t<DataType>(instance.get_coefficients_out().size(), instance.get_coefficients_out().data());
    },
        [](IIRFilter<CustomIIRCoefficients<DataType>>& instance, const py::array_t<DataType>& array)
    {
      if(array.ndim() != 1 || array.shape()[0] == 0)
      {
        throw std::length_error("Wrong size for input coefficients, must be of dimension 1 and not empty");
      }
      instance.set_coefficients_out(std::vector<DataType>(array.data(), array.data() + array.size()));
    });
  }

  template<typename Coefficients, typename T>
  void populate_EmptyCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent);
  }

  template<typename Coefficients, typename T>
  void populate_ndOrderCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent)
    .def_property("cut_frequency", &Coefficients::get_cut_frequency, &Coefficients::set_cut_frequency);
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
}

PYBIND11_MODULE(PythonEQ, m)
{
  m.doc() = "Audio ToolKit EQ module";

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");

  populate_ChamberlinFilter<float>(m, "FloatChamberlinFilter", f1);
  populate_ChamberlinFilter<double>(m, "DoubleChamberlinFilter", f1);
  
  populate_CustomFIR<float>(m, "FloatCustomFIRFilter", f1);
  populate_CustomFIR<double>(m, "DoubleCustomFIRFilter", f2);
  
  populate_CustomIIR<float>(m, "FloatCustomIIRFilter", f1);
  populate_CustomIIR<double>(m, "DoubleCustomIIRFilter", f2);
  
  populate_StandardFilters(m, f1, f2);

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
  populate_IIRFilter<LinkwitzRiley4HighPassCoefficients<float>>(m, "FloatLinkwitzRiley4HighPassFilter");
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

  populate_TimeVaryingIIRFilters(m, f1, f2);
  populate_TimeVaryingSVFFilters(m, f1, f2);
}
