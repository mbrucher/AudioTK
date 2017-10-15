/**
 * \file DryWetFilter.cpp
 */

#include <ATK/Tools/DryWetFilter.hxx>

#include <complex>

namespace ATK
{
  template class DryWetFilter<std::int16_t>;
  template class DryWetFilter<std::int32_t>;
  template class DryWetFilter<std::int64_t>;
  template class DryWetFilter<float>;
  template class DryWetFilter<double>;
  template class DryWetFilter<std::complex<float>>;
  template class DryWetFilter<std::complex<double>>;
}
