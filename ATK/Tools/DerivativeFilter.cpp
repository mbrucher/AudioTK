/**
 * \file DerivativeFilter.cpp
 */

#include "DerivativeFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  DerivativeFilter<DataType_>::DerivativeFilter(int nb_channels)
  :Parent(nb_channels, nb_channels)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  DerivativeFilter<DataType_>::~DerivativeFilter()
  {
    
  }

  template<typename DataType_>
  void DerivativeFilter<DataType_>::process_impl(std::int64_t size)
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::int64_t i = 0; i < size; ++i)
      {
        output[i] = input[i] - input[i-1];
      }
    }
  }
  
  template class DerivativeFilter<std::int16_t>;
  template class DerivativeFilter<std::int32_t>;
  template class DerivativeFilter<std::int64_t>;
  template class DerivativeFilter<float>;
  template class DerivativeFilter<double>;
}
