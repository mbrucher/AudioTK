/**
 * \file GainLimiterFilter.cpp
 */

#include "GainLimiterFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  GainLimiterFilter<DataType_>::GainLimiterFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
    recomputeLUT();
  }

  template<typename DataType_>
  GainLimiterFilter<DataType_>::~GainLimiterFilter()
  {
  }

  template<typename DataType_>
  void GainLimiterFilter<DataType_>::recomputeLUT()
  {
    gainLUT.clear();
    gainLUT.push_back(1); // gain of 1 at input = 0

    for(int i = 1; i < LUTsize; ++i)
    {
      DataType diff = 10 * std::log10(static_cast<DataType>(i) / LUTprecision);
      gainLUT.push_back(static_cast<DataType>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40)));
    }
  }

  template class GainLimiterFilter<float>;
  template class GainLimiterFilter<double>;
}
