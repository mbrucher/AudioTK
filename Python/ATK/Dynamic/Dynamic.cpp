/**
* \file Dynamic.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>
#include <ATK/Dynamic/AttackReleaseHysteresisFilter.h>

#include <ATK/Dynamic/PowerFilter.h>
#include <ATK/Dynamic/RelativePowerFilter.h>

#include "GainFilter.h"

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
}

PYBIND11_MODULE(PythonDynamic, m) {
  m.doc() = "Audio ToolKit Dynamic module";

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

  populate_GainFilter(m, f1, f2);
}
