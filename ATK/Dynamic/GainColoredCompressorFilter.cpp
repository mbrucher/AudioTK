/**
 * \file GainColoredCompressorFilter.cpp
 */

#include "GainColoredCompressorFilter.h"
#include <ATK/Core/Utilities.h>
#include <ATK/Utility/fmath.h>

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  GainColoredCompressorFilter<DataType_>::GainColoredCompressorFilter(gsl::index nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
  }
  
  template<typename DataType_>
  void GainColoredCompressorFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness < 0)
    {
      throw ATK::RuntimeError("Softness factor must be positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainColoredCompressorFilter<DataType_>::get_softness() const
  {
    return softness;
  }
  
  template<typename DataType_>
  void GainColoredCompressorFilter<DataType_>::set_color(DataType_ color)
  {
    this->color = color;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainColoredCompressorFilter<DataType_>::get_color() const
  {
    return color;
  }
  
  template<typename DataType_>
  void GainColoredCompressorFilter<DataType_>::set_quality(DataType_ quality)
  {
    if (quality <= 0)
    {
      throw ATK::RuntimeError("Quality factor must be a strictly positive value");
    }
    this->quality = quality;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainColoredCompressorFilter<DataType_>::get_quality() const
  {
    return quality;
  }
  
  template<typename DataType_>
  DataType_ GainColoredCompressorFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
    {
      return 1;
    }
    DataType diff = 10 * fmath::log10(value);
    
    DataType additional_color = color * fmath::exp(- diff * diff * quality);
    return static_cast<DataType>(fmath::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1) / ratio)) + additional_color;
  }

#if ATK_ENABLE_INSTANTIATION
  template class GainColoredCompressorFilter<float>;
  template class GainFilter<GainColoredCompressorFilter<float>>;
#endif
  template class GainColoredCompressorFilter<double>;
  template class GainFilter<GainColoredCompressorFilter<double>>;
}
