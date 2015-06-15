/**
 * \file RelativePowerFilter.cpp
 */

#include "RelativePowerFilter.h"

#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  RelativePowerFilter<DataType_>::RelativePowerFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), memory_factor(0), temp_output(0)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  RelativePowerFilter<DataType_>::~RelativePowerFilter()
  {
    
  }

  template<typename DataType_>
  void RelativePowerFilter<DataType_>::set_memory(DataType_ memory_factor)
  {
    if(memory_factor < 0 || memory_factor >= 1)
    {
      throw std::out_of_range("Memory factor must be a positive value less than 1 (so that it doesn't diverge)");
    }
    this->memory_factor = memory_factor;
  }
  
  template<typename DataType_>
  DataType_ RelativePowerFilter<DataType_>::get_memory() const
  {
    return memory_factor;
  }
  
  template<typename DataType_>
  void RelativePowerFilter<DataType_>::process_impl(std::int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::int64_t i = 0; i < size; ++i)
      {
        temp_output = (1 - memory_factor) * input[i] * input[i] + memory_factor * temp_output;
        if(temp_output > std::numeric_limits<DataType_>::epsilon())
        {
          output[i] = (input[i] * input[i]) / (temp_output + std::numeric_limits<DataType_>::epsilon());
        }
        else
        {
          output[i] = output[i-1];
        }
      }
    }
  }
  
  template class RelativePowerFilter<float>;
  template class RelativePowerFilter<double>;
}
