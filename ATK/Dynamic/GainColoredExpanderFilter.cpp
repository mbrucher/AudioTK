/**
 * \file GainColoredExpanderFilter.cpp
 */

#include "GainColoredExpanderFilter.h"
#include <ATK/Core/Utilities.h>
#include <ATK/Utility/fmath.h>

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainColoredExpanderFilter<DataType_>::GainColoredExpanderFilter(gsl::index nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
  }

  template<typename DataType_>
  void GainColoredExpanderFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness < 0)
    {
      throw ATK::RuntimeError("Softness factor must be positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainColoredExpanderFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  void GainColoredExpanderFilter<DataType_>::set_color(DataType_ color)
  {
    this->color = color;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainColoredExpanderFilter<DataType_>::get_color() const
  {
    return color;
  }
  
  template<typename DataType_>
  void GainColoredExpanderFilter<DataType_>::set_quality(DataType_ quality)
  {
    if (quality <= 0)
    {
      throw ATK::RuntimeError("Quality factor must be a strictly positive value");
    }
    this->quality = quality;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainColoredExpanderFilter<DataType_>::get_quality() const
  {
    return quality;
  }

  template<typename DataType_>
  DataType_ GainColoredExpanderFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
    {
      return 0;
    }
    DataType diff = -10 * fmath::log10(value);
    DataType additional_color = color * fmath::exp(- diff * diff * quality);
    return static_cast<DataType>(fmath::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1))) + additional_color;
  }

#if ATK_ENABLE_INSTANTIATION
  template class GainColoredExpanderFilter<float>;
  template class GainFilter<GainColoredExpanderFilter<float>>;
#endif
  template class GainColoredExpanderFilter<double>;
  template class GainFilter<GainColoredExpanderFilter<double>>;
}
