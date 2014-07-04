/**
 * \file GainExpanderFilter.cpp
 */

#include "GainExpanderFilter.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace
{
  static const int LUTsize = 128*1024;
  static const int LUTprecision = 1000;
}

namespace ATK
{
  template<typename DataType_>
  GainExpanderFilter<DataType_>::GainExpanderFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), threshold(1), slope(1), softness(.0001)
  {
    gainLUT.reserve(LUTsize);
    recomputeLUT();
  }
  
  template<typename DataType_>
  GainExpanderFilter<DataType_>::~GainExpanderFilter()
  {
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::process_impl(std::int64_t size)
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::int64_t i = 0; i < size; ++i)
      {
        DataType_ value = input[i] * threshold;
        int step = static_cast<int>(value * LUTprecision);
        if(step >= gainLUT.size())
        {
          step = gainLUT.size() - 1;
        }
        DataType delta = value - step / LUTprecision;
        output[i] = gainLUT[step];
      }
    }
  }
  
  template<typename DataType_>
  void GainExpanderFilter<DataType_>::set_threshold(DataType_ threshold)
  {
    if(threshold <= 0)
    {
      throw std::out_of_range("Threshold factor must be strictly positive value");
    }
    this->threshold = 1 / threshold;
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::set_threshold_db(DataType_ threshold_db)
  {
    this->threshold = std::pow(10, - threshold_db / 10);
  }

  template<typename DataType_>
  DataType_ GainExpanderFilter<DataType_>::get_threshold() const
  {
    return 1 / threshold;
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::set_slope(DataType_ slope)
  {
    if(slope < 1)
    {
      throw std::out_of_range("Slope factor must be higher than or equal to 1");
    }
    this->slope = slope;
    recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainExpanderFilter<DataType_>::get_slope() const
  {
    return slope;
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::set_softness(DataType_ softness)
  {
    if(softness <= 0)
    {
      throw std::out_of_range("Softness factor must be strictly positive value");
    }
    this->softness = softness;
    recomputeLUT();
  }

  template<typename DataType_>
  DataType_ GainExpanderFilter<DataType_>::get_softness() const
  {
    return softness;
  }

  template<typename DataType_>
  void GainExpanderFilter<DataType_>::recomputeLUT()
  {
    gainLUT.clear();
    gainLUT.push_back(0); // gain of 1 at input = 0

    for(int i = 1; i < LUTsize; ++i)
    {
      DataType diff = -10 * std::log10(static_cast<DataType>(i) / LUTprecision);
      gainLUT.push_back(std::pow(10, -(std::sqrt(diff*diff + softness) + diff) / 20 * (slope - 1) / slope));
    }
  }

  template class GainExpanderFilter<float>;
  template class GainExpanderFilter<double>;
}
