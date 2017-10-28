/**
 * \file OffsetVolumeFilter.cpp
 */

#include <ATK/Tools/OffsetVolumeFilter.hxx>

#include <complex>

namespace ATK
{
  template class OffsetVolumeFilter<float>;
  template class OffsetVolumeFilter<double>;
  template class OffsetVolumeFilter<std::complex<float>>;
  template class OffsetVolumeFilter<std::complex<double>>;
}
