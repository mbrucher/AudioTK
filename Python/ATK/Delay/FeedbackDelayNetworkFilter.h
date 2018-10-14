/**
 * \file FeedbackDelayNetworkFilter.h
 */

#ifndef PYTHON_ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_H
#define PYTHON_ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_H

#include <pybind11/pybind11.h>

void populate_FeedbackDelayNetworkFilter(pybind11::module& m, const pybind11::object& f2
#if ATK_ENABLE_INSTANTIATION
    , const pybind11::object& f1, const pybind11::object& f3, const pybind11::object& f4
#endif
);

#endif
