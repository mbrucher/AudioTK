/**
 * \file GainMaxExpanderFilter.cpp
 */

#include "GainMaxExpanderFilter.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include <ATK/Utility/fmath.h>

namespace ATK
{
  template<typename DataType_>
  GainMaxExpanderFilter<DataType_>::GainMaxExpanderFilter(int nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, LUTsize, LUTprecision), softness(static_cast<DataType_>(.0001)), max_reduction(static_cast<DataType_>(0.01))
  {
  }

  template<typename DataType_>
  GainMaxExpanderFilter<DataType_>::~GainMaxExpanderFilter()
  {
  }

  template<typename DataType_>
  void GainMaxExpanderFilter<DataType_>::set_softness(DataType_ softness)
  {
    if (softness <= 0)
    {
      throw std::out_of_range("Softness factor must be strictly positive value");
    }
    this->softness = softness;
    start_recomputeLUT();
  }
  
  template<typename DataType_>
  DataType_ GainMaxExpanderFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  void GainMaxExpanderFilter<DataType_>::set_max_reduction(DataType_ max_reduction)
  {
    if (max_reduction <= 0)
    {
      throw std::out_of_range("Maximum reduction factor must be strictly positive value");
    }
    this->max_reduction = max_reduction;
  }

  template<typename DataType_>
  void GainMaxExpanderFilter<DataType_>::set_max_reduction_db(DataType_ max_reduction_db)
  {
    this->max_reduction = static_cast<DataType_>(std::pow(10, max_reduction_db / 10));
  }

  template<typename DataType_>
  DataType_ GainMaxExpanderFilter<DataType_>::get_max_reduction() const
  {
    return max_reduction;
  }

  template<typename DataType_>
  DataType_ GainMaxExpanderFilter<DataType_>::computeGain( DataType_ value ) const
  {
    if(value == 0)
      return static_cast<DataType_>(std::pow(max_reduction, 1 / (ratio - 1)));

    DataType diff = static_cast<DataType_>(-10 * fmath::log10(std::sqrt(value * value + std::pow(max_reduction, 2 / (ratio - 1)))));

    return static_cast<DataType>(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 40 * (ratio - 1)));
  }

  template class GainMaxExpanderFilter<float>;
  template class GainMaxExpanderFilter<double>;
  template class GainFilter<GainMaxExpanderFilter<float>>;
  template class GainFilter<GainMaxExpanderFilter<double>>;
}
