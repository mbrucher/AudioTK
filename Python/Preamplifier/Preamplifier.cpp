/**
* \file Preamplifier.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Preamplifier/FollowerTransistorClassAFilter.h>
#include <ATK/Preamplifier/TransistorClassAFilter.h>
#include <ATK/Preamplifier/TransistorFunction.h>

#include <ATK/Preamplifier/KorenTriodeFunction.h>
#include <ATK/Preamplifier/TriodeFilter.h>
#include <ATK/Preamplifier/Triode2Filter.h>

namespace py = pybind11;

using namespace ATK;
using namespace pybind11::literals;

namespace
{
  template<typename DataType>
  void populate_TransistorFunction(py::module& m, const char* type)
  {
    py::class_<TransistorFunction<DataType>>(m, type)
      .def_static("build_standard_function", &TransistorFunction<DataType>::build_standard_function, "I"_a = 1e-12, "Vt"_a = 26e-3, "Br"_a = 1, "Bf"_a = 100);
  }

  template<typename DataType>
  void populate_FollowerTransistorClassAFilter(py::module& m, const char* type)
  {
    py::class_<FollowerTransistorClassAFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def_static("build_standard_filter", &FollowerTransistorClassAFilter<DataType>::build_standard_filter, "Rp"_a = 10e3, "Rg1"_a = 220e3, "Rg2"_a = 27e3, "Ro"_a = 8, "Rk1"_a = 1.5e3, "Rk2"_a = 1e3,"Vbias"_a = 10, "Cg"_a = 0.47e-6, "Co"_a = 4.7e-6, "Ck"_a = 33e-6, "function1"_a = TransistorFunction<DataType>::build_standard_function(), "function2"_a = TransistorFunction<DataType>::build_standard_function());
  }

  template<typename DataType>
  void populate_TransistorClassAFilter(py::module& m, const char* type)
  {
    py::class_<TransistorClassAFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def_static("build_standard_filter", &TransistorClassAFilter<DataType>::build_standard_filter, "Rp"_a = 1e3, "Rg1"_a = 15e3, "Rg2"_a = 1.5e3, "Ro"_a = 22e3, "Rk"_a = 100, "Vbias"_a = 5, "Cg"_a = 3.3e-6, "Co"_a = 1e-6, "Ck"_a = 160e-6, "function"_a = TransistorFunction<DataType>::build_standard_function());
  }

  template<typename DataType>
  void populate_KorenTriodeFunction(py::module& m, const char* type)
  {
    py::class_<KorenTriodeFunction<DataType>>(m, type)
      .def_static("build_standard_function", &KorenTriodeFunction<DataType>::build_standard_function, "mu"_a = 100, "K"_a = 1.73e-6, "Kp"_a = 600, "Kvb"_a = 300, "Kg"_a = 1060, "Ex"_a = 1.4, "Cpg"_a = 1.7e-12);
  }

  template<typename DataType, typename Model>
  void populate_TriodeFilter(py::module& m, const char* type)
  {
    py::class_<TriodeFilter<DataType, Model>, TypedBaseFilter<DataType>>(m, type)
      .def_static("build_standard_filter", &TriodeFilter<DataType, Model>::build_standard_filter, "Rp"_a = 200e3, "Rg"_a = 220e3, "Ro"_a = 220e3, "Rk"_a = 1e3, "Vbias"_a = 300, "Co"_a = 22e-9, "Ck"_a = 1.e-6, "function"_a = Model::build_standard_function());
  }

  template<typename DataType, typename Model>
  void populate_Triode2Filter(py::module& m, const char* type)
  {
    py::class_<Triode2Filter<DataType, Model>, TypedBaseFilter<DataType>>(m, type)
      .def_static("build_standard_filter", &Triode2Filter<DataType, Model>::build_standard_filter, "Rp"_a = 200e3, "Rg"_a = 220e3, "Ro"_a = 220e3, "Rk"_a = 1e3, "Vbias"_a = 300, "Co"_a = 22e-9, "Ck"_a = 1.e-6, "function"_a = Model::build_standard_function());
  }
}

PYBIND11_PLUGIN(PythonPreamplifier) {
  py::module m("PythonPreamplifier", "Audio ToolKit Preamplifier module");

  populate_TransistorFunction<float>(m, "FloatTransistorFunction");
  populate_TransistorFunction<double>(m, "DoubleTransistorFunction");

  populate_FollowerTransistorClassAFilter<float>(m, "FloatFollowerTransistorClassAFilter");
  populate_FollowerTransistorClassAFilter<double>(m, "DoubleFollowerTransistorClassAFilter");

  populate_TransistorClassAFilter<float>(m, "FloatTransistorClassAFilter");
  populate_TransistorClassAFilter<double>(m, "DoubleTransistorClassAFilter");

  populate_KorenTriodeFunction<float>(m, "FloatKorenTriodeFunction");
  populate_KorenTriodeFunction<double>(m, "DoubleKorenTriodeFunction");

  populate_Triode2Filter<float, KorenTriodeFunction<float>>(m, "FloatKorenTriode2Filter");
  populate_Triode2Filter<double, KorenTriodeFunction<double>>(m, "DoubleKorenTriode2Filter");

  populate_TriodeFilter<float, KorenTriodeFunction<float>>(m, "FloatKorenTriodeFilter");
  populate_TriodeFilter<double, KorenTriodeFunction<double>>(m, "DoubleKorenTriodeFilter");

  return m.ptr();
}
