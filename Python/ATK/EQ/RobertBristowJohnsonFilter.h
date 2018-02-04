/**
 * \file RobertBristowJohnsonFilter.h
 */

#ifndef PYTHON_ATK_EQ_ROBERTBRISTOWJOHNSONFILTER_H
#define PYTHON_ATK_EQ_ROBERTBRISTOWJOHNSONFILTER_H

#include <pybind11/pybind11.h>

namespace ATK
{
  void populate_RobertBristowJohnsonFilter(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2);
}

#endif
