/**
 * \file ButterworthFilter.h
 */

#ifndef ATK_EQ_SIMD_BUTTERWORTHFILTER_H
#define ATK_EQ_SIMD_BUTTERWORTHFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized low pass Butterworth filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassButterworthFilter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Butterworth filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassButterworthFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Butterworth filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassButterworthFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Butterworth filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopButterworthFilter(gsl::index nb_channels = 1);
  /// Create a vectorized low pass Butterworth TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassButterworthTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Butterworth TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassButterworthTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Butterworth TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassButterworthTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Butterworth TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopButterworthTDF2Filter(gsl::index nb_channels = 1);
}

#endif
