/**
 * \file MaxFilter.cpp
 */

#include <ATK/Tools/MaxFilter.hxx>

namespace ATK
{
  template class MaxFilter<std::int16_t>;
  template class MaxFilter<std::int32_t>;
  template class MaxFilter<int64_t>;
  template class MaxFilter<float>;
  template class MaxFilter<double>;
}
