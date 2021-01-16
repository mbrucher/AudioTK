/**
 * \file PowerFilter.cpp
 */

#include "PowerFilter.h"
#include <ATK/Core/Utilities.h>

#include <cassert>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  PowerFilter<DataType_>::PowerFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
    output_delay = 1;
  }

  template<typename DataType_>
  void PowerFilter<DataType_>::set_memory(DataType_ memory_factor)
  {
    if(memory_factor < 0 || memory_factor >= 1)
    {
      throw ATK::RuntimeError("Memory factor must be a positive value less than 1 (so that it doesn't diverge)");
    }
    this->memory_factor = memory_factor;
  }
  
  template<typename DataType_>
  DataType_ PowerFilter<DataType_>::get_memory() const
  {
    return memory_factor;
  }
  
  template<typename DataType_>
  void PowerFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = (1 - memory_factor) * input[i] * input[i] + memory_factor * output[i-1];
      }
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class PowerFilter<float>;
#endif
  template class PowerFilter<double>;
}
