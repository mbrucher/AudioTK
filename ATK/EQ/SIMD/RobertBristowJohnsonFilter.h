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
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass peak Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized all pass Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized low shelf Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized high shelf Robert Bristow Johnson filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonFilter(gsl::index nb_channels = 1);
  /// Create a vectorized low pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band stop Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized band pass peak Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized all pass Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized low shelf Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
  /// Create a vectorized high shelf Robert Bristow Johnson TDF2 filter
  template<typename DataType, gsl::index VL>
  ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonTDF2Filter(gsl::index nb_channels = 1);
}

#endif
