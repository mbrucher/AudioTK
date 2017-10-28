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
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Bessel filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Bessel filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Bessel filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized low pass Bessel TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Bessel TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Bessel TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Bessel TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter(std::size_t nb_channels = 1);
}

#endif
