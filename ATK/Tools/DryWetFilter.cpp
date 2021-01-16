/**
 * \file DryWetFilter.cpp
 */

#include "DryWetFilter.hxx"

#include <complex>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class DryWetFilter<std::int16_t>;
  template class DryWetFilter<std::int32_t>;
  template class DryWetFilter<std::int64_t>;
  template class DryWetFilter<float>;
  template class DryWetFilter<std::complex<float>>;
  template class DryWetFilter<std::complex<double>>;
#endif
  template class DryWetFilter<double>;
}
