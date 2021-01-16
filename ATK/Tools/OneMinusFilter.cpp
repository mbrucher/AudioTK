/**
 * \file OneMinusFilter.cpp
 */

#include "OneMinusFilter.hxx"
#include <ATK/Core/TypeTraits.h>

#include <complex>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class OneMinusFilter<float>;
  template class OneMinusFilter<std::complex<float>>;
  template class OneMinusFilter<std::complex<double>>;
#endif
  template class OneMinusFilter<double>;
}
