/**
 * \file ApplyGainFilter.h
 */

#include "ApplyGainFilter.hxx"

#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class ApplyGainFilter<float>;
  template class ApplyGainFilter<std::complex<float>>;
  template class ApplyGainFilter<std::complex<double>>;
#endif
  template class ApplyGainFilter<double>;
}
