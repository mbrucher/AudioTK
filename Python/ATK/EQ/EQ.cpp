/**
* \file EQ.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/ChamberlinFilter.h>

#include <ATK/EQ/CustomIIRFilter.h>
#include <ATK/EQ/PedalToneStackFilter.h>
#include <ATK/EQ/RIAAFilter.h>
#include <ATK/EQ/FourthOrderFilter.h>
#include <ATK/EQ/LinkwitzRileyFilter.h>
#include <ATK/EQ/RobertBristowJohnsonFilter.h>
#include <ATK/EQ/ToneStackFilter.h>

#include <ATK/EQ/CustomFIRFilter.h>
#include <ATK/EQ/FIRFilter.h>

#include "ChebyshevFilter.h"
#include "MainFilter.h"
#include "RobertBristowJohnsonFilter.h"
#include "SecondOrderFilter.h"
#include "SecondOrderSVFFilter.h"
#include "StandardFilters.h"
#include "TimeVaryingIIRFilter.h"
#include "TimeVaryingSVFFilter.h"

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
    .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1))
    .def_property_readonly("coefficients_in", [](const FIRFilter<Coefficients>& instance)
    {
      return py::array_t<DataType>(instance.get_coefficients_in().size(), instance.get_coefficients_in().data());
    });
  }
  
  template<typename DataType, typename T>
  void populate_CustomFIR(py::module& m, const char* type, T& parent)
  {
    py::class_<FIRFilter<CustomFIRCoefficients<DataType>>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1))
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
      instance.set_coefficients_in(std::vector<DataType>(array.data(), array.data() + array.shape()[0]));
    });
  }
  
  template<typename DataType, typename T>
  void populate_CustomIIR(py::module& m, const char* type, T& parent)
  {
    py::class_<IIRFilter<CustomIIRCoefficients<DataType>>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1))
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
      instance.set_coefficients_in(std::vector<DataType>(array.data(), array.data() + array.shape()[0]));
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
      instance.set_coefficients_out(std::vector<DataType>(array.data(), array.data() + array.shape()[0]));
    });
  }

  template<typename Coefficients, typename T>
  void populate_EmptyCoefficients(py::module& m, const char* type, T& parent)
  {
    py::class_<Coefficients>(m, type, parent);
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
  populate_ChebyshevFilter(m, f1, f2);
  populate_SecondOrderFilter(m, f1, f2);
  populate_RobertBristowJohnsonFilter(m);
  populate_SecondOrderSVFFilter(m, f1, f2);

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

  populate_TimeVaryingIIRFilters(m, f1, f2);
  populate_TimeVaryingSVFFilters(m, f1, f2);
}
