/**
 * \file LinkwitzRileyFilter.h
 */

#ifndef ATK_EQ_SIMD_LINKWITZRILEYFILTER_H
#define ATK_EQ_SIMD_LINKWITZRILEYFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized low pass Linkwitz-Riley filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Linkwitz-Riley filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Linkwitz-Riley filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Linkwitz-Riley filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter(std::size_t nb_channels = 1);
  /// Create a vectorized low pass Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter(std::size_t nb_channels = 1);
}

#endif
