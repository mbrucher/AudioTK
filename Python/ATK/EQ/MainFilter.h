/**
 * \file StandardFilters.h
 */

#ifndef PYTHON_ATK_EQ_STANDARD_FILTERS_H
#define PYTHON_ATK_EQ_STANDARD_FILTERS_H

#include <pybind11/pybind11.h>

#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  using namespace pybind11::literals;
  
  template<typename Coefficients>
  void populate_IIRFilter(pybind11::module& m, const char* type)
  {
    typedef typename Coefficients::DataType DataType;
    pybind11::class_<IIRFilter<Coefficients>, Coefficients>(m, type)
    .def(pybind11::init<std::size_t>(), "nb_channels"_a = 1)
    .def_property_readonly("coefficients_in", [](const IIRFilter<Coefficients>& instance)
                           {
                             return pybind11::array_t<DataType>(instance.get_coefficients_in().size(), instance.get_coefficients_in().data());
                           })
    .def_property_readonly("coefficients_out", [](const IIRFilter<Coefficients>& instance)
                           {
                             return pybind11::array_t<DataType>(instance.get_coefficients_out().size(), instance.get_coefficients_out().data());
                           });
  }

  
  template<typename Coefficients>
  void populate_DirectCoefficients(pybind11::module& m, const char* type)
  {
    pybind11::class_<Coefficients, typename Coefficients::Parent>(m, type);
  }
  
  template<typename Coefficients>
  void populate_QCoefficients(pybind11::module& m, const char* type)
  {
    pybind11::class_<Coefficients, typename Coefficients::Parent>(m, type)
    .def_property("Q", &Coefficients::get_Q, &Coefficients::set_Q);
  }
  
  template<typename Coefficients>
  void populate_shelfCoefficients(pybind11::module& m, const char* type)
  {
    pybind11::class_<Coefficients, typename Coefficients::Parent>(m, type)
    .def_property("gain", &Coefficients::get_gain, &Coefficients::set_gain);
  }
  
  template<typename Coefficients>
  void populate_QshelfCoefficients(pybind11::module& m, const char* type)
  {
    pybind11::class_<Coefficients, typename Coefficients::Parent>(m, type)
    .def_property("Q", &Coefficients::get_Q, &Coefficients::set_Q)
    .def_property("gain", &Coefficients::get_gain, &Coefficients::set_gain);
  }
}

#endif
