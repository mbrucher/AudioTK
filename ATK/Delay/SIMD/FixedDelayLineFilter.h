/**
 * \file FixedDelayLineFilter
 */

#ifndef ATK_DELAY_SIMD_FIXEDDELAYLINEFILTER_H
#define ATK_DELAY_SIMD_FIXEDDELAYLINEFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Delay/config.h>

namespace ATK
{
  /// Create a SIMD filter to multiply channels together
  template<typename DataType, std::size_t VL>
  ATK_DELAY_EXPORT std::unique_ptr<BaseFilter> createFixedDelayLineFilter(std::size_t max_delay);
}

#endif
