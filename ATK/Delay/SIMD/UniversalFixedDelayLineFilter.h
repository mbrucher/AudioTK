/**
 * \file UniversalFixedDelayLineFilter
 */

#ifndef ATK_DELAY_SIMD_UNIVERSALFIXEDDELAYLINEFILTER_H
#define ATK_DELAY_SIMD_UNIVERSALFIXEDDELAYLINEFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Delay/config.h>

namespace ATK
{
  /// Create a SIMD filter to multiply channels together
  template<typename DataType, std::size_t VL>
  ATK_DELAY_EXPORT std::unique_ptr<BaseFilter> createUniversalFixedDelayLineFilter(std::size_t max_delay);
}

#endif
