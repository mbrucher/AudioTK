/**
 * \file ReduceFilter.hxx
 */

#include <ATK/Tools/SIMD/ReduceFilter.h>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<typename DataType_, typename DataType__>
  ReduceFilter<DataType_, DataType__>::ReduceFilter(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_, typename DataType__>
  ReduceFilter<DataType_, DataType__>::~ReduceFilter()
  {
  }

  template<typename DataType_, typename DataType__>
  void ReduceFilter<DataType_, DataType__>::process_impl(std::size_t size) const
  {
    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType_* ATK_RESTRICT input = converted_inputs[channel];
      DataType__* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        output[i] = simdpp::reduce_add(input[i]);
      }
    }
  }
}
