/**
 * \file DecimationFilter.hxx
 */

#include "DecimationFilter.h"

#include <cassert>

namespace ATK
{
  template<class DataType>
  DecimationFilter<DataType>::DecimationFilter(gsl::index nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels)
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
  void DecimationFilter<DataType>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = input[i*decimation];
      }
    }
  }
}
