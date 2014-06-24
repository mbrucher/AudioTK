/**
 * \file GainCompressorFilter.cpp
 */

#include "GainCompressorFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  GainCompressorFilter<DataType_>::GainCompressorFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), threshold(0), slope(1), softness(.000000001)
  {
  }
  
  template<typename DataType_>
  GainCompressorFilter<DataType_>::~GainCompressorFilter()
  {
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::process_impl(std::int64_t size)
  {
    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      for(std::int64_t i = 0; i < size; ++i)
      {
        DataType tmplog = 10 * std::log10(converted_inputs[channel][i]+1e-100);
        DataType diff = tmplog - threshold;

        outputs[channel][i] = converted_inputs[channel][i] * std::pow(10, -((std::sqrt(diff*diff + softness) + diff) / 2) / 10 * (slope - 1) / slope);
      }
    }
  }
  
  template<typename DataType_>
  void GainCompressorFilter<DataType_>::set_threshold(DataType_ threshold)
  {
    if(threshold <= 0)
    {
      throw std::out_of_range("Threshold factor must be strictly positive value");
    }
    this->threshold = 10 * std::log10(threshold);
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::set_threshold_db(DataType_ threshold)
  {
    this->threshold = threshold;
  }

  template<typename DataType_>
  DataType_ GainCompressorFilter<DataType_>::get_threshold() const
  {
    return std::pow(10, threshold / 10);
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::set_slope(DataType_ slope)
  {
    if(slope < 1)
    {
      throw std::out_of_range("Slope factor must be higher than or equal to 1");
    }
    this->slope = slope;
  }

  template<typename DataType_>
  DataType_ GainCompressorFilter<DataType_>::get_slope() const
  {
    return slope;
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::set_softness(DataType_ softness)
  {
    if(softness <= 0)
    {
      throw std::out_of_range("Softness factor must be strictly positive value");
    }
    this->softness = softness;
  }

  template<typename DataType_>
  DataType_ GainCompressorFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template class GainCompressorFilter<float>;
  template class GainCompressorFilter<double>;
}
