/**
 * \file BroadcastFilter.hxx
 */

#include <ATK/Tools/SIMD/BroadcastFilter.h>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<typename DataType_, typename DataType__>
  BroadcastFilter<DataType_, DataType__>::BroadcastFilter(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_, typename DataType__>
  BroadcastFilter<DataType_, DataType__>::~BroadcastFilter()
  {
  }

  template<typename DataType_, typename DataType__>
  void BroadcastFilter<DataType_, DataType__>::process_impl(std::size_t size) const
  {
    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType_* ATK_RESTRICT input = converted_inputs[channel];
      DataType__* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        output[i] = simdpp::load_splat(input + i);
      }
    }
  }
}
