/**
* \file FeedbackDelayNetworkFilter.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Delay/FeedbackDelayNetworkFilter.h>
#include <ATK/Delay/HadamardMixture.h>
#include <ATK/Delay/HouseholderMixture.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename Mixture, typename T>
  void populate_FeedbackDelayNetworkFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<FeedbackDelayNetworkFilter<Mixture>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("max_delay"))
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

void populate_FeedbackDelayNetworkFilter(pybind11::module& m, const pybind11::object& f2
#if ATK_ENABLE_INSTANTIATION
    , const pybind11::object& f1, const pybind11::object& f3, const pybind11::object& f4
#endif
)
{
  populate_FeedbackDelayNetworkFilter<HadamardMixture<double, 1>>(m, "DoubleDualHadamardFeedbackDelayNetworkFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_FeedbackDelayNetworkFilter<HadamardMixture<float, 1>>(m, "FloatDualHadamardFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 1>>(m, "ComplexFloatDualHadamardFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 1>>(m, "ComplexDoubleDualHadamardFeedbackDelayNetworkFilter", f4);
#endif

  populate_FeedbackDelayNetworkFilter<HadamardMixture<double, 2>>(m, "DoubleQuadHadamardFeedbackDelayNetworkFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_FeedbackDelayNetworkFilter<HadamardMixture<float, 2>>(m, "FloatQuadHadamardFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 2>>(m, "ComplexFloatQuadHadamardFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 2>>(m, "ComplexDoubleQuadHadamardFeedbackDelayNetworkFilter", f4);
#endif

  populate_FeedbackDelayNetworkFilter<HadamardMixture<double, 3>>(m, "DoubleOctHadamardFeedbackDelayNetworkFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_FeedbackDelayNetworkFilter<HadamardMixture<float, 3>>(m, "FloatOctHadamardFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 3>>(m, "ComplexFloatOctHadamardFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 3>>(m, "ComplexDoubleOctHadamardFeedbackDelayNetworkFilter", f4);
#endif

  populate_FeedbackDelayNetworkFilter<HouseholderMixture<double, 2>>(m, "DoubleDualHouseholderFeedbackDelayNetworkFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<float, 2>>(m, "FloatDualHouseholderFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 2>>(m, "ComplexFloatDualHouseholderFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 2>>(m, "ComplexDoubleDualHouseholderFeedbackDelayNetworkFilter", f4);
#endif

  populate_FeedbackDelayNetworkFilter<HouseholderMixture<double, 4>>(m, "DoubleQuadHouseholderFeedbackDelayNetworkFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<float, 4>>(m, "FloatQuadHouseholderFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 4>>(m, "ComplexFloatQuadHouseholderFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 4>>(m, "ComplexDoubleQuadHouseholderFeedbackDelayNetworkFilter", f4);
#endif

  populate_FeedbackDelayNetworkFilter<HouseholderMixture<double, 8>>(m, "DoubleOctHouseholderFeedbackDelayNetworkFilter", f2);
#if ATK_ENABLE_INSTANTIATION
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<float, 8>>(m, "FloatOctHouseholderFeedbackDelayNetworkFilter", f1);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 8>>(m, "ComplexFloatOctHouseholderFeedbackDelayNetworkFilter", f3);
  populate_FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 8>>(m, "ComplexDoubleOctHouseholderFeedbackDelayNetworkFilter", f4);
#endif
}
