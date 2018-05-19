/**
 * \file Chebyshev1Filter.h
 */

#ifndef ATK_EQ_SIMD_CHEBYSHEV1FILTER_H
#define ATK_EQ_SIMD_CHEBYSHEV1FILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized low pass Chebyshev1 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Chebyshev1 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Chebyshev1 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Chebyshev1 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter(gsl::index nb_channels = 1);
  /// Create a vectorized low pass Chebyshev1 TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Chebyshev1 TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Chebyshev1 TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Chebyshev1 TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter(gsl::index nb_channels = 1);
}

#endif
