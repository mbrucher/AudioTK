/**
 * \file SumFilter.cpp
 */

#include <ATK/Tools/SumFilter.hxx>

#include <cstdint>
#include <cstring>

namespace ATK
{
  template class SumFilter<std::int16_t>;
  template class SumFilter<std::int32_t>;
  template class SumFilter<std::int64_t>;
  template class SumFilter<float>;
  template class SumFilter<double>;
  template class SumFilter<std::complex<float>>;
  template class SumFilter<std::complex<double>>;
}
