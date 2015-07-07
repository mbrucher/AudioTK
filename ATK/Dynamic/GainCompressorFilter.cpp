/**
 * \file GainCompressorFilter.cpp
 */

#include "GainCompressorFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainCompressorFilter<DataType_>::GainCompressorFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
    recomputeLUT();
  }
  
  template<typename DataType_>
  GainCompressorFilter<DataType_>::~GainCompressorFilter()
  {
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::recomputeLUT()
  {
    auto gainLUT_ptr = gainLUT.data();
    *(gainLUT_ptr++) = 1; // gain of 1 at input = 0

    for(int i = 1; i < LUTsize; ++i)
    {
      *(gainLUT_ptr++) = computeGain(static_cast<DataType>(i) / LUTprecision);
    }
  }

  template<typename DataType_>
  DataType_ ATK::GainCompressorFilter<DataType_>::computeGain( DataType_ value )  
  {
    DataType diff = 10 * std::log10(value);
    return static_cast<DataType>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1) / ratio));
  }

  template class GainCompressorFilter<float>;
  template class GainCompressorFilter<double>;
}
