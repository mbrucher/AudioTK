/**
 * \file DecimationFilter.cpp
 */

#include "DecimationFilter.h"

#include <cstdint>

namespace ATK
{
  template<class DataType>
  DecimationFilter<DataType>::DecimationFilter(int ports)
  :TypedBaseFilter<DataType>(ports, ports)
  {
  }
  
  template<class DataType>
  DecimationFilter<DataType>::~DecimationFilter()
  {
  }
  
  template<class DataType>
  void DecimationFilter<DataType>::setup()
  {
    Parent::setup();
    if(output_sampling_rate == 0 || input_sampling_rate % output_sampling_rate != 0)
    {
      decimation = 0;
    }
    else
    {
      decimation = (input_sampling_rate / output_sampling_rate);
    }
  }
  
  template<class DataType>
  void DecimationFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        output[i] = input[i * decimation];
      }
    }
  }
  
  template class DecimationFilter<std::int16_t>;
  template class DecimationFilter<std::int32_t>;
  template class DecimationFilter<int64_t>;
  template class DecimationFilter<float>;
  template class DecimationFilter<double>;
}
