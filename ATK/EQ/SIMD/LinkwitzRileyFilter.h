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
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyFilter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Linkwitz-Riley filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Linkwitz-Riley filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassLinkwitzRileyFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Linkwitz-Riley filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopLinkwitzRileyFilter(std::size_t nb_channels = 1);
  /// Create a vectorized low pass Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassLinkwitzRileyTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Linkwitz-Riley TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopLinkwitzRileyTDF2Filter(std::size_t nb_channels = 1);
}

#endif
