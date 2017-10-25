/**
 * \file VolumeFilter.cpp
 */

#include <ATK/Tools/VolumeFilter.hxx>

#include <complex>
#include <cstdint>

namespace ATK
{
  template class VolumeFilter<std::int16_t>;
  template class VolumeFilter<std::int32_t>;
  template class VolumeFilter<std::int64_t>;
  template class VolumeFilter<float>;
  template class VolumeFilter<double>;
  template class VolumeFilter<std::complex<float>>;
  template class VolumeFilter<std::complex<double>>;
}
