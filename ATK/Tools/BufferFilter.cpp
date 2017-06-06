/**
 * \file BufferFilter.cpp
 */

#include "BufferFilter.h"

#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  BufferFilter<DataType_>::BufferFilter(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels)
  {
    
  }
  
  template<typename DataType_>
  BufferFilter<DataType_>::~BufferFilter()
  {
  }
  
  template<typename DataType_>
  void BufferFilter<DataType_>::process_impl(std::size_t size) const
  {
    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        output[i] = input[i];
      }
    }
  }
  
  template class BufferFilter<std::int16_t>;
  template class BufferFilter<std::int32_t>;
  template class BufferFilter<std::int64_t>;
  template class BufferFilter<float>;
  template class BufferFilter<double>;
  template class BufferFilter<std::complex<float>>;
  template class BufferFilter<std::complex<double>>;
}
