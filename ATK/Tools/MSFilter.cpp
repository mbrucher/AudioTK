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
  void MiddleSideFilter<DataType_>::process_impl(std::int64_t size)
  {
    for(std::int64_t i = 0; i < size; ++i)
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
