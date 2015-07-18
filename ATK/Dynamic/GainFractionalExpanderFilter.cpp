/**
 * \file GainFractionalExpanderFilter.cpp
 */

#include "GainFractionalExpanderFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainFractionalExpanderFilter<DataType_>::GainFractionalExpanderFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision), color(0)
  {
    recomputeLUT();
  }

  template<typename DataType_>
  GainFractionalExpanderFilter<DataType_>::~GainFractionalExpanderFilter()
  {
    //Future has to be deleted in child destructor as it uses computeGain
    if(recomputeFuture.valid())
    {
      recomputeFuture.wait();
    }
  }

  template<typename DataType_>
  void GainFractionalExpanderFilter<DataType_>::set_color(DataType_ color)
  {
    this->color = color;
    start_recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainFractionalExpanderFilter<DataType_>::get_color() const
  {
    return color;
  }

  template<typename DataType_>
  DataType_ GainFractionalExpanderFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
      return 0;
    DataType diff = std::pow(value, (ratio - 1)/2);
    return (diff + diff * diff) / (1 + color * diff + diff * diff);
  }

  template class GainFractionalExpanderFilter<float>;
  template class GainFractionalExpanderFilter<double>;
}
