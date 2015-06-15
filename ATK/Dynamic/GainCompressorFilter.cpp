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
    gainLUT.clear();
    gainLUT.push_back(1); // gain of 1 at input = 0

    for(int i = 1; i < LUTsize; ++i)
    {
      DataType diff = 10 * std::log10(static_cast<DataType>(i) / LUTprecision);
      gainLUT.push_back(static_cast<DataType_>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1) / ratio)));
    }
  }

  template class GainCompressorFilter<float>;
  template class GainCompressorFilter<double>;
}
