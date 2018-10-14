/**
 * \file ChebyshevFilter.h
 */

#ifndef PYTHON_ATK_EQ_CHEBYSHEVFILTERS_H
#define PYTHON_ATK_EQ_CHEBYSHEVFILTERS_H

#include <pybind11/pybind11.h>

void populate_ChebyshevFilter(pybind11::module& m,
#if ATK_ENABLE_INSTANTIATION
  const pybind11::object& f1,
#endif
  const pybind11::object& f2);

#endif
