/**
 * \file GainExpanderFilter.cpp
 */

#include "GainExpanderFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainExpanderFilter<DataType_>::GainExpanderFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision), softness(static_cast<DataType_>(.0001))
  {
  }

  template<typename DataType_>
  GainExpanderFilter<DataType_>::~GainExpanderFilter()
  {
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness <= 0)
    {
      throw std::out_of_range("Softness factor must be strictly positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainExpanderFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  DataType_ GainExpanderFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
      return 0;
    DataType diff = -10 * std::log10(value);
    return static_cast<DataType>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1)));
  }

  template class GainExpanderFilter<float>;
  template class GainExpanderFilter<double>;
  template class GainFilter<GainExpanderFilter<float>>;
  template class GainFilter<GainExpanderFilter<double>>;
}
