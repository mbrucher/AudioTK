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
    gainLUT.clear();
    gainLUT.push_back(0); // gain of 0 at input = 0

    for(int i = 1; i < LUTsize; ++i)
    {
      DataType diff = -10 * std::log10(static_cast<DataType>(i) / LUTprecision);
      gainLUT.push_back(static_cast<DataType>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1))));
    }
  }

  template class GainExpanderFilter<float>;
  template class GainExpanderFilter<double>;
}
