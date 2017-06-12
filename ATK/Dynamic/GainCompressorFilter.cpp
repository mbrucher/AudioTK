/**
 * \file GainCompressorFilter.cpp
 */

#include "GainCompressorFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

#include <ATK/Utility/fmath.h>

namespace ATK
{
  template<typename DataType_>
  GainCompressorFilter<DataType_>::GainCompressorFilter(std::size_t nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision), softness(static_cast<DataType_>(.0001))
  {
  }
  
  template<typename DataType_>
  GainCompressorFilter<DataType_>::~GainCompressorFilter()
  {
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness <= 0)
    {
      throw std::out_of_range("Softness factor must be strictly positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainCompressorFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  DataType_ GainCompressorFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
      return 1;
    DataType diff = 10 * fmath::log10(value);
    return static_cast<DataType>(fmath::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1) / ratio));
  }

  template class GainCompressorFilter<float>;
  template class GainCompressorFilter<double>;
  template class GainFilter<GainCompressorFilter<float>>;
  template class GainFilter<GainCompressorFilter<double>>;
}
