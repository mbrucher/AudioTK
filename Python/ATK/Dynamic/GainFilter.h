/**
 * \file GainFilter.h
 */

#ifndef PYTHON_ATK_DYNAMIC_GAINFILTER_H
#define PYTHON_ATK_DYNAMIC_GAINFILTER_H

#include <pybind11/pybind11.h>

void populate_GainFilter(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2);

#endif
