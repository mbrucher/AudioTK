/**
 * \file DecimationFilter.cpp
 */

#include "DecimationFilter.hxx"

#include <complex>
#include <cstdint>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class DecimationFilter<std::int16_t>;
  template class DecimationFilter<std::int32_t>;
  template class DecimationFilter<int64_t>;
  template class DecimationFilter<float>;
  template class DecimationFilter<std::complex<float>>;
  template class DecimationFilter<std::complex<double>>;
#endif
  template class DecimationFilter<double>;
}
