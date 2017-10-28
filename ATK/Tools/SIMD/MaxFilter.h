/**
 * \file MaxFilter.h
 */

#ifndef ATK_TOOLS_SIMD_MAXFILTER_H
#define ATK_TOOLS_SIMD_MAXFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to mix channels together
  template<typename DataType, std::size_t VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createMaxFilter(std::size_t nb_channels = 1);
}

#endif
