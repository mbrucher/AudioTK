/**
 * \file UniversalFixedDelayLineFilter.cpp
 */

#include "UniversalFixedDelayLineFilter.hxx"

#include <complex>

namespace ATK
{
  template class UniversalFixedDelayLineFilter<double>;
#if ATK_ENABLE_INSTANTIATION
  template class UniversalFixedDelayLineFilter<float>;
  template class UniversalFixedDelayLineFilter<std::complex<float>>;
  template class UniversalFixedDelayLineFilter<std::complex<double>>;
#endif
}
