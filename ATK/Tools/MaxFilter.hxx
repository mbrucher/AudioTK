/**
 * \file MaxFilter.hxx
 */

#include <ATK/Tools/MaxFilter.h>

namespace ATK
{
  template<typename DataType_>
  MaxFilter<DataType_>::MaxFilter(std::size_t nb_channels)
  :Parent(2 * nb_channels, nb_channels)
  {
    
  }
  
  template<typename DataType_>
  MaxFilter<DataType_>::~MaxFilter()
  {
    
  }

  template<typename DataType_>
  void MaxFilter<DataType_>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == 2 * nb_output_ports);

    for (unsigned int channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input0 = converted_inputs[2 * channel];
      const DataType* ATK_RESTRICT input1 = converted_inputs[2 * channel + 1];
      DataType* ATK_RESTRICT output = outputs[channel];
      for (std::size_t i = 0; i < size; ++i)
      {
        output[i] = TypeTraits<DataType>::max(input0[i], input1[i]);
      }
    }
  }
}
