/**
 * \file OneMinusFilter.cpp
 */

#include "OneMinusFilter.h"

#include <cassert>
#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  OneMinusFilter<DataType_>::OneMinusFilter(int nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  OneMinusFilter<DataType_>::~OneMinusFilter()
  {
  }

  template<typename DataType_>
  void OneMinusFilter<DataType_>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        *(output++) = 1 - *(input++);
      }
    }
  }
  
  template class OneMinusFilter<int16_t>;
  template class OneMinusFilter<int32_t>;
  template class OneMinusFilter<int64_t>;
  template class OneMinusFilter<float>;
  template class OneMinusFilter<double>;
}
