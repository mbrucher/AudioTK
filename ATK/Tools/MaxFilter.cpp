/**
 * \file MaxFilter.cpp
 */

#include "MaxFilter.hxx"

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class MaxFilter<std::int16_t>;
  template class MaxFilter<std::int32_t>;
  template class MaxFilter<int64_t>;
  template class MaxFilter<float>;
#endif
  template class MaxFilter<double>;
}
