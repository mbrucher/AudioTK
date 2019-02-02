/**
 * \file TimeVaryingSVFFilters.h
 */

#ifndef PYTHON_ATK_EQ_TIMEVARYINGSVFFILTERS_H
#define PYTHON_ATK_EQ_TIMEVARYINGSVFFILTERS_H

#include <pybind11/pybind11.h>

void populate_TimeVaryingSVFFilters(pybind11::module& m,
#if ATK_ENABLE_INSTANTIATION
  const pybind11::object& f1,
#endif
  const pybind11::object& f2);

#endif
