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
  void DecimationFilter<DataType>::process_impl(std::int64_t size)
  {    
    for(int j = 0; j < outputs_size.size(); ++j)
    {
      for(std::int64_t i = 0; i < size; ++i)
      {
        outputs[j][i] = converted_inputs[j][i * decimation];
      }
    }
  }
  
  template class DecimationFilter<std::int16_t>;
  template class DecimationFilter<std::int32_t>;
  template class DecimationFilter<std::int64_t>;
  template class DecimationFilter<float>;
  template class DecimationFilter<double>;
}
