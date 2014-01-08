/**
 * \file MSFilter.cpp
 */

#include "MSFilter.h"

#include <cmath>

namespace ATK
{
  template<typename DataType_>
  MiddleSideFilter<DataType_>::MiddleSideFilter()
  :Parent(2, 2)
  {
    
  }
  
  template<typename DataType_>
  MiddleSideFilter<DataType_>::~MiddleSideFilter()
  {
    
  }
  
  template<typename DataType_>
  void MiddleSideFilter<DataType_>::process_impl(int size)
  {
    if(outputs_size[0] < size)
    {
      outputs[0].reset(new DataType[size]);
      outputs_size[0] = size;
    }
    if(outputs_size[1] < size)
    {
      outputs[1].reset(new DataType[size]);
      outputs_size[1] = size;
    }
    
    for(int i = 0; i < size; ++i)
    {
      outputs[0][i] = static_cast<DataType>((converted_inputs[0][i] + converted_inputs[1][i]) / 2);
      outputs[1][i] = static_cast<DataType>((converted_inputs[0][i] - converted_inputs[1][i]) / 2);
    }
    
  }
  
  template class MiddleSideFilter<std::int16_t>;
  template class MiddleSideFilter<std::int32_t>;
  template class MiddleSideFilter<std::int64_t>;
  template class MiddleSideFilter<float>;
  template class MiddleSideFilter<double>;
}
