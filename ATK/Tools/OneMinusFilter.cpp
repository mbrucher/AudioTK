/**
 * \file OneMinusFilter.cpp
 */

#include <ATK/Tools/OneMinusFilter.hxx>

#include <complex>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class OneMinusFilter<float>;
  template class OneMinusFilter<std::complex<float>>;
  template class OneMinusFilter<std::complex<double>>;
#endif
  template class OneMinusFilter<double>;
}
