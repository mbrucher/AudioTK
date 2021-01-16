/**
 * \file VolumeFilter.cpp
 */

#include "VolumeFilter.hxx"

#include <complex>
#include <cstdint>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class VolumeFilter<std::int16_t>;
  template class VolumeFilter<std::int32_t>;
  template class VolumeFilter<std::int64_t>;
  template class VolumeFilter<std::complex<float>>;
  template class VolumeFilter<std::complex<double>>;
#endif
  template class VolumeFilter<float>;
  template class VolumeFilter<double>;
}
