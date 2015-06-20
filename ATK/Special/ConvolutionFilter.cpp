/**
 * \file ConvolutionFilter.cpp
 */

#include "ConvolutionFilter.h"

#include <cassert>

namespace ATK
{
  template <typename DataType>
  ConvolutionFilter<DataType>::ConvolutionFilter(int nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::set_impulse(std::vector<DataType> impulse)
  {
    in_order = static_cast<int>(impulse.size() - 1);
    input_delay = in_order;
    this->impulse = std::move(impulse);

    setup();
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);
    assert(nb_input_ports == nb_output_ports);
    
    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        DataType tempout = impulse[in_order] * input[i];
        
        for(int j = 0; j < in_order; ++j)
        {
          tempout += impulse[j] * input[i - in_order + j];
        }
        output[i] = tempout;
      }
    }
  }

  template class ConvolutionFilter<double>;
}
