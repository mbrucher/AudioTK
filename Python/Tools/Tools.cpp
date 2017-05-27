/**
* \file Tools.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Tools/ApplyGainFilter.h>
#include <ATK/Tools/BufferFilter.h>
#include <ATK/Tools/DecimationFilter.h>
#include <ATK/Tools/DryWetFilter.h>
#include <ATK/Tools/MSFilter.h>
#include <ATK/Tools/OversamplingFilter.h>
#include <ATK/Tools/PanFilter.h>
#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/VolumeFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType>
  void populate_ApplyGainFilter(py::module& m, const char* type)
  {
    py::class_<ApplyGainFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType>
  void populate_BufferFilter(py::module& m, const char* type)
  {
    py::class_<BufferFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType>
  void populate_DecimationFilter(py::module& m, const char* type)
  {
    py::class_<DecimationFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType>
  void populate_DryWetFilter(py::module& m, const char* type)
  {
    py::class_<DryWetFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType>
  void populate_MiddleSideFilter(py::module& m, const char* type)
  {
    py::class_<MiddleSideFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType, typename Coefficients>
  void populate_OversamplingFilter(py::module& m, const char* type)
  {
    py::class_<OversamplingFilter<DataType, Coefficients>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType>
  void populate_PanFilter(py::module& m, const char* type)
  {
    py::class_<PanFilter<DataType>, TypedBaseFilter<DataType>> pan(m, type);
    pan.def(py::init<unsigned long>(), py::arg("nb_channels") = 1)
      .def_property("pan_law", &PanFilter<DataType>::get_pan_law, &PanFilter<DataType>::set_pan_law)
      .def_property("pan", &PanFilter<DataType>::get_pan, &PanFilter<DataType>::set_pan);


    py::enum_<PanFilter<DataType>::PAN_LAWS>(pan, "PAN_LAWS")
      .value("SINCOS_0_CENTER", PanFilter<DataType>::PAN_LAWS::SINCOS_0_CENTER)
      .value("SINCOS_3_CENTER", PanFilter<DataType>::PAN_LAWS::SINCOS_3_CENTER)
      .value("SQUARE_0_CENTER", PanFilter<DataType>::PAN_LAWS::SQUARE_0_CENTER)
      .value("SQUARE_3_CENTER", PanFilter<DataType>::PAN_LAWS::SQUARE_3_CENTER)
      .value("LINEAR_TAPER", PanFilter<DataType>::PAN_LAWS::LINEAR_TAPER)
      .value("BALANCE", PanFilter<DataType>::PAN_LAWS::BALANCE)
      .export_values();
  }

  template<typename DataType>
  void populate_SumFilter(py::module& m, const char* type)
  {
    py::class_<SumFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType>
  void populate_VolumeFilter(py::module& m, const char* type)
  {
    py::class_<VolumeFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def(py::init<unsigned long>(), py::arg("nb_channels")=1)
      .def_property("volume", &VolumeFilter<DataType>::get_volume, &VolumeFilter<DataType>::set_volume);
  }
}

PYBIND11_PLUGIN(PythonTools) {
  py::module m("PythonTools", "Audio ToolKit Tools module");

  populate_ApplyGainFilter<float>(m, "FloatApplyGainFilter");
  populate_ApplyGainFilter<double>(m, "DoubleApplyGainFilter");
  populate_ApplyGainFilter<std::complex<float>>(m, "ComplexFloatApplyGainFilter");
  populate_ApplyGainFilter<std::complex<double>>(m, "ComplexDoubleApplyGainFilter");

  populate_BufferFilter<float>(m, "FloatBufferFilter");
  populate_BufferFilter<double>(m, "DoubleBufferFilter");
  populate_BufferFilter<std::complex<float>>(m, "ComplexFloatBufferFilter");
  populate_BufferFilter<std::complex<double>>(m, "ComplexDoubleBufferFilter");

  populate_DecimationFilter<float>(m, "FloatDecimationFilter");
  populate_DecimationFilter<double>(m, "DoubleDecimationFilter");
  populate_DecimationFilter<std::complex<float>>(m, "ComplexFloatDecimationFilter");
  populate_DecimationFilter<std::complex<double>>(m, "ComplexDoubleDecimationFilter");

  populate_DryWetFilter<float>(m, "FloatDryWetFilter");
  populate_DryWetFilter<double>(m, "DoubleDryWetFilter");
  populate_DryWetFilter<std::complex<float>>(m, "ComplexFloatDryWetFilter");
  populate_DryWetFilter<std::complex<double>>(m, "ComplexDoubleDryWetFilter");

  populate_MiddleSideFilter<float>(m, "FloatMiddleSideFilter");
  populate_MiddleSideFilter<double>(m, "DoubleMiddleSideFilter");
  populate_MiddleSideFilter<std::complex<float>>(m, "ComplexFloatMiddleSideFilter");
  populate_MiddleSideFilter<std::complex<double>>(m, "ComplexDoubleMiddleSideFilter");

  populate_OversamplingFilter<float, Oversampling6points5order_2<float>>(m, "FloatOversampling6points5order_2Filter");
  populate_OversamplingFilter<double, Oversampling6points5order_2<double>>(m, "DoubleOversampling6points5order_2Filter");
  populate_OversamplingFilter<float, Oversampling6points5order_4<float>>(m, "FloatOversampling6points5order_4Filter");
  populate_OversamplingFilter<double, Oversampling6points5order_4<double>>(m, "DoubleOversampling6points5order_4Filter");
  populate_OversamplingFilter<float, Oversampling6points5order_8<float>>(m, "FloatOversampling6points5order_8Filter");
  populate_OversamplingFilter<double, Oversampling6points5order_8<double>>(m, "DoubleOversampling6points5order_8Filter");
  populate_OversamplingFilter<float, Oversampling6points5order_16<float>>(m, "FloatOversampling6points5order_16Filter");
  populate_OversamplingFilter<double, Oversampling6points5order_16<double>>(m, "DoubleOversampling6points5order_16Filter");
  populate_OversamplingFilter<float, Oversampling6points5order_32<float>>(m, "FloatOversampling6points5order_32Filter");
  populate_OversamplingFilter<double, Oversampling6points5order_32<double>>(m, "DoubleOversampling6points5order_32Filter");

  populate_PanFilter<float>(m, "FloatPanFilter");
  populate_PanFilter<double>(m, "DoublePanFilter");
  populate_PanFilter<std::complex<float>>(m, "ComplexFloatPanFilter");
  populate_PanFilter<std::complex<double>>(m, "ComplexDoublePanFilter");

  populate_SumFilter<float>(m, "FloatSumFilter");
  populate_SumFilter<double>(m, "DoubleSumFilter");
  populate_SumFilter<std::complex<float>>(m, "ComplexFloatSumFilter");
  populate_SumFilter<std::complex<double>>(m, "ComplexDoubleSumFilter");

  populate_VolumeFilter<float>(m, "FloatVolumeFilter");
  populate_VolumeFilter<double>(m, "DoubleVolumeFilter");
  populate_VolumeFilter<std::complex<float>>(m, "ComplexFloatVolumeFilter");
  populate_VolumeFilter<std::complex<double>>(m, "ComplexDoubleVolumeFilter");

  return m.ptr();
}
