/**
 * \file GainExpanderFilter.cpp
 */

#include "GainExpanderFilter.h"
#include <ATK/Core/Utilities.h>
#include <ATK/Utility/fmath.h>

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  GainExpanderFilter<DataType_>::GainExpanderFilter(gsl::index nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness < 0)
    {
      throw ATK::RuntimeError("Softness factor must be positive value");
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
    {
      return 0;
    }
    DataType diff = -10 * fmath::log10(value);
    return static_cast<DataType>(fmath::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1)));
  }

#if ATK_ENABLE_INSTANTIATION
  template class GainExpanderFilter<float>;
  template class GainFilter<GainExpanderFilter<float>>;
#endif
  template class GainExpanderFilter<double>;
  template class GainFilter<GainExpanderFilter<double>>;
}
