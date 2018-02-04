/**
 * \file SecondOrderSVFFilter.h
 */

#ifndef PYTHON_ATK_EQ_SECONDORDERSVFFILTERS_H
#define PYTHON_ATK_EQ_SECONDORDERSVFFILTERS_H

#include <pybind11/pybind11.h>

void populate_SecondOrderSVFFilter(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2);

#endif
