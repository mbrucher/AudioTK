/**
 * \file BesselFilter.h
 */

#ifndef ATK_EQ_SIMD_BESSELFILTER_H
#define ATK_EQ_SIMD_BESSELFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized low pass Bessel filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Bessel filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Bessel filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Bessel filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter(gsl::index nb_channels = 1);
  /// Create a vectorized low pass Bessel TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Bessel TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Bessel TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Bessel TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter(gsl::index nb_channels = 1);
}

#endif
