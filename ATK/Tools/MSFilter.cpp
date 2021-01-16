/**
 * \file MSFilter.cpp
 */

#include "MSFilter.hxx"

#include <complex>
#include <cstdint>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class MiddleSideFilter<std::int16_t>;
  template class MiddleSideFilter<std::int32_t>;
  template class MiddleSideFilter<std::int64_t>;
  template class MiddleSideFilter<float>;
  template class MiddleSideFilter<std::complex<float>>;
  template class MiddleSideFilter<std::complex<double>>;
#endif
  template class MiddleSideFilter<double>;
}
