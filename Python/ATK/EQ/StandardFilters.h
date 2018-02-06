/**
 * \file StandardFilters.h
 */

#ifndef PYTHON_ATK_EQ_STANDARDFILTERS_H
#define PYTHON_ATK_EQ_STANDARDFILTERS_H

#include <pybind11/pybind11.h>

void populate_StandardFilters(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2);

#endif
