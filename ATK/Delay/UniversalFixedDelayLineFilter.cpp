/**
 * \file UniversalFixedDelayLineFilter.cpp
 */

#include <ATK/Delay/UniversalFixedDelayLineFilter.hxx>

#include <complex>

namespace ATK
{
  template class UniversalFixedDelayLineFilter<float>;
  template class UniversalFixedDelayLineFilter<double>;
  template class UniversalFixedDelayLineFilter<std::complex<float>>;
  template class UniversalFixedDelayLineFilter<std::complex<double>>;
}
