/**
* \file Delay.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Delay/FixedDelayLineFilter.h>
#include <ATK/Delay/MultipleUniversalFixedDelayLineFilter.h>
#include <ATK/Delay/UniversalFixedDelayLineFilter.h>
#include <ATK/Delay/UniversalVariableDelayLineFilter.h>
#include <ATK/Delay/VariableDelayLineFilter.h>

#include "FeedbackDelayNetworkFilter.h"

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType, typename T>
  void populate_FixedDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<FixedDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("max_delay"))
    .def_property("delay", &FixedDelayLineFilter<DataType>::get_delay, &FixedDelayLineFilter<DataType>::set_delay);
  }

  template<typename DataType, typename T>
  void populate_VariableDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<VariableDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("max_delay"));
  }
  
  template<typename DataType, typename T>
  void populate_UniversalFixedDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<UniversalFixedDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("max_delay"))
    .def_property("delay", &UniversalFixedDelayLineFilter<DataType>::get_delay, &UniversalFixedDelayLineFilter<DataType>::set_delay)
    .def_property("blend", &UniversalFixedDelayLineFilter<DataType>::get_blend, &UniversalFixedDelayLineFilter<DataType>::set_blend)
    .def_property("feedback", &UniversalFixedDelayLineFilter<DataType>::get_feedback, &UniversalFixedDelayLineFilter<DataType>::set_feedback)
    .def_property("feedforward", &UniversalFixedDelayLineFilter<DataType>::get_feedforward, &UniversalFixedDelayLineFilter<DataType>::set_feedforward);
  }
  
  template<typename DataType, gsl::index size, typename T>
  void populate_MultipleUniversalFixedDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<MultipleUniversalFixedDelayLineFilter<DataType, size>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("max_delay"))
    .def("get_delay", &MultipleUniversalFixedDelayLineFilter<DataType, size>::get_delay, py::arg("channel"))
    .def("set_delay", &MultipleUniversalFixedDelayLineFilter<DataType, size>::set_delay, py::arg("channel"), py::arg("delay"))
    .def("get_blend", &MultipleUniversalFixedDelayLineFilter<DataType, size>::get_blend, py::arg("channel"))
    .def("set_blend", &MultipleUniversalFixedDelayLineFilter<DataType, size>::set_blend, py::arg("channel"), py::arg("blend"))
    .def("get_feedback", &MultipleUniversalFixedDelayLineFilter<DataType, size>::get_feedback, py::arg("channel_from"), py::arg("channel_to"))
    .def("set_feedback", &MultipleUniversalFixedDelayLineFilter<DataType, size>::set_feedback, py::arg("channel_from"), py::arg("channel_to"), py::arg("feedback"))
    .def("get_feedforward", &MultipleUniversalFixedDelayLineFilter<DataType, size>::get_feedforward, py::arg("channel_from"), py::arg("channel_to"))
    .def("set_feedforward", &MultipleUniversalFixedDelayLineFilter<DataType, size>::set_feedforward, py::arg("channel_from"), py::arg("channel_to"), py::arg("feedforward"));
  }
  
  template<typename DataType, typename T>
  void populate_UniversalVariableDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<UniversalVariableDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("max_delay"))
    .def_property("central_delay", &UniversalVariableDelayLineFilter<DataType>::get_central_delay, &UniversalVariableDelayLineFilter<DataType>::set_central_delay)
    .def_property("blend", &UniversalVariableDelayLineFilter<DataType>::get_blend, &UniversalVariableDelayLineFilter<DataType>::set_blend)
    .def_property("feedback", &UniversalVariableDelayLineFilter<DataType>::get_feedback, &UniversalVariableDelayLineFilter<DataType>::set_feedback)
    .def_property("feedforward", &UniversalVariableDelayLineFilter<DataType>::get_feedforward, &UniversalVariableDelayLineFilter<DataType>::set_feedforward);
  }

}

PYBIND11_MODULE(PythonDelay, m)
{
  m.doc() = "Audio ToolKit Delay module";

  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");
#if ATK_ENABLE_INSTANTIATION
  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f3 = (py::object) py::module::import("ATK.Core").attr("ComplexFloatTypedBaseFilter");
  py::object f4 = (py::object) py::module::import("ATK.Core").attr("ComplexDoubleTypedBaseFilter");
#endif

  populate_FixedDelayLineFilter<double>(m, "DoubleFixedDelayLineFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_FixedDelayLineFilter<float>(m, "FloatFixedDelayLineFilter", f1);
  populate_FixedDelayLineFilter<std::complex<float>>(m, "ComplexFloatFixedDelayLineFilter", f3);
  populate_FixedDelayLineFilter<std::complex<double>>(m, "ComplexDoubleFixedDelayLineFilter", f4);
#endif

  populate_UniversalFixedDelayLineFilter<double>(m, "DoubleUniversalFixedDelayLineFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_UniversalFixedDelayLineFilter<float>(m, "FloatUniversalFixedDelayLineFilter", f1);
  populate_UniversalFixedDelayLineFilter<std::complex<float>>(m, "ComplexFloatUniversalFixedDelayLineFilter", f3);
  populate_UniversalFixedDelayLineFilter<std::complex<double>>(m, "ComplexDoubleUniversalFixedDelayLineFilter", f4);
#endif

#if ATK_ENABLE_INSTANTIATION
  populate_UniversalVariableDelayLineFilter<float>(m, "FloatUniversalVariableDelayLineFilter", f1);
#endif
  populate_UniversalVariableDelayLineFilter<double>(m, "DoubleUniversalVariableDelayLineFilter", f2);
  
#if ATK_ENABLE_INSTANTIATION
  populate_VariableDelayLineFilter<float>(m, "FloatVariableDelayLineFilter", f1);
#endif
  populate_VariableDelayLineFilter<double>(m, "DoubleVariableDelayLineFilter", f2);
  
  populate_MultipleUniversalFixedDelayLineFilter<double, 2>(m, "DoubleDualMultipleUniversalFixedDelayLineFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_MultipleUniversalFixedDelayLineFilter<float, 2>(m, "FloatDualMultipleUniversalFixedDelayLineFilter", f1);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<float>, 2>(m, "ComplexFloatDualMultipleUniversalFixedDelayLineFilter", f3);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<double>, 2>(m, "ComplexDoubleDualMultipleUniversalFixedDelayLineFilter", f4);
#endif

  populate_MultipleUniversalFixedDelayLineFilter<double, 4>(m, "DoubleQuadMultipleUniversalFixedDelayLineFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_MultipleUniversalFixedDelayLineFilter<float, 4>(m, "FloatQuadMultipleUniversalFixedDelayLineFilter", f1);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<float>, 4>(m, "ComplexFloatQuadMultipleUniversalFixedDelayLineFilter", f3);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<double>, 4>(m, "ComplexDoubleQuadMultipleUniversalFixedDelayLineFilter", f4);
#endif

  populate_MultipleUniversalFixedDelayLineFilter<double, 8>(m, "DoubleOctMultipleUniversalFixedDelayLineFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_MultipleUniversalFixedDelayLineFilter<float, 8>(m, "FloatOctMultipleUniversalFixedDelayLineFilter", f1);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<float>, 8>(m, "ComplexFloatOctMultipleUniversalFixedDelayLineFilter", f3);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<double>, 8>(m, "ComplexDoubleOctMultipleUniversalFixedDelayLineFilter", f4);
#endif

  populate_FeedbackDelayNetworkFilter(m, f2
#if ATK_ENABLE_INSTANTIATION
  , f1, f3, f4
#endif
);
}
