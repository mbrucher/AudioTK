/**
 * \file TimeVaryingIIRFilters.h
 */

#ifndef PYTHON_ATK_EQ_TIMEVARYINGIIRFILTERS_H
#define PYTHON_ATK_EQ_TIMEVARYINGIIRFILTERS_H

#include <pybind11/pybind11.h>

namespace ATK
{
  void populate_TimeVaryingIIRFilters(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2);
}

#endif
