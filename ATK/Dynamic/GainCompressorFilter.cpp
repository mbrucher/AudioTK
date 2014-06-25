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
  GainCompressorFilter<DataType_>::GainCompressorFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), threshold(0), slope(1), softness(.000000001)
  {
    gainLUT.reserve(64*1024);
  }
  
  template<typename DataType_>
  GainCompressorFilter<DataType_>::~GainCompressorFilter()
  {
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::process_impl(std::int64_t size)
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      for(std::int64_t i = 0; i < size; ++i)
      {
        int step = static_cast<int>(converted_inputs[channel][i] * threshold / 1000);
        if(step >= gainLUT.size())
        {
          step = gainLUT.size() - 1;
        }
        DataType delta = converted_inputs[channel][i] * threshold - step * 1000;
        outputs[channel][i] = converted_inputs[channel][i] * gainLUT[step];
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
    this->threshold = 1 / threshold;
    recomputeLUT();
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::set_threshold_db(DataType_ threshold_db)
  {
    this->threshold = std::pow(10, - threshold_db / 10);
    recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainCompressorFilter<DataType_>::get_threshold() const
  {
    return 1 / threshold;
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::set_slope(DataType_ slope)
  {
    if(slope < 1)
    {
      throw std::out_of_range("Slope factor must be higher than or equal to 1");
    }
    this->slope = slope;
    recomputeLUT();
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
    recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainCompressorFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  void GainCompressorFilter<DataType_>::recomputeLUT()
  {
    gainLUT.clear();
    gainLUT.push_back(1); // gain of 1 at input = 0

    for(int i = 1; i < 64*1024; ++i)
    {
      DataType diff = 10 * std::log10(static_cast<DataType>(i) / 1000);
      gainLUT.push_back(std::pow(10, -((std::sqrt(diff*diff + softness) + diff) / 2) / 10 * (slope - 1) / slope));
    }
  }

  template class GainCompressorFilter<float>;
  template class GainCompressorFilter<double>;
}
