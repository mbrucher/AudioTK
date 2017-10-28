/**
 * \file ApplyGainFilter.h
 */

#ifndef ATK_TOOLS_SIMD_APPLYGAINFILTER_H
#define ATK_TOOLS_SIMD_APPLYGAINFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to multiply channels together
  template<typename DataType, std::size_t VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createApplyGainFilter(std::size_t nb_channels = 1);
}

#endif
