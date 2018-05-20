/**
* \file Tools.cpp
*/

#include <gsl/gsl>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Tools/ApplyGainFilter.h>
#include <ATK/Tools/BufferFilter.h>
#include <ATK/Tools/DecimationFilter.h>
#include <ATK/Tools/DryWetFilter.h>
#include <ATK/Tools/MuteSoloBufferFilter.h>
#include <ATK/Tools/MSFilter.h>
#include <ATK/Tools/OversamplingFilter.h>
#include <ATK/Tools/PanFilter.h>
#include <ATK/Tools/SinusGeneratorFilter.h>
#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/TanFilter.h>
#include <ATK/Tools/VolumeFilter.h>
#include <ATK/Tools/WhiteNoiseGeneratorFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType, typename T>
  void populate_ApplyGainFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<ApplyGainFilter<DataType>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }

  template<typename DataType, typename T>
  void populate_BufferFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<BufferFilter<DataType>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }

  template<typename DataType, typename T>
  void populate_DecimationFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<DecimationFilter<DataType>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }

  template<typename DataType, typename T>
  void populate_DryWetFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<DryWetFilter<DataType>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1))
      .def_property("dry", &DryWetFilter<DataType>::get_dry, &DryWetFilter<DataType>::set_dry);
  }

  template<typename DataType, typename T>
  void populate_MiddleSideFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<MiddleSideFilter<DataType>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }
  
  template<typename DataType, typename T>
  void populate_MuteSoloBufferFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<MuteSoloBufferFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1))
    .def_property("mute", &MuteSoloBufferFilter<DataType>::get_mute, &MuteSoloBufferFilter<DataType>::set_mute)
    .def_property("solo", &MuteSoloBufferFilter<DataType>::get_solo, &MuteSoloBufferFilter<DataType>::set_solo);
  }

  template<typename Coefficients, typename T>
  void populate_OversamplingFilter(py::module& m, const char* type, T& parent)
  {
    typedef typename Coefficients::DataType DataType;
    py::class_<OversamplingFilter<DataType, Coefficients>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }

  template<typename DataType, typename T>
  void populate_PanFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<PanFilter<DataType>> pan(m, type, parent);
    pan.def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1))
      .def_property("pan_law", &PanFilter<DataType>::get_pan_law, &PanFilter<DataType>::set_pan_law)
      .def_property("pan", &PanFilter<DataType>::get_pan, &PanFilter<DataType>::set_pan);

    py::enum_<typename PanFilter<DataType>::PAN_LAWS>(pan, "PAN_LAWS")
      .value("SINCOS_0_CENTER", PanFilter<DataType>::PAN_LAWS::SINCOS_0_CENTER)
      .value("SINCOS_3_CENTER", PanFilter<DataType>::PAN_LAWS::SINCOS_3_CENTER)
      .value("SQUARE_0_CENTER", PanFilter<DataType>::PAN_LAWS::SQUARE_0_CENTER)
      .value("SQUARE_3_CENTER", PanFilter<DataType>::PAN_LAWS::SQUARE_3_CENTER)
      .value("LINEAR_TAPER", PanFilter<DataType>::PAN_LAWS::LINEAR_TAPER)
      .value("BALANCE", PanFilter<DataType>::PAN_LAWS::BALANCE)
      .export_values();
  }

  template<typename DataType, typename T>
  void populate_SinusGeneratorFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<SinusGeneratorFilter<DataType>>(m, type, parent)
    .def(py::init<>())
    .def_property("frequency", &SinusGeneratorFilter<DataType>::get_frequency, &SinusGeneratorFilter<DataType>::set_frequency)
    .def_property("volume", &SinusGeneratorFilter<DataType>::get_volume, &SinusGeneratorFilter<DataType>::set_volume)
    .def_property("offset", &SinusGeneratorFilter<DataType>::get_offset, &SinusGeneratorFilter<DataType>::set_offset)
    ;
  }

  template<typename DataType, typename T>
  void populate_SumFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<SumFilter<DataType>>(m, type, parent)
      .def(py::init<gsl::index, gsl::index>(), py::arg("nb_output_channels") = static_cast<gsl::index>(1), py::arg("summed_channels") = gsl::index(2));
  }

  template<typename DataType, typename T>
  void populate_TanFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<TanFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1));
  }

  template<typename DataType, typename T>
  void populate_VolumeFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<VolumeFilter<DataType>>(m, type, parent)
      .def(py::init<gsl::index>(), py::arg("nb_channels") = static_cast<gsl::index>(1))
      .def_property("volume", &VolumeFilter<DataType>::get_volume, &VolumeFilter<DataType>::set_volume);
  }
  
  template<typename DataType, typename T>
  void populate_WhiteNoiseGeneratorFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<WhiteNoiseGeneratorFilter<DataType>>(m, type, parent)
    .def(py::init<>())
    .def_property("volume", &WhiteNoiseGeneratorFilter<DataType>::get_volume, &WhiteNoiseGeneratorFilter<DataType>::set_volume)
    .def_property("offset", &WhiteNoiseGeneratorFilter<DataType>::get_offset, &WhiteNoiseGeneratorFilter<DataType>::set_offset);
  }
}

PYBIND11_MODULE(PythonTools, m)
{
  m.doc() = "Audio ToolKit Tools module";

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");
  py::object f3 = (py::object) py::module::import("ATK.Core").attr("ComplexFloatTypedBaseFilter");
  py::object f4 = (py::object) py::module::import("ATK.Core").attr("ComplexDoubleTypedBaseFilter");

  populate_ApplyGainFilter<float>(m, "FloatApplyGainFilter", f1);
  populate_ApplyGainFilter<double>(m, "DoubleApplyGainFilter", f2);
  populate_ApplyGainFilter<std::complex<float>>(m, "ComplexFloatApplyGainFilter", f3);
  populate_ApplyGainFilter<std::complex<double>>(m, "ComplexDoubleApplyGainFilter", f4);

  populate_BufferFilter<float>(m, "FloatBufferFilter", f1);
  populate_BufferFilter<double>(m, "DoubleBufferFilter", f2);
  populate_BufferFilter<std::complex<float>>(m, "ComplexFloatBufferFilter", f3);
  populate_BufferFilter<std::complex<double>>(m, "ComplexDoubleBufferFilter", f4);

  populate_DecimationFilter<float>(m, "FloatDecimationFilter", f1);
  populate_DecimationFilter<double>(m, "DoubleDecimationFilter", f2);
  populate_DecimationFilter<std::complex<float>>(m, "ComplexFloatDecimationFilter", f3);
  populate_DecimationFilter<std::complex<double>>(m, "ComplexDoubleDecimationFilter", f4);

  populate_DryWetFilter<float>(m, "FloatDryWetFilter", f1);
  populate_DryWetFilter<double>(m, "DoubleDryWetFilter", f2);
  populate_DryWetFilter<std::complex<float>>(m, "ComplexFloatDryWetFilter", f3);
  populate_DryWetFilter<std::complex<double>>(m, "ComplexDoubleDryWetFilter", f4);

  populate_MuteSoloBufferFilter<float>(m, "FloatMuteSoloBufferFilter", f1);
  populate_MuteSoloBufferFilter<double>(m, "DoubleMuteSoloBufferFilter", f2);
  populate_MuteSoloBufferFilter<std::complex<float>>(m, "ComplexFloatMuteSoloBufferFilter", f3);
  populate_MuteSoloBufferFilter<std::complex<double>>(m, "ComplexDoubleMuteSoloBufferFilter", f4);

  populate_MiddleSideFilter<float>(m, "FloatMiddleSideFilter", f1);
  populate_MiddleSideFilter<double>(m, "DoubleMiddleSideFilter", f2);
  populate_MiddleSideFilter<std::complex<float>>(m, "ComplexFloatMiddleSideFilter", f3);
  populate_MiddleSideFilter<std::complex<double>>(m, "ComplexDoubleMiddleSideFilter", f4);

  populate_OversamplingFilter<Oversampling6points5order_2<float>>(m, "FloatOversampling6points5order_2Filter", f1);
  populate_OversamplingFilter<Oversampling6points5order_2<double>>(m, "DoubleOversampling6points5order_2Filter", f2);
  populate_OversamplingFilter<Oversampling6points5order_4<float>>(m, "FloatOversampling6points5order_4Filter", f1);
  populate_OversamplingFilter<Oversampling6points5order_4<double>>(m, "DoubleOversampling6points5order_4Filter", f2);
  populate_OversamplingFilter<Oversampling6points5order_8<float>>(m, "FloatOversampling6points5order_8Filter", f1);
  populate_OversamplingFilter<Oversampling6points5order_8<double>>(m, "DoubleOversampling6points5order_8Filter", f2);
  populate_OversamplingFilter<Oversampling6points5order_16<float>>(m, "FloatOversampling6points5order_16Filter", f1);
  populate_OversamplingFilter<Oversampling6points5order_16<double>>(m, "DoubleOversampling6points5order_16Filter", f2);
  populate_OversamplingFilter<Oversampling6points5order_32<float>>(m, "FloatOversampling6points5order_32Filter", f1);
  populate_OversamplingFilter<Oversampling6points5order_32<double>>(m, "DoubleOversampling6points5order_32Filter", f2);

  populate_PanFilter<float>(m, "FloatPanFilter", f1);
  populate_PanFilter<double>(m, "DoublePanFilter", f2);
  populate_PanFilter<std::complex<float>>(m, "ComplexFloatPanFilter", f3);
  populate_PanFilter<std::complex<double>>(m, "ComplexDoublePanFilter", f4);

  populate_SinusGeneratorFilter<float>(m, "FloatSinusGeneratorFilter", f1);
  populate_SinusGeneratorFilter<double>(m, "DoubleSinusGeneratorFilter", f2);

  populate_SumFilter<float>(m, "FloatSumFilter", f1);
  populate_SumFilter<double>(m, "DoubleSumFilter", f2);
  populate_SumFilter<std::complex<float>>(m, "ComplexFloatSumFilter", f3);
  populate_SumFilter<std::complex<double>>(m, "ComplexDoubleSumFilter", f4);
  
  populate_TanFilter<float>(m, "FloatTanFilter", f1);
  populate_TanFilter<double>(m, "DoubleTanFilter", f2);

  populate_VolumeFilter<float>(m, "FloatVolumeFilter", f1);
  populate_VolumeFilter<double>(m, "DoubleVolumeFilter", f2);
  populate_VolumeFilter<std::complex<float>>(m, "ComplexFloatVolumeFilter", f3);
  populate_VolumeFilter<std::complex<double>>(m, "ComplexDoubleVolumeFilter", f4);

  populate_WhiteNoiseGeneratorFilter<float>(m, "FloatWhiteNoiseGeneratorFilter", f1);
  populate_WhiteNoiseGeneratorFilter<double>(m, "DoubleWhiteNoiseGeneratorFilter", f2);
}
