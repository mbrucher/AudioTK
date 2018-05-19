/**
 * \file SecondOrderFilter.h
 */

#ifndef ATK_EQ_SIMD_SECONDORDERFILTER_H
#define ATK_EQ_SIMD_SECONDORDERFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized low pass second order filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass second order filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass second order filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass peak second order filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter(gsl::index nb_channels = 1);
  /// Create a vectorized all pass second order filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter(gsl::index nb_channels = 1);
  /// Create a vectorized low shelf second order filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter(gsl::index nb_channels = 1);
  /// Create a vectorized high shelf second order filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter(gsl::index nb_channels = 1);
  /// Create a vectorized low pass second order TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass second order TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass second order TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass peak second order TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized all pass second order TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized low shelf second order TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high shelf second order TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter(gsl::index nb_channels = 1);
}

#endif
