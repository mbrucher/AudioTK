/**
 * \file ApplyGainFilter.h
 */

#include <ATK/Tools/ApplyGainFilter.hxx>

#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template class ApplyGainFilter<float>;
  template class ApplyGainFilter<double>;
  template class ApplyGainFilter<std::complex<float>>;
  template class ApplyGainFilter<std::complex<double>>;
}
