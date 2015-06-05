/**
 * \file VariableDelayLineFilter.cpp
 */

#include "VariableDelayLineFilter.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  VariableDelayLineFilter<DataType_>::VariableDelayLineFilter(int max_delay)
  :Parent(2, 1), delay_line(max_delay, 0), max_delay(max_delay)
  {
  }
  
  template<typename DataType_>
  VariableDelayLineFilter<DataType_>::~VariableDelayLineFilter()
  {
    
  }

  template<typename DataType_>
  void VariableDelayLineFilter<DataType_>::process_impl(std::int64_t size) const
  {
    const DataType* ATK_RESTRICT input1 = converted_inputs[0]; // samples
    const DataType* ATK_RESTRICT input2 = converted_inputs[1]; // delay
    DataType* ATK_RESTRICT output = outputs[0];

    // Update delay line
    for(std::int64_t i = 0; i < max_delay; ++i)
    {
      delay_line[i] = delay_line[delay_line.size() + i - max_delay];
    }
    delay_line.resize(size + max_delay);
    memcpy(reinterpret_cast<void*>(delay_line.data() + max_delay), reinterpret_cast<const void*>(input1), size * sizeof(DataType));
    
    integer_delay.resize(size);
    fractional_delay.resize(size);
    for(std::int64_t i = 0; i < size; ++i)
    {
      integer_delay[i] = static_cast<std::int64_t>(input2[i]);
      fractional_delay[i] = input2[i] - integer_delay[i];
    }

    for(std::int64_t i = 0; i < size; ++i)
    {
      output[i] = delay_line[i + max_delay - integer_delay[i]] * (1 - fractional_delay[i]) + delay_line[i + max_delay - integer_delay[i] - 1] * fractional_delay[i];
    }
  }
  
  template class VariableDelayLineFilter<float>;
  template class VariableDelayLineFilter<double>;
}
