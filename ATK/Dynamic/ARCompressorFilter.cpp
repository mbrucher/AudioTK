/**
 * \file ARCompressorFilter.cpp
 */

#include "ARCompressorFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  ARCompressorFilter<DataType_>::ARCompressorFilter(int nb_channels)
  :Parent(2 * nb_channels, nb_channels)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  ARCompressorFilter<DataType_>::~ARCompressorFilter()
  {
    
  }

  template<typename DataType_>
  void ARCompressorFilter<DataType_>::process_impl(std::int64_t size)
  {
    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      for(std::int64_t i = 0; i < size; ++i)
      {
        outputs[channel][i] = converted_inputs[2 * channel][i] * converted_inputs[2 * channel + 1][i];
      }
    }
  }
  
  template class ARCompressorFilter<float>;
  template class ARCompressorFilter<double>;
}
