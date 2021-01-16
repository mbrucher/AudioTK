/**
 * \file GainMaxCompressorFilter.cpp
 */

#include "GainMaxCompressorFilter.h"
#include <ATK/Core/Utilities.h>
#include <ATK/Utility/fmath.h>

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  GainMaxCompressorFilter<DataType_>::GainMaxCompressorFilter(gsl::index nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision)
  {
  }

  template<typename DataType_>
  void GainMaxCompressorFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness < 0)
    {
      throw ATK::RuntimeError("Softness factor must be positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainMaxCompressorFilter<DataType_>::get_softness() const
  {
    return softness;
  }
  
  template<typename DataType_>
  void GainMaxCompressorFilter<DataType_>::set_max_reduction(DataType_ max_reduction)
  {
    if (max_reduction <= 0)
    {
      throw ATK::RuntimeError("Maximum reduction factor must be strictly positive value");
    }
    this->max_reduction = max_reduction;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  void GainMaxCompressorFilter<DataType_>::set_max_reduction_db(DataType_ max_reduction_db)
  {
    this->max_reduction = static_cast<DataType_>(std::pow(10, max_reduction_db / 10));
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainMaxCompressorFilter<DataType_>::get_max_reduction() const
  {
    return max_reduction;
  }

  template<typename DataType_>
  DataType_ GainMaxCompressorFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
    {
      return 1;
    }
    DataType diff = static_cast<DataType_>(-5 * fmath::log10(1/(value * value) + fmath::pow(max_reduction, 2 * ratio / (ratio - 1))));
    return static_cast<DataType>(fmath::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1) / ratio));
  }

#if ATK_ENABLE_INSTANTIATION
  template class GainMaxCompressorFilter<float>;
  template class GainFilter<GainMaxCompressorFilter<float>>;
#endif
  template class GainMaxCompressorFilter<double>;
  template class GainFilter<GainMaxCompressorFilter<double>>;
}
