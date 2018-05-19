/**
 * \file DryWetFilter.h
 */

#ifndef ATK_TOOLS_SIMD_DRYWETFILTER_H
#define ATK_TOOLS_SIMD_DRYWETFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to mix channels together
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createDryWetFilter(gsl::index nb_channels = 1);
}

#endif
