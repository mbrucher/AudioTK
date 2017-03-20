/**
 * \file MSFilter.cpp
 */

#include "MSFilter.h"

#include <cmath>
#include <cstdint>

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
  void MiddleSideFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input0 = converted_inputs[0];
    const DataType* ATK_RESTRICT input1 = converted_inputs[1];
    DataType* ATK_RESTRICT output0 = outputs[0];
    DataType* ATK_RESTRICT output1 = outputs[1];

    for(std::size_t i = 0; i < size; ++i)
    {
      *(output0++) = static_cast<DataType>((*(input0) + *(input1)));
      *(output1++) = static_cast<DataType>((*(input0++) - *(input1++)));
    }
  }
  
  template class MiddleSideFilter<std::int16_t>;
  template class MiddleSideFilter<std::int32_t>;
  template class MiddleSideFilter<int64_t>;
  template class MiddleSideFilter<float>;
  template class MiddleSideFilter<double>;
}
