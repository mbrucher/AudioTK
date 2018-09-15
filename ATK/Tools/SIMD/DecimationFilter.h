/**
 * \file DecimationFilter.h
 */

#ifndef ATK_TOOLS_SIMD_DECIMATIONFILTER_H
#define ATK_TOOLS_SIMD_DECIMATIONFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to decimate channels
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createDecimationFilter(gsl::index nb_channels = 1);
}

#endif
