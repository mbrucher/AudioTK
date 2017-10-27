/**
 * \file RobertBristowJohnsonFilter.h
 */

#ifndef ATK_EQ_SIMD_ROBERTBRISTOWJOHNSONFILTER_H
#define ATK_EQ_SIMD_ROBERTBRISTOWJOHNSONFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /// Create a vectorized low pass Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass peak Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized all pass Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized low shelf Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized high shelf Robert Bristow Johnson filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonFilter(std::size_t nb_channels = 1);
  /// Create a vectorized low pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band stop Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized band pass peak Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized all pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized low shelf Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
  /// Create a vectorized high shelf Robert Bristow Johnson TDF2 filter
  template<typename DataType, std::size_t VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonTDF2Filter(std::size_t nb_channels = 1);
}

#endif
