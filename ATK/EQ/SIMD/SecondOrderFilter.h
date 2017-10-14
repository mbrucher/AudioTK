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
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass second order filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass second order filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass peak second order filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter(std::size_t nb_channels = 1);
  /// Create a vectorized all pass second order filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter(std::size_t nb_channels = 1);
  /// Create a vectorized low shelf second order filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter(std::size_t nb_channels = 1);
  /// Create a vectorized high shelf second order filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter(std::size_t nb_channels = 1);
  /// Create a vectorized low pass second order TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass second order TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass second order TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass peak second order TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized all pass second order TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized low shelf second order TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high shelf second order TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter(std::size_t nb_channels = 1);
}

#endif
