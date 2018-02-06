/**
 * \file Core.cpp
 */

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Core/ComplexConvertFilter.h>
#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/PipelineGlobalSinkFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType_, typename DataType__ = DataType_>
  void populate_TypedBaseFilter(py::module& m, const char* type)
  {
    py::class_<TypedBaseFilter<DataType_, DataType__>, BaseFilter>(m, type)
      .def("get_output_array", [](TypedBaseFilter<DataType__>& instance, std::size_t port)
    {
      if (port >= instance.get_nb_output_ports())
      {
        throw std::length_error("No port with this number");
      }
      return py::array_t<DataType__>(instance.get_output_array_size(), instance.get_output_array(port));
    });
  }

  void create_base_filter(py::module& m)
  {
    py::class_<BaseFilter>(m, "BaseFilter")
    .def("set_input_port", [](BaseFilter& instance, std::size_t input_port, BaseFilter& filter, std::size_t output_port){instance.set_input_port(input_port, filter, output_port);})
      .def("process", &BaseFilter::process)
      .def("full_setup", &BaseFilter::full_setup)
      .def_property("input_sampling_rate", &BaseFilter::get_input_sampling_rate, &BaseFilter::set_input_sampling_rate)
      .def_property("output_sampling_rate", &BaseFilter::get_output_sampling_rate, &BaseFilter::set_output_sampling_rate)
      .def_property("input_delay", &BaseFilter::get_input_delay, &BaseFilter::set_input_delay)
      .def_property("output_delay", &BaseFilter::get_output_delay, &BaseFilter::set_output_delay)
      .def_property("nb_input_ports", &BaseFilter::get_nb_input_ports, &BaseFilter::set_nb_input_ports)
      .def_property("nb_output_ports", &BaseFilter::get_nb_output_ports, &BaseFilter::set_nb_output_ports)
      .def_property("latency", &BaseFilter::get_latency, &BaseFilter::set_latency)
      .def_property_readonly("global_latency", &BaseFilter::get_global_latency);

    populate_TypedBaseFilter<int16_t>(m, "Int16TypedBaseFilter");
    populate_TypedBaseFilter<int32_t>(m, "Int32TypedBaseFilter");
    populate_TypedBaseFilter<int64_t>(m, "Int64TypedBaseFilter");
    populate_TypedBaseFilter<float>(m, "FloatTypedBaseFilter");
    populate_TypedBaseFilter<double>(m, "DoubleTypedBaseFilter");
    populate_TypedBaseFilter<std::complex<float>>(m, "ComplexFloatTypedBaseFilter");
    populate_TypedBaseFilter<std::complex<double>>(m, "ComplexDoubleTypedBaseFilter");
    populate_TypedBaseFilter<std::complex<float>, float>(m, "ComplexFloatFloatTypedBaseFilter");
    populate_TypedBaseFilter<std::complex<double>, double>(m, "ComplexDoubleDoubleTypedBaseFilter");
    populate_TypedBaseFilter<float, std::complex<float>>(m, "FloatComplexFloatTypedBaseFilter");
    populate_TypedBaseFilter<double, std::complex<double>>(m, "DoubleComplexDoubleTypedBaseFilter");
  }

  template<typename DataType>
  void populate_InPointerFilter(py::module& m, const char* type)
  {
    py::class_<InPointerFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def("__init__", [](InPointerFilter<DataType>& instance, const py::array_t<DataType>& array, bool interleaved) {
        std::size_t channels = 1;
        std::size_t size = array.shape(0);
        if(array.ndim() == 2)
        {
          channels = array.shape(0);
          size = array.shape(1);
        }
        new (&instance) InPointerFilter<DataType>(array.data(), channels, size, interleaved);
    }, py::arg().noconvert(), py::arg("interleaved") = false)
      .def("set_pointer", [](InPointerFilter<DataType>& instance, const py::array_t<DataType>& array)
    {
      std::size_t channels = 1;
      std::size_t size = array.shape(0);
      if(array.ndim() == 2)
      {
        channels = array.shape(0);
        size = array.shape(1);
      }
      if (channels != instance.get_nb_output_ports())
      {
        throw std::length_error("Wrong size for the number of channels");
      }
      instance.set_pointer(array.data(), array.ndim() == 2 ? array.shape(1) : array.shape(0));
    });
  }

  template<typename DataType>
  void populate_OutPointerFilter(py::module& m, const char* type)
  {
    py::class_<OutPointerFilter<DataType>, TypedBaseFilter<DataType>>(m, type)
      .def("__init__", [](OutPointerFilter<DataType>& instance, py::array_t<DataType>& array, bool interleaved) {
        std::size_t channels = 1;
        std::size_t size = array.shape(0);
        if(array.ndim() == 2)
        {
          channels = array.shape(0);
          size = array.shape(1);
        }
      new (&instance) OutPointerFilter<DataType>(array.mutable_data(), channels, size, interleaved);
    }, py::arg().noconvert(), py::arg("interleaved") = false)
      .def("set_pointer", [](OutPointerFilter<DataType>& instance, py::array_t<DataType>& array)
    {
      std::size_t channels = 1;
      std::size_t size = array.shape(0);
      if(array.ndim() == 2)
      {
        channels = array.shape(0);
        size = array.shape(1);
      }
      if (channels != instance.get_nb_input_ports())
      {
        throw std::length_error("Wrong size for the number of channels");
      }
      instance.set_pointer(array.mutable_data(), array.ndim() == 2 ? array.shape(1) : array.shape(0));
    });
  }
  
  template<typename DataType>
  void populate_ComplexToRealFilter(py::module& m, const char* type)
  {
    py::class_<ComplexToRealFilter<DataType>, TypedBaseFilter<std::complex<DataType>, DataType>>(m, type)
    .def(py::init<std::size_t>(), py::arg("nb_channels") = 1);
  }

  template<typename DataType>
  void populate_RealToComplexFilter(py::module& m, const char* type)
  {
    py::class_<RealToComplexFilter<DataType>, TypedBaseFilter<DataType, std::complex<DataType>>>(m, type)
    .def(py::init<std::size_t>(), py::arg("nb_channels") = 1);
  }
}

PYBIND11_MODULE(PythonCore, m) {
  m.doc() = "Audio ToolKit Core module";

  create_base_filter(m);
  populate_InPointerFilter<int16_t>(m, "Int16InPointerFilter");
  populate_InPointerFilter<int32_t>(m, "Int32InPointerFilter");
  populate_InPointerFilter<int64_t>(m, "Int64InPointerFilter");
  populate_InPointerFilter<float>(m, "FloatInPointerFilter");
  populate_InPointerFilter<double>(m, "DoubleInPointerFilter");
  populate_InPointerFilter<std::complex<float>>(m, "ComplexFloatInPointerFilter");
  populate_InPointerFilter<std::complex<double>>(m, "ComplexDoubleInPointerFilter");
  populate_OutPointerFilter<int16_t>(m, "Int16OutPointerFilter");
  populate_OutPointerFilter<int32_t>(m, "Int32OutPointerFilter");
  populate_OutPointerFilter<int64_t>(m, "Int64OutPointerFilter");
  populate_OutPointerFilter<float>(m, "FloatOutPointerFilter");
  populate_OutPointerFilter<double>(m, "DoubleOutPointerFilter");
  populate_OutPointerFilter<std::complex<float>>(m, "ComplexFloatOutPointerFilter");
  populate_OutPointerFilter<std::complex<double>>(m, "ComplexDoubleOutPointerFilter");

  py::class_<PipelineGlobalSinkFilter, BaseFilter>(m, "PipelineGlobalSinkFilter")
    .def(py::init())
    .def("add_filter", [](PipelineGlobalSinkFilter& instance, BaseFilter& filter){instance.add_filter(&filter);})
    .def("remove_filter", [](PipelineGlobalSinkFilter& instance, BaseFilter& filter){instance.remove_filter(&filter);});
  
  populate_ComplexToRealFilter<float>(m, "FloatComplexToRealFilter");
  populate_ComplexToRealFilter<double>(m, "DoubleComplexToRealFilter");
  populate_RealToComplexFilter<float>(m, "FloatRealToComplexFilter");
  populate_RealToComplexFilter<double>(m, "DoubleRealToComplexFilter");
}
