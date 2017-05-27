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

#include <ATK/Delay/FeedbackDelayNetworkFilter.h>
#include <ATK/Delay/HadamardMixture.h>
#include <ATK/Delay/HouseholderMixture.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType, typename T>
  void populate_FixedDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<FixedDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("max_delay"))
    .def_property("delay", &FixedDelayLineFilter<DataType>::get_delay, &FixedDelayLineFilter<DataType>::set_delay);
  }

  template<typename DataType, typename T>
  void populate_VariableDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<VariableDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("max_delay"));
  }
  
  template<typename DataType, typename T>
  void populate_UniversalFixedDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<UniversalFixedDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("max_delay"))
    .def_property("delay", &UniversalFixedDelayLineFilter<DataType>::get_delay, &UniversalFixedDelayLineFilter<DataType>::set_delay)
    .def_property("blend", &UniversalFixedDelayLineFilter<DataType>::get_blend, &UniversalFixedDelayLineFilter<DataType>::set_blend)
    .def_property("feedback", &UniversalFixedDelayLineFilter<DataType>::get_feedback, &UniversalFixedDelayLineFilter<DataType>::set_feedback)
    .def_property("feedforward", &UniversalFixedDelayLineFilter<DataType>::get_feedforward, &UniversalFixedDelayLineFilter<DataType>::set_feedforward);
  }
  
  template<typename DataType, int size, typename T>
  void populate_MultipleUniversalFixedDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<MultipleUniversalFixedDelayLineFilter<DataType, size>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("max_delay"))
    .def("get_delay", &UniversalFixedDelayLineFilter<DataType>::get_delay, "channel")
    .def("set_delay", &UniversalFixedDelayLineFilter<DataType>::set_delay, "channel", "delay")
    .def("get_blend", &UniversalFixedDelayLineFilter<DataType>::get_blend, "channel")
    .def("set_blend", &UniversalFixedDelayLineFilter<DataType>::set_blend, "channel", "blend")
    .def("get_feedback", &UniversalFixedDelayLineFilter<DataType>::get_feedback, "channel")
    .def("set_feedback", &UniversalFixedDelayLineFilter<DataType>::set_feedback, "channel", "feedback")
    .def("get_feedforward", &UniversalFixedDelayLineFilter<DataType>::get_feedforward, "channel")
    .def("set_feedback", &UniversalFixedDelayLineFilter<DataType>::set_feedforward, "channel", "feedforward");
  }
  
  template<typename DataType, typename T>
  void populate_UniversalVariableDelayLineFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<UniversalVariableDelayLineFilter<DataType>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("max_delay"))
    .def_property("central_delay", &UniversalVariableDelayLineFilter<DataType>::get_central_delay, &UniversalVariableDelayLineFilter<DataType>::set_central_delay)
    .def_property("blend", &UniversalVariableDelayLineFilter<DataType>::get_blend, &UniversalVariableDelayLineFilter<DataType>::set_blend)
    .def_property("feedback", &UniversalVariableDelayLineFilter<DataType>::get_feedback, &UniversalVariableDelayLineFilter<DataType>::set_feedback)
    .def_property("feedforward", &UniversalVariableDelayLineFilter<DataType>::get_feedforward, &UniversalVariableDelayLineFilter<DataType>::set_feedforward);
  }

  
  template<typename Mixture, typename T>
  void populate_FeedbackDelayNetworkFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<FeedbackDelayNetworkFilter<Mixture>>(m, type, parent)
    .def(py::init<std::size_t>(), py::arg("max_delay"))
    .def("get_delay", &FeedbackDelayNetworkFilter<Mixture>::get_delay, "channel")
    .def("set_delay", &FeedbackDelayNetworkFilter<Mixture>::set_delay, "channel", "delay")
    .def("get_ingain", &FeedbackDelayNetworkFilter<Mixture>::get_ingain, "channel")
    .def("set_ingain", &FeedbackDelayNetworkFilter<Mixture>::set_ingain, "channel", "ingain")
    .def("get_feedback", &FeedbackDelayNetworkFilter<Mixture>::get_feedback, "channel")
    .def("set_feedback", &FeedbackDelayNetworkFilter<Mixture>::set_feedback, "channel", "feedback")
    .def("get_outgain", &FeedbackDelayNetworkFilter<Mixture>::get_outgain, "channel")
    .def("set_outgain", &FeedbackDelayNetworkFilter<Mixture>::set_outgain, "channel", "outgain");
  }
}

PYBIND11_PLUGIN(PythonDelay) {
  py::module m("PythonDelay", "Audio ToolKit Delay module");

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");
  py::object f3 = (py::object) py::module::import("ATK.Core").attr("ComplexFloatTypedBaseFilter");
  py::object f4 = (py::object) py::module::import("ATK.Core").attr("ComplexDoubleTypedBaseFilter");
  
  populate_FixedDelayLineFilter<float>(m, "FloatFixedDelayLineFilter", f1);
  populate_FixedDelayLineFilter<double>(m, "DoubleFixedDelayLineFilter", f2);
  populate_FixedDelayLineFilter<std::complex<float>>(m, "ComplexFloatFixedDelayLineFilter", f3);
  populate_FixedDelayLineFilter<std::complex<double>>(m, "ComplexDoubleFixedDelayLineFilter", f4);
  
  populate_UniversalFixedDelayLineFilter<float>(m, "FloatUniversalFixedDelayLineFilter", f1);
  populate_UniversalFixedDelayLineFilter<double>(m, "DoubleUniversalFixedDelayLineFilter", f2);
  populate_UniversalFixedDelayLineFilter<std::complex<float>>(m, "ComplexFloatUniversalFixedDelayLineFilter", f3);
  populate_UniversalFixedDelayLineFilter<std::complex<double>>(m, "ComplexDoubleUniversalFixedDelayLineFilter", f4);
  
  populate_UniversalVariableDelayLineFilter<float>(m, "FloatUniversalVariableDelayLineFilter", f1);
  populate_UniversalVariableDelayLineFilter<double>(m, "DoubleUniversalVariableDelayLineFilter", f2);
  
  populate_VariableDelayLineFilter<float>(m, "FloatVariableDelayLineFilter", f1);
  populate_VariableDelayLineFilter<double>(m, "DoubleVariableDelayLineFilter", f2);
  
  populate_MultipleUniversalFixedDelayLineFilter<float, 2>(m, "FloatDualMultipleUniversalFixedDelayLineFilter", f1);
  populate_MultipleUniversalFixedDelayLineFilter<double, 2>(m, "DoubleDualMultipleUniversalFixedDelayLineFilter", f2);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<float>, 2>(m, "ComplexFloatDualMultipleUniversalFixedDelayLineFilter", f3);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<double>, 2>(m, "ComplexDoubleDualMultipleUniversalFixedDelayLineFilter", f4);
  
  populate_MultipleUniversalFixedDelayLineFilter<float, 4>(m, "FloatQuadMultipleUniversalFixedDelayLineFilter", f1);
  populate_MultipleUniversalFixedDelayLineFilter<double, 4>(m, "DoubleQuadMultipleUniversalFixedDelayLineFilter", f2);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<float>, 4>(m, "ComplexFloatQuadMultipleUniversalFixedDelayLineFilter", f3);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<double>, 4>(m, "ComplexDoubleQuadMultipleUniversalFixedDelayLineFilter", f4);
  
  populate_MultipleUniversalFixedDelayLineFilter<float, 8>(m, "FloatOctMultipleUniversalFixedDelayLineFilter", f1);
  populate_MultipleUniversalFixedDelayLineFilter<double, 8>(m, "DoubleOctMultipleUniversalFixedDelayLineFilter", f2);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<float>, 8>(m, "ComplexFloatOctMultipleUniversalFixedDelayLineFilter", f3);
  populate_MultipleUniversalFixedDelayLineFilter<std::complex<double>, 8>(m, "ComplexDoubleOctMultipleUniversalFixedDelayLineFilter", f4);
  
  populate_FeedbackDelayNetworkFilter<HadamardMixture<float, 1>>(m, "FloatDualHadamardFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<double, 1>>(m, "DoubleDualHadamardFeedbackDelayNetworkFilter", f2);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 1>>(m, "ComplexFloatDualHadamardFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 1>>(m, "ComplexDoubleDualHadamardFeedbackDelayNetworkFilter", f4);
  
  populate_FeedbackDelayNetworkFilter<HadamardMixture<float, 2>>(m, "FloatQuadHadamardFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<double, 2>>(m, "DoubleQuadHadamardFeedbackDelayNetworkFilter", f2);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 2>>(m, "ComplexFloatQuadHadamardFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 2>>(m, "ComplexDoubleQuadHadamardFeedbackDelayNetworkFilter", f4);
  
  populate_FeedbackDelayNetworkFilter<HadamardMixture<float, 3>>(m, "FloatOctHadamardFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<double, 3>>(m, "DoubleOctHadamardFeedbackDelayNetworkFilter", f2);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 3>>(m, "ComplexFloatOctHadamardFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 3>>(m, "ComplexDoubleOctHadamardFeedbackDelayNetworkFilter", f4);
  
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<float, 2>>(m, "FloatDualHouseholderFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<double, 2>>(m, "DoubleDualHouseholderFeedbackDelayNetworkFilter", f2);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 2>>(m, "ComplexFloatDualHouseholderFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 2>>(m, "ComplexDoubleDualHouseholderFeedbackDelayNetworkFilter", f4);
  
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<float, 4>>(m, "FloatQuadHouseholderFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<double, 4>>(m, "DoubleQuadHouseholderFeedbackDelayNetworkFilter", f2);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 4>>(m, "ComplexFloatQuadHouseholderFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 4>>(m, "ComplexDoubleQuadHouseholderFeedbackDelayNetworkFilter", f4);
  
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<float, 8>>(m, "FloatOctHouseholderFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<double, 8>>(m, "DoubleOctHouseholderFeedbackDelayNetworkFilter", f2);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 8>>(m, "ComplexFloatOctHouseholderFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 8>>(m, "ComplexDoubleOctHouseholderFeedbackDelayNetworkFilter", f4);

  return m.ptr();
}
