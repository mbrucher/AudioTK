/**
 * \file GainFractionalCompressorFilter.cpp
 */

#include "GainFractionalCompressorFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainFractionalCompressorFilter<DataType_>::GainFractionalCompressorFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
    recomputeLUT();
  }
  
  template<typename DataType_>
  GainFractionalCompressorFilter<DataType_>::~GainFractionalCompressorFilter()
  {
    //Future has to be deleted in child destructor as it uses computeGain
    if(recomputeFuture.valid())
    {
      recomputeFuture.wait();
    }
  }

  template<typename DataType_>
  void GainFractionalCompressorFilter<DataType_>::set_color(DataType_ color)
  {
    this->color = color;
    start_recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainFractionalCompressorFilter<DataType_>::get_color() const
  {
    return color;
  }

  template<typename DataType_>
  DataType_ GainFractionalCompressorFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
      return 1;
    DataType diff = std::pow(value, (1. - ratio) / (ratio * 2));
    return (diff + diff * diff * diff) / (1 + color * diff + diff * diff * diff);
  }

  template class GainFractionalCompressorFilter<float>;
  template class GainFractionalCompressorFilter<double>;
}
