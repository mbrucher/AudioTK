/**
 * \file DecimationFilter.cpp
 */

#include "DecimationFilter.h"

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
  void DecimationFilter<DataType>::process_impl(long size)
  {
    for(int j = 0; j < outputs_size.size(); ++j)
    {
      if(outputs_size[j] < size)
      {
        outputs[j].reset(new DataType[size]);
        outputs_size[j] = size;
      }
    }
    
    for(int j = 0; j < outputs_size.size(); ++j)
    {
      for(long i = 0; i < size; ++i)
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
