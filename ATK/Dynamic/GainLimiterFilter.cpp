/**
 * \file GainLimiterFilter.cpp
 */

#include "GainLimiterFilter.h"
#include <ATK/Core/Utilities.h>
#include <ATK/Utility/fmath.h>

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  GainLimiterFilter<DataType_>::GainLimiterFilter(gsl::index nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
  }

  template<typename DataType_>
  void GainLimiterFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness <= 0)
    {
      throw ATK::RuntimeError("Softness factor must be strictly positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainLimiterFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  DataType_ GainLimiterFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
    {
      return 1;
    }
    DataType diff = 10 * fmath::log10(value);
    return static_cast<DataType>(fmath::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40));
  }

#if ATK_ENABLE_INSTANTIATION
  template class GainLimiterFilter<float>;
  template class GainFilter<GainLimiterFilter<float>>;
#endif
  template class GainLimiterFilter<double>;
  template class GainFilter<GainLimiterFilter<double>>;
}
