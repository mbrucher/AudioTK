/**
 * \file GainColoredExpanderFilter.cpp
 */

#include "GainColoredExpanderFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainColoredExpanderFilter<DataType_>::GainColoredExpanderFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision), softness(static_cast<DataType_>(.0001)), color(0), quality(0)
  {
    recomputeLUT();
  }

  template<typename DataType_>
  GainColoredExpanderFilter<DataType_>::~GainColoredExpanderFilter()
  {
    //Future has to be deleted in child destructor as it uses computeGain
    if(recomputeFuture.valid())
    {
      recomputeFuture.wait();
    }
  }

  template<typename DataType_>
  void GainColoredExpanderFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness <= 0)
    {
      throw std::out_of_range("Softness factor must be strictly positive value");
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
      throw std::out_of_range("Quality factor must be a strictly positive value");
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
      return 0;
    DataType diff = -10 * std::log10(value);
    DataType additional_color = color * std::exp(- diff * diff * quality);
    return static_cast<DataType>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1))) + additional_color;
  }

  template class GainColoredExpanderFilter<float>;
  template class GainColoredExpanderFilter<double>;
}
