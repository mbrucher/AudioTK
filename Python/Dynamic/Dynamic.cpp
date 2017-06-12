/**
* \file Dynamic.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>
#include <ATK/Dynamic/AttackReleaseHysteresisFilter.h>

#include <ATK/Dynamic/PowerFilter.h>
#include <ATK/Dynamic/RelativePowerFilter.h>

#include <ATK/Dynamic/GainCompressorFilter.h>
#include <ATK/Dynamic/GainExpanderFilter.h>
#include <ATK/Dynamic/GainFilter.h>
#include <ATK/Dynamic/GainLimiterFilter.h>
#include <ATK/Dynamic/GainSwellFilter.h>

#include <ATK/Dynamic/GainColoredCompressorFilter.h>
#include <ATK/Dynamic/GainColoredExpanderFilter.h>
#include <ATK/Dynamic/GainMaxColoredExpanderFilter.h>
#include <ATK/Dynamic/GainMaxCompressorFilter.h>
#include <ATK/Dynamic/GainMaxExpanderFilter.h>


namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType, typename T>
  void populate_AttackReleaseFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<AttackReleaseFilter<DataType>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("nb_channels") = 1)
    .def_property("attack", &AttackReleaseFilter<DataType>::get_attack, &AttackReleaseFilter<DataType>::set_attack)
    .def_property("release", &AttackReleaseFilter<DataType>::get_release, &AttackReleaseFilter<DataType>::set_release);
  }

  template<typename DataType, typename T>
  void populate_AttackReleaseHysteresisFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<AttackReleaseHysteresisFilter<DataType>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("nb_channels") = 1)
    .def_property("attack", &AttackReleaseHysteresisFilter<DataType>::get_attack, &AttackReleaseHysteresisFilter<DataType>::set_attack)
    .def_property("attack_hysteresis", &AttackReleaseHysteresisFilter<DataType>::get_attack_hysteresis, &AttackReleaseHysteresisFilter<DataType>::set_attack_hysteresis)
    .def_property("release", &AttackReleaseHysteresisFilter<DataType>::get_release, &AttackReleaseHysteresisFilter<DataType>::set_release)
    .def_property("release_hysteresis", &AttackReleaseHysteresisFilter<DataType>::get_release_hysteresis, &AttackReleaseHysteresisFilter<DataType>::set_release_hysteresis);
  }
  
  template<typename Filter, typename T>
  void populate_PowerFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<Filter>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("nb_channels") = 1)
    .def_property("memory", &Filter::get_memory, &Filter::set_memory);
  }

  template<typename DataType, typename T>
  void populate_ParentGainFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<ParentGainFilter<DataType>>(m, type, parent)
    .def_property("threshold", &ParentGainFilter<DataType>::get_threshold, &ParentGainFilter<DataType>::set_threshold)
    .def_property("ratio", &ParentGainFilter<DataType>::get_ratio, &ParentGainFilter<DataType>::set_ratio);
  }
  
  template<typename Filter>
  void populate_SimpleGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness);
  }
  
  template<typename Filter>
  void populate_ColoredGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness)
    .def_property("color", &Filter::get_color, &Filter::set_color)
    .def_property("quality", &Filter::get_quality, &Filter::set_quality);
  }
  
  template<typename Filter>
  void populate_MaxColoredGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness)
    .def_property("color", &Filter::get_color, &Filter::set_color)
    .def_property("quality", &Filter::get_quality, &Filter::set_quality)
    .def_property("max_reduction", &Filter::get_max_reduction, &Filter::set_max_reduction);
  }
  
  template<typename Filter>
  void populate_MaxGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness)
    .def_property("max_reduction", &Filter::get_max_reduction, &Filter::set_max_reduction);
  }
  
  template<typename Filter>
  void populate_GainFilter(py::module& m, const char* type)
  {
    py::class_<GainFilter<Filter>, Filter>(m, type)
    .def(py::init<std::size_t, std::size_t, std::size_t>(), py::arg("nb_channels") = 1, py::arg("LUTsize") = 128*1024, py::arg("LUTprecision") = 64);
  }
}

PYBIND11_PLUGIN(PythonDynamic) {
  py::module m("PythonDynamic", "Audio ToolKit Dynamic module");

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");
  
  populate_AttackReleaseFilter<float>(m, "FloatAttackReleaseFilter", f1);
  populate_AttackReleaseFilter<double>(m, "DoubleAttackReleaseFilter", f2);
  
  populate_AttackReleaseHysteresisFilter<float>(m, "FloatAttackReleaseHysteresisFilter", f1);
  populate_AttackReleaseHysteresisFilter<double>(m, "DoubleAttackReleaseHysteresisFilter", f2);

  populate_PowerFilter<PowerFilter<float>>(m, "FloatPowerFilter", f1);
  populate_PowerFilter<PowerFilter<double>>(m, "DoublePowerFilter", f2);
  populate_PowerFilter<RelativePowerFilter<float>>(m, "FloatRelativePowerFilter", f1);
  populate_PowerFilter<RelativePowerFilter<double>>(m, "DoubleRelativePowerFilter", f2);

  populate_ParentGainFilter<float>(m, "FloatParentGainFilter", f1);
  populate_ParentGainFilter<double>(m, "DoubleParentGainFilter", f2);
  
  populate_SimpleGainFilter<GainCompressorFilter<float>>(m, "FloatTempGainCompressorFilter");
  populate_SimpleGainFilter<GainCompressorFilter<double>>(m, "DoubleTempGainCompressorFilter");
  populate_SimpleGainFilter<GainExpanderFilter<float>>(m, "FloatTempGainExpanderFilter");
  populate_SimpleGainFilter<GainExpanderFilter<double>>(m, "DoubleTempGainExpanderFilter");
  populate_SimpleGainFilter<GainLimiterFilter<float>>(m, "FloatTempGainLimiterFilter");
  populate_SimpleGainFilter<GainLimiterFilter<double>>(m, "DoubleTempGainLimiterFilter");
  populate_SimpleGainFilter<GainSwellFilter<float>>(m, "FloatTempGainSwellFilter");
  populate_SimpleGainFilter<GainSwellFilter<double>>(m, "DoubleTempGainSwellFilter");

  populate_GainFilter<GainCompressorFilter<float>>(m, "FloatGainCompressorFilter");
  populate_GainFilter<GainCompressorFilter<double>>(m, "DoubleGainCompressorFilter");
  populate_GainFilter<GainExpanderFilter<float>>(m, "FloatGainExpanderFilter");
  populate_GainFilter<GainExpanderFilter<double>>(m, "DoubleGainExpanderFilter");
  populate_GainFilter<GainLimiterFilter<float>>(m, "FloatGainLimiterFilter");
  populate_GainFilter<GainLimiterFilter<double>>(m, "DoubleGainLimiterFilter");
  populate_GainFilter<GainSwellFilter<float>>(m, "FloatGainSwellFilter");
  populate_GainFilter<GainSwellFilter<double>>(m, "DoubleGainSwellFilter");

  populate_ColoredGainFilter<GainColoredCompressorFilter<float>>(m, "FloatTempGainColoredCompressorFilter");
  populate_ColoredGainFilter<GainColoredCompressorFilter<double>>(m, "DoubleTempGainColoredCompressorFilter");
  populate_ColoredGainFilter<GainColoredExpanderFilter<float>>(m, "FloatTempGainColoredExpanderFilter");
  populate_ColoredGainFilter<GainColoredExpanderFilter<double>>(m, "DoubleTempGainColoredExpanderFilter");
  populate_MaxColoredGainFilter<GainMaxColoredExpanderFilter<float>>(m, "FloatTempGainMaxColoredExpanderFilter");
  populate_MaxColoredGainFilter<GainMaxColoredExpanderFilter<double>>(m, "DoubleTempGainMaxColoredExpanderFilter");
  populate_MaxGainFilter<GainMaxCompressorFilter<float>>(m, "FloatTempGainMaxCompressorFilter");
  populate_MaxGainFilter<GainMaxCompressorFilter<double>>(m, "DoubleTempGainMaxCompressorFilter");
  populate_MaxGainFilter<GainMaxExpanderFilter<float>>(m, "FloatTempGainMaxExpanderFilter");
  populate_MaxGainFilter<GainMaxExpanderFilter<double>>(m, "DoubleTempGainMaxExpanderFilter");

  populate_GainFilter<GainColoredCompressorFilter<float>>(m, "FloatGainColoredCompressorFilter");
  populate_GainFilter<GainColoredCompressorFilter<double>>(m, "DoubleGainColoredCompressorFilter");
  populate_GainFilter<GainColoredExpanderFilter<float>>(m, "FloatGainColoredExpanderFilter");
  populate_GainFilter<GainColoredExpanderFilter<double>>(m, "DoubleGainColoredExpanderFilter");
  populate_GainFilter<GainMaxColoredExpanderFilter<float>>(m, "FloatGainMaxColoredExpanderFilter");
  populate_GainFilter<GainMaxColoredExpanderFilter<double>>(m, "DoubleGainMaxColoredExpanderFilter");
  populate_GainFilter<GainMaxCompressorFilter<float>>(m, "FloatGainMaxCompressorFilter");
  populate_GainFilter<GainMaxCompressorFilter<double>>(m, "DoubleGainMaxCompressorFilter");
  populate_GainFilter<GainMaxExpanderFilter<float>>(m, "FloatGainMaxExpanderFilter");
  populate_GainFilter<GainMaxExpanderFilter<double>>(m, "DoubleGainMaxExpanderFilter");

  return m.ptr();
}
