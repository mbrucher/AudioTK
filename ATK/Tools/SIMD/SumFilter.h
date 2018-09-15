/**
 * \file SumFilter.h
 */

#ifndef ATK_TOOLS_SIMD_SUMFILTER_H
#define ATK_TOOLS_SIMD_SUMFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to sum several channels together
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createSumFilter(gsl::index nb_channels = 1, gsl::index summed_channels = 2);
}

#endif
