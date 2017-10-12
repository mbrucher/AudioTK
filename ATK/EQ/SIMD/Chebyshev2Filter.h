/**
 * \file Chebyshev2Filter.h
 */

#ifndef ATK_EQ_SIMD_CHEBYSHEV2FILTER_H
#define ATK_EQ_SIMD_CHEBYSHEV2FILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized low pass Chebyshev2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Chebyshev2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Chebyshev2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Chebyshev2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized low pass Chebyshev2 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2TDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Chebyshev2 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2TDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Chebyshev2 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2TDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Chebyshev2 TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2TDF2Filter(std::size_t nb_channels = 1);
}

#endif
