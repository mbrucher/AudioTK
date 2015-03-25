/**
 * \file DerivativeFilter.cpp
 */

#include "DerivativeFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  DerivativeFilter<DataType_>::DerivativeFilter()
  :Parent(1, 1)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  DerivativeFilter<DataType_>::~DerivativeFilter()
  {
    
  }

  template<typename DataType_>
  void DerivativeFilter<DataType_>::process_impl(std::int64_t size)
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];

    for(std::int64_t i = 0; i < size; ++i)
    {
      output[i] = input[i] - input[i-1];
    }
  }
  
  template class DerivativeFilter<std::int16_t>;
  template class DerivativeFilter<std::int32_t>;
  template class DerivativeFilter<std::int64_t>;
  template class DerivativeFilter<float>;
  template class DerivativeFilter<double>;
}
