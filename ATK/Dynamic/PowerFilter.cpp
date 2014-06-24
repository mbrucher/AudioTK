/**
 * \file PowerFilter.cpp
 */

#include "PowerFilter.h"

#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  PowerFilter<DataType_>::PowerFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), memory_factor(0)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  PowerFilter<DataType_>::~PowerFilter()
  {
    
  }

  template<typename DataType_>
  void PowerFilter<DataType_>::set_memory(DataType_ memory_factor)
  {
    if(memory_factor < 0 || memory_factor >= 1)
    {
      throw std::out_of_range("Memory factor must be a positive value less than 1 (so that it doesn't diverge)");
    }
    this->memory_factor = memory_factor;
  }
  
  template<typename DataType_>
  DataType_ PowerFilter<DataType_>::get_memory() const
  {
    return memory_factor;
  }
  
  template<typename DataType_>
  void PowerFilter<DataType_>::process_impl(std::int64_t size)
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      for(std::int64_t i = 0; i < size; ++i)
      {
        outputs[channel][i] = (1 - memory_factor) * converted_inputs[channel][i] * converted_inputs[channel][i] + memory_factor * outputs[channel][i-1];
      }
    }
  }
  
  template class PowerFilter<float>;
  template class PowerFilter<double>;
}
