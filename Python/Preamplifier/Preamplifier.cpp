/**
* \file Preamplifier.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Preamplifier/FollowerTransistorClassAFilter.h>
#include <ATK/Preamplifier/TransistorClassAFilter.h>
#include <ATK/Preamplifier/TransistorFunction.h>

#include <ATK/Preamplifier/DempwolfTriodeFunction.h>
#include <ATK/Preamplifier/EnhancedKorenTriodeFunction.h>
#include <ATK/Preamplifier/KorenTriodeFunction.h>
#include <ATK/Preamplifier/LeachTriodeFunction.h>
#include <ATK/Preamplifier/ModifiedMunroPiazzaTriodeFunction.h>
#include <ATK/Preamplifier/MunroPiazzaTriodeFunction.h>
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

  template<typename DataType, typename T>
  void populate_FollowerTransistorClassAFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<FollowerTransistorClassAFilter<DataType>>(m, type, parent)
      .def_static("build_standard_filter", &FollowerTransistorClassAFilter<DataType>::build_standard_filter, "Rp"_a = 10e3, "Rg1"_a = 220e3, "Rg2"_a = 27e3, "Ro"_a = 8, "Rk1"_a = 1.5e3, "Rk2"_a = 1e3,"Vbias"_a = 10, "Cg"_a = 0.47e-6, "Co"_a = 4.7e-6, "Ck"_a = 33e-6, "function1"_a = TransistorFunction<DataType>::build_standard_function(), "function2"_a = TransistorFunction<DataType>::build_standard_function());
  }

  template<typename DataType, typename T>
  void populate_TransistorClassAFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<TransistorClassAFilter<DataType>>(m, type, parent)
      .def_static("build_standard_filter", &TransistorClassAFilter<DataType>::build_standard_filter, "Rp"_a = 1e3, "Rg1"_a = 15e3, "Rg2"_a = 1.5e3, "Ro"_a = 22e3, "Rk"_a = 100, "Vbias"_a = 5, "Cg"_a = 3.3e-6, "Co"_a = 1e-6, "Ck"_a = 160e-6, "function"_a = TransistorFunction<DataType>::build_standard_function());
  }
  
  template<typename DataType>
  void populate_DempwolfTriodeFunction(py::module& m, const char* type)
  {
    py::class_<DempwolfTriodeFunction<DataType>>(m, type)
    .def_static("build_standard_function", &DempwolfTriodeFunction<DataType>::build_standard_function, "G"_a = 1.371e-3, "mu"_a = 83.9, "gamma"_a = 1.349, "C"_a = 4.56, "Gg"_a = 3.263e-4, "eta"_a = 1.156, "Cg"_a = 11.99, "Ig0"_a = 3.917e-8, "Cpg"_a = 1.7e-12);
  }

  template<typename DataType>
  void populate_EnhancedKorenTriodeFunction(py::module& m, const char* type)
  {
    py::class_<EnhancedKorenTriodeFunction<DataType>>(m, type)
    .def_static("build_standard_function", &EnhancedKorenTriodeFunction<DataType>::build_standard_function, "a"_a = 17.32, "b"_a = 21238.8, "c"_a = 163757, "Vphi"_a = -0.2227, "gamma"_a = 1.444, "mu"_a = 105, "Kp"_a = 578.2, "Vct"_a = 0.378, "Kvb"_a = 50, "Kvb2"_a = 18.8, "Kg"_a = 1335, "Ex"_a = 1.277, "Cpg"_a = 1.7e-12);
  }

  template<typename DataType>
  void populate_KorenTriodeFunction(py::module& m, const char* type)
  {
    py::class_<KorenTriodeFunction<DataType>>(m, type)
    .def_static("build_standard_function", &KorenTriodeFunction<DataType>::build_standard_function, "mu"_a = 100, "K"_a = 1.73e-6, "Kp"_a = 600, "Kvb"_a = 300, "Kg"_a = 1060, "Ex"_a = 1.4, "Cpg"_a = 1.7e-12);
  }

  template<typename DataType>
  void populate_LeachTriodeFunction(py::module& m, const char* type)
  {
    py::class_<LeachTriodeFunction<DataType>>(m, type)
      .def_static("build_standard_function", &LeachTriodeFunction<DataType>::build_standard_function, "mu"_a=88.5, "K"_a =1.73e-6, "Rgk"_a =20e3, "Vgamma"_a =0.6, "Cpg"_a =1.7e-12);
  }

  template<typename DataType>
  void populate_ModifiedMunroPiazzaTriodeFunction(py::module& m, const char* type)
  {
    py::class_<ModifiedMunroPiazzaTriodeFunction<DataType>>(m, type)
    .def_static("build_standard_function", &ModifiedMunroPiazzaTriodeFunction<DataType>::build_standard_function, "mu"_a = 0.2, "K"_a = 5e-6, "Kp"_a = 45, "Kvb"_a = 1.147e-6, "Kg"_a = 95.43, "sigma"_a = 1, "Cpg"_a = 1.7e-12);
  }
  
  template<typename DataType>
  void populate_MunroPiazzaTriodeFunction(py::module& m, const char* type)
  {
    py::class_<MunroPiazzaTriodeFunction<DataType>>(m, type)
    .def_static("build_standard_function", &MunroPiazzaTriodeFunction<DataType>::build_standard_function, "mu"_a = 0.2, "K"_a = 5e-6, "Kp"_a = 45, "Kvb"_a = 1.147e-6, "Kg"_a = 95.43, "Cpg"_a = 1.7e-12);
  }

  template<typename DataType, typename Model, typename T>
  void populate_TriodeFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<TriodeFilter<DataType, Model>>(m, type, parent)
      .def_static("build_standard_filter", &TriodeFilter<DataType, Model>::build_standard_filter, "Rp"_a = 200e3, "Rg"_a = 220e3, "Ro"_a = 220e3, "Rk"_a = 1e3, "Vbias"_a = 300, "Co"_a = 22e-9, "Ck"_a = 1.e-6, "function"_a = Model::build_standard_function());
  }

  template<typename DataType, typename Model, typename T>
  void populate_Triode2Filter(py::module& m, const char* type, T& parent)
  {
    py::class_<Triode2Filter<DataType, Model>>(m, type, parent)
      .def_static("build_standard_filter", &Triode2Filter<DataType, Model>::build_standard_filter, "Rp"_a = 200e3, "Rg"_a = 220e3, "Ro"_a = 220e3, "Rk"_a = 1e3, "Vbias"_a = 300, "Co"_a = 22e-9, "Ck"_a = 1.e-6, "function"_a = Model::build_standard_function());
  }
}

PYBIND11_PLUGIN(PythonPreamplifier) {
  py::module m("PythonPreamplifier", "Audio ToolKit Preamplifier module");

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");

  populate_TransistorFunction<float>(m, "FloatTransistorFunction");
  populate_TransistorFunction<double>(m, "DoubleTransistorFunction");

  populate_FollowerTransistorClassAFilter<float>(m, "FloatFollowerTransistorClassAFilter", f1);
  populate_FollowerTransistorClassAFilter<double>(m, "DoubleFollowerTransistorClassAFilter", f2);

  populate_TransistorClassAFilter<float>(m, "FloatTransistorClassAFilter", f1);
  populate_TransistorClassAFilter<double>(m, "DoubleTransistorClassAFilter", f2);

  populate_DempwolfTriodeFunction<float>(m, "FloatDempwolfTriodeFunction");
  populate_DempwolfTriodeFunction<double>(m, "DoubleDempwolfTriodeFunction");
  populate_EnhancedKorenTriodeFunction<float>(m, "FloatEnhancedKorenTriodeFunction");
  populate_EnhancedKorenTriodeFunction<double>(m, "DoubleEnhancedKorenTriodeFunction");
  populate_KorenTriodeFunction<float>(m, "FloatKorenTriodeFunction");
  populate_KorenTriodeFunction<double>(m, "DoubleKorenTriodeFunction");
  populate_LeachTriodeFunction<float>(m, "FloatLeachTriodeFunction");
  populate_LeachTriodeFunction<double>(m, "DoubleLeachTriodeFunction");
  populate_ModifiedMunroPiazzaTriodeFunction<float>(m, "FloatModifiedMunroPiazzaTriodeFunction");
  populate_ModifiedMunroPiazzaTriodeFunction<double>(m, "DoubleModifiedMunroPiazzaTriodeFunction");
  populate_MunroPiazzaTriodeFunction<float>(m, "FloatMunroPiazzaTriodeFunction");
  populate_MunroPiazzaTriodeFunction<double>(m, "DoubleMunroPiazzaTriodeFunction");

  populate_Triode2Filter<float, DempwolfTriodeFunction<float>>(m, "FloatDempwolfTriode2Filter", f1);
  populate_Triode2Filter<double, DempwolfTriodeFunction<double>>(m, "DoubleDempwolfTriode2Filter", f2);
  populate_Triode2Filter<float, KorenTriodeFunction<float>>(m, "FloatKorenTriode2Filter", f1);
  populate_Triode2Filter<double, KorenTriodeFunction<double>>(m, "DoubleKorenTriode2Filter", f2);
  populate_Triode2Filter<float, EnhancedKorenTriodeFunction<float>>(m, "FloatEnhancedKorenTriode2Filter", f1);
  populate_Triode2Filter<double, EnhancedKorenTriodeFunction<double>>(m, "DoubleEnhancedKorenTriode2Filter", f2);
  populate_Triode2Filter<float, LeachTriodeFunction<float>>(m, "FloatLeachTriode2Filter", f1);
  populate_Triode2Filter<double, LeachTriodeFunction<double>>(m, "DoubleLeachTriode2Filter", f2);
  populate_Triode2Filter<float, ModifiedMunroPiazzaTriodeFunction<float>>(m, "FloatModifiedMunroPiazzaTriode2Filter", f1);
  populate_Triode2Filter<double, ModifiedMunroPiazzaTriodeFunction<double>>(m, "DoubleModifiedMunroPiazzaTriode2Filter", f2);
  populate_Triode2Filter<float, MunroPiazzaTriodeFunction<float>>(m, "FloatMunroPiazzaTriode2Filter", f1);
  populate_Triode2Filter<double, MunroPiazzaTriodeFunction<double>>(m, "DoubleMunroPiazzaTriode2Filter", f2);

  populate_TriodeFilter<float, DempwolfTriodeFunction<float>>(m, "FloatDempwolfTriodeFilter", f1);
  populate_TriodeFilter<double, DempwolfTriodeFunction<double>>(m, "DoubleDempwolfTriodeFilter", f2);
  populate_TriodeFilter<float, KorenTriodeFunction<float>>(m, "FloatKorenTriodeFilter", f1);
  populate_TriodeFilter<double, KorenTriodeFunction<double>>(m, "DoubleKorenTriodeFilter", f2);
  populate_TriodeFilter<float, EnhancedKorenTriodeFunction<float>>(m, "FloatEnhancedKorenTriodeFilter", f1);
  populate_TriodeFilter<double, EnhancedKorenTriodeFunction<double>>(m, "DoubleEnhancedKorenTriodeFilter", f2);
  populate_TriodeFilter<float, LeachTriodeFunction<float>>(m, "FloatLeachTriodeFilter", f1);
  populate_TriodeFilter<double, LeachTriodeFunction<double>>(m, "DoubleLeachTriodeFilter", f2);
  populate_TriodeFilter<float, ModifiedMunroPiazzaTriodeFunction<float>>(m, "FloatModifiedMunroPiazzaTriodeFilter", f1);
  populate_TriodeFilter<double, ModifiedMunroPiazzaTriodeFunction<double>>(m, "DoubleModifiedMunroPiazzaTriodeFilter", f2);
  populate_TriodeFilter<float, MunroPiazzaTriodeFunction<float>>(m, "FloatMunroPiazzaTriodeFilter", f1);
  populate_TriodeFilter<double, MunroPiazzaTriodeFunction<double>>(m, "DoubleMunroPiazzaTriodeFilter", f2);

  return m.ptr();
}
