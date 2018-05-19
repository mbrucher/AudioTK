/**
 * \file RIAAFilter.h
 */

#ifndef ATK_EQ_SIMD_RIAAFILTER_H
#define ATK_EQ_SIMD_RIAAFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized RIAA filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createRIAAFilter(gsl::index nb_channels = 1);
  /// Create a vectorized inverse RIAA filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createInverseRIAAFilter(gsl::index nb_channels = 1);
  /// Create a vectorized RIAA filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createRIAATDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized inverse RIAA filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createInverseRIAATDF2Filter(gsl::index nb_channels = 1);
}

#endif
