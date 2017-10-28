/**
 * \file OneMinusFilter.cpp
 */

#include <ATK/Tools/OneMinusFilter.hxx>

#include <complex>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template class OneMinusFilter<float>;
  template class OneMinusFilter<double>;
  template class OneMinusFilter<std::complex<float>>;
  template class OneMinusFilter<std::complex<double>>;
}
