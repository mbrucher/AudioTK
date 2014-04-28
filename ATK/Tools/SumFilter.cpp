/**
 * \file SumFilter.cpp
 */

#include "SumFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  SumFilter<DataType_>::SumFilter()
  :Parent(2, 1)
  {
    
  }
  
  template<typename DataType_>
  SumFilter<DataType_>::~SumFilter()
  {
    
  }

  template<typename DataType_>
  void SumFilter<DataType_>::process_impl(std::int64_t size)
  {
    for(std::int64_t i = 0; i < size; ++i)
    {
      outputs[0][i] = static_cast<DataType>(converted_inputs[0][i] + converted_inputs[1][i]);
    }
  }
  
  template class SumFilter<std::int16_t>;
  template class SumFilter<std::int32_t>;
  template class SumFilter<std::int64_t>;
  template class SumFilter<float>;
  template class SumFilter<double>;
}
