/**
 * \file OffsetVolumeFilter.cpp
 */

#include "OffsetVolumeFilter.hxx"

#include <complex>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class OffsetVolumeFilter<float>;
  template class OffsetVolumeFilter<std::complex<float>>;
  template class OffsetVolumeFilter<std::complex<double>>;
#endif
  template class OffsetVolumeFilter<double>;
}
