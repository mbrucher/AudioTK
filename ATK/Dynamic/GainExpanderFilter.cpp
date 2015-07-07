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
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::recomputeLUT()
  {
    auto gainLUT_ptr = gainLUT.data();
    *(gainLUT_ptr++) = 0; // gain of 0 at input = 0

    for(int i = 1; i < LUTsize; ++i)
    {
      *(gainLUT_ptr++) = computeGain(static_cast<DataType>(i) / LUTprecision);
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
