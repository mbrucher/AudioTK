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
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassButterworthFilter(std::size_t nb_channels);
  /// Create a vectorized high pass Butterworth filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassButterworthFilter(std::size_t nb_channels);
  /// Create a vectorized band pass Butterworth filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassButterworthFilter(std::size_t nb_channels);
  /// Create a vectorized band stop Butterworth filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandStopButterworthFilter(std::size_t nb_channels);
}

#endif
