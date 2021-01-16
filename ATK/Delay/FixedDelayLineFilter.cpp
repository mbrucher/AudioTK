/**
 * \file FixedDelayLineFilter.cpp
 */

#include "FixedDelayLineFilter.hxx"

#include <complex>

namespace ATK
{
  template class FixedDelayLineFilter<double>;
#if ATK_ENABLE_INSTANTIATION
  template class FixedDelayLineFilter<float>;
  template class FixedDelayLineFilter<std::complex<float>>;
  template class FixedDelayLineFilter<std::complex<double>>;
#endif
}
