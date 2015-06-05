/**
 * \file MaxFilter.cpp
 */

#include "MaxFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  MaxFilter<DataType_>::MaxFilter()
  :Parent(2, 1)
  {
    
  }
  
  template<typename DataType_>
  MaxFilter<DataType_>::~MaxFilter()
  {
    
  }

  template<typename DataType_>
  void MaxFilter<DataType_>::process_impl(std::int64_t size) const
  {
    const DataType* ATK_RESTRICT input0 = converted_inputs[0];
    const DataType* ATK_RESTRICT input1 = converted_inputs[1];
    DataType* ATK_RESTRICT output = outputs[0];
    for(std::int64_t i = 0; i < size; ++i)
    {
      output[i] = std::max(input0[i], input1[i]);
    }
  }
  
  template class MaxFilter<std::int16_t>;
  template class MaxFilter<std::int32_t>;
  template class MaxFilter<std::int64_t>;
  template class MaxFilter<float>;
  template class MaxFilter<double>;
}
