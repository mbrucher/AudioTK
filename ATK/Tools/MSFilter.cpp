/**
 * \file MSFilter.cpp
 */

#include <ATK/Tools/MSFilter.hxx>

#include <complex>
#include <cstdint>

namespace ATK
{
  template class MiddleSideFilter<std::int16_t>;
  template class MiddleSideFilter<std::int32_t>;
  template class MiddleSideFilter<std::int64_t>;
  template class MiddleSideFilter<float>;
  template class MiddleSideFilter<double>;
  template class MiddleSideFilter<std::complex<float>>;
  template class MiddleSideFilter<std::complex<double>>;
}
