/**
 * \file Core.cpp
 */

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/PipelineGlobalSinkFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType>
  void populate_TypedBaseFilter(py::module& m, const char* type)
  {
    py::class_<ATK::TypedBaseFilter<DataType>, ATK::BaseFilter>(m, type)
      .def("get_output_array", [](ATK::TypedBaseFilter<DataType>& instance, std::size_t port)
    {
      if (port >= instance.get_nb_output_ports())
      {
        throw std::length_error("No port with this number");
      }
      return py::array_t<DataType>(instance.get_output_array_size(), instance.get_output_array(port));
    });
  }

  void create_base_filter(py::module& m)
  {
    py::class_<ATK::BaseFilter>(m, "BaseFilter")
      .def("set_input_port", &ATK::BaseFilter::set_input_port)
      .def("process", &ATK::BaseFilter::process)
      .def("full_setup", &ATK::BaseFilter::full_setup)
      .def_property("input_sampling_rate", &ATK::BaseFilter::get_input_sampling_rate, &ATK::BaseFilter::set_input_sampling_rate)
      .def_property("output_sampling_rate", &ATK::BaseFilter::get_output_sampling_rate, &ATK::BaseFilter::set_output_sampling_rate)
      .def_property("input_delay", &ATK::BaseFilter::get_input_delay, &ATK::BaseFilter::set_input_delay)
      .def_property("output_delay", &ATK::BaseFilter::get_output_delay, &ATK::BaseFilter::set_output_delay)
      .def_property("nb_input_ports", &ATK::BaseFilter::get_nb_input_ports, &ATK::BaseFilter::set_nb_input_ports)
      .def_property("nb_output_ports", &ATK::BaseFilter::get_nb_output_ports, &ATK::BaseFilter::set_nb_output_ports)
      .def_property("latency", &ATK::BaseFilter::get_latency, &ATK::BaseFilter::set_latency)
      .def_property_readonly("global_latency", &ATK::BaseFilter::get_global_latency);

    populate_TypedBaseFilter<float>(m, "FloatTypedBaseFilter");
    populate_TypedBaseFilter<double>(m, "DoubleTypedBaseFilter");
    populate_TypedBaseFilter<std::complex<float>>(m, "ComplexFloatTypedBaseFilter");
    populate_TypedBaseFilter<std::complex<double>>(m, "ComplexDoubleTypedBaseFilter");
  }

  template<typename DataType>
  void populate_InPointerFilter(py::module& m, const char* type)
  {
    py::class_<ATK::InPointerFilter<DataType>, ATK::TypedBaseFilter<DataType>>(m, type)
      .def("__init__", [](ATK::InPointerFilter<DataType>& instance, const py::array_t<DataType>& array, bool interleaved) {
      new (&instance) ATK::InPointerFilter<DataType>(array.data(), array.shape(0), array.shape(1), interleaved);
    }/*, py::arg("interleaved") = false*/)
      .def("set_pointer", [](ATK::InPointerFilter<DataType>& instance, const py::array_t<DataType>& array)
    {
      if (array.shape(0) != instance.get_nb_output_ports())
      {
        throw std::length_error("Wrong size for the number of channels");
      }
      instance.set_pointer(array.data(), array.shape(1));
    });
  }

  template<typename DataType>
  void populate_OutPointerFilter(py::module& m, const char* type)
  {
    py::class_<ATK::OutPointerFilter<DataType>, ATK::TypedBaseFilter<DataType>>(m, type)
      .def("__init__", [](ATK::OutPointerFilter<DataType>& instance, py::array_t<DataType>& array, bool interleaved) {
      new (&instance) ATK::OutPointerFilter<DataType>(array.mutable_data(), array.shape(0), array.shape(1), interleaved);
    }/*, py::arg("interleaved") = false*/)
      .def("set_pointer", [](ATK::OutPointerFilter<DataType>& instance, py::array_t<DataType>& array)
    {
      if (array.shape(0) != instance.get_nb_input_ports())
      {
        throw std::length_error("Wrong size for the number of channels");
      }
      instance.set_pointer(array.mutable_data(), array.shape(1));
    });
  }
}

PYBIND11_PLUGIN(PythonCore) {
  py::module m("PythonCore", "Audio ToolKit Core module");

  create_base_filter(m);
  populate_InPointerFilter<float>(m, "FloatInPointerFilter");
  populate_InPointerFilter<double>(m, "DoubleInPointerFilter");
  populate_InPointerFilter<std::complex<float>>(m, "ComplexFloatInPointerFilter");
  populate_InPointerFilter<std::complex<double>>(m, "ComplexDoubleInPointerFilter");
  populate_OutPointerFilter<float>(m, "FloatOutPointerFilter");
  populate_OutPointerFilter<double>(m, "DoubleOutPointerFilter");
  populate_OutPointerFilter<std::complex<float>>(m, "ComplexFloatOutPointerFilter");
  populate_OutPointerFilter<std::complex<double>>(m, "ComplexDoubleOutPointerFilter");

  py::class_<ATK::PipelineGlobalSinkFilter, ATK::BaseFilter>(m, "PipelineGlobalSinkFilter")
    .def(py::init())
    .def("add_filter", &ATK::PipelineGlobalSinkFilter::add_filter)
    .def("remove_filter", &ATK::PipelineGlobalSinkFilter::remove_filter);
  return m.ptr();
}
