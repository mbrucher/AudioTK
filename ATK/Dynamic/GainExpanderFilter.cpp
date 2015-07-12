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
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
    recomputeLUT();
  }

  template<typename DataType_>
  GainExpanderFilter<DataType_>::~GainExpanderFilter()
  {
    //Future has to be deleted in child destructor as it uses computeGain
    if(recomputeFuture.valid())
    {
      recomputeFuture.wait();
    }
  }

  template<typename DataType_>
  DataType_ ATK::GainExpanderFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
      return 0;
    DataType diff = -10 * std::log10(value);
    return static_cast<DataType>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1)));
  }

  template class GainExpanderFilter<float>;
  template class GainExpanderFilter<double>;
}
