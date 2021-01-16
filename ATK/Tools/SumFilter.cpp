/**
 * \file SumFilter.cpp
 */

#include "SumFilter.hxx"

#include <cstdint>
#include <cstring>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class SumFilter<std::int16_t>;
  template class SumFilter<std::int32_t>;
  template class SumFilter<std::int64_t>;
  template class SumFilter<std::complex<float>>;
  template class SumFilter<std::complex<double>>;
#endif
  template class SumFilter<float>;
  template class SumFilter<double>;
}
