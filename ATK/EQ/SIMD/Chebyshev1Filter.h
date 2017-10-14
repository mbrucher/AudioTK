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
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Chebyshev1 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Chebyshev1 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Chebyshev1 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter(std::size_t nb_channels = 1);
  /// Create a vectorized low pass Chebyshev1 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Chebyshev1 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Chebyshev1 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Chebyshev1 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter(std::size_t nb_channels = 1);
}

#endif
