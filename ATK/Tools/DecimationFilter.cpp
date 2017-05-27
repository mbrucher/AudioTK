/**
 * \file DecimationFilter.cpp
 */

#include "DecimationFilter.h"

#include <cassert>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<class DataType>
  DecimationFilter<DataType>::DecimationFilter(std::size_t nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels)
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
      decimation = static_cast<int>(input_sampling_rate / output_sampling_rate);
    }
  }
  
  template<class DataType>
  void DecimationFilter<DataType>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        output[i] = input[i*decimation];
      }
    }
  }
  
  template class DecimationFilter<std::int16_t>;
  template class DecimationFilter<std::int32_t>;
  template class DecimationFilter<int64_t>;
  template class DecimationFilter<float>;
  template class DecimationFilter<double>;
  template class DecimationFilter<std::complex<float>>;
  template class DecimationFilter<std::complex<double>>;
}
