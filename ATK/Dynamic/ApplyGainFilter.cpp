/**
 * \file ApplyGainFilter.cpp
 */

#include "ApplyGainFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  ApplyGainFilter<DataType_>::ApplyGainFilter(int nb_channels)
  :Parent(2 * nb_channels, nb_channels)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  ApplyGainFilter<DataType_>::~ApplyGainFilter()
  {
    
  }

  template<typename DataType_>
  void ApplyGainFilter<DataType_>::process_impl(std::int64_t size)
  {
    assert(nb_input_ports == 2*nb_output_ports);

    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input1 = converted_inputs[2 * channel];
      const DataType* ATK_RESTRICT input2 = converted_inputs[2 * channel + 1];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::int64_t i = 0; i < size; ++i)
      {
        output[i] = input1[i] * input2[i];
      }
    }
  }
  
  template class ApplyGainFilter<float>;
  template class ApplyGainFilter<double>;
}
