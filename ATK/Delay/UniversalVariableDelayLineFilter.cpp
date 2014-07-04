/**
 * \file UniversalVariableDelayLineFilter.cpp
 */

#include "UniversalVariableDelayLineFilter.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  UniversalVariableDelayLineFilter<DataType_>::UniversalVariableDelayLineFilter(int max_delay)
  :Parent(2, 1), processed_input(max_delay, 0), max_delay(max_delay), blend(0), feedback(0), feedforward(1), last_delay(0)
  {
  }
  
  template<typename DataType_>
  UniversalVariableDelayLineFilter<DataType_>::~UniversalVariableDelayLineFilter()
  {
    
  }

  template<typename DataType_>
  void UniversalVariableDelayLineFilter<DataType_>::set_blend(DataType_ blend)
  {
    this->blend = blend;
  }
  
  template<typename DataType_>
  DataType_ UniversalVariableDelayLineFilter<DataType_>::get_blend() const
  {
    return blend;
  }
  
  template<typename DataType_>
  void UniversalVariableDelayLineFilter<DataType_>::set_feedback(DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    this->feedback = feedback;
  }
  
  template<typename DataType_>
  DataType_ UniversalVariableDelayLineFilter<DataType_>::get_feedback() const
  {
    return feedback;
  }
  
  template<typename DataType_>
  void UniversalVariableDelayLineFilter<DataType_>::set_feedforward(DataType_ feedforward)
  {
    this->feedforward = feedforward;
  }
  
  template<typename DataType_>
  DataType_ UniversalVariableDelayLineFilter<DataType_>::get_feedforward() const
  {
    return feedforward;
  }

  template<typename DataType_>
  void UniversalVariableDelayLineFilter<DataType_>::process_impl(std::int64_t size)
  {
    const DataType* ATK_RESTRICT input1 = converted_inputs[0]; // samples
    const DataType* ATK_RESTRICT input2 = converted_inputs[1]; // delay
    DataType* ATK_RESTRICT output = outputs[0];

    // Update delay line
    for(std::int64_t i = 0; i < max_delay; ++i)
    {
      processed_input[i] = processed_input[processed_input.size() + i - max_delay];
    }

    delay_line.resize(size);
    processed_input.resize(size + max_delay);
    DataType* ATK_RESTRICT delay_line_ptr = delay_line.data();
    DataType* ATK_RESTRICT processed_input_ptr = processed_input.data();

    // Update the delay line
    integer_delay.resize(size);
    fractional_delay.resize(size);
    for(std::int64_t i = 0; i < size; ++i)
    {
      integer_delay[i] = static_cast<std::int64_t>(input2[i]);
      assert(integer_delay[i] > 0);
      assert(integer_delay[i] < (max_delay - 1));
      fractional_delay[i] = input2[i] - integer_delay[i];
    }

    for(std::int64_t i = 0; i < size; ++i)
    {
      //delay_line_ptr[i] = processed_input_ptr[i + max_delay - integer_delay[i]] * (1 - fractional_delay[i]) + processed_input_ptr[i + max_delay - integer_delay[i] - 1] * fractional_delay[i];
      delay_line_ptr[i] = (processed_input_ptr[i + max_delay - integer_delay[i]] - last_delay) * (1 - fractional_delay[i]) + processed_input_ptr[i + max_delay - integer_delay[i] - 1];
      processed_input_ptr[max_delay + i] = input1[i] + feedback * delay_line_ptr[i];
      output[i] = blend * input1[i] + feedforward * delay_line_ptr[i];
      last_delay = delay_line_ptr[i];
    }
  }
  
  template class UniversalVariableDelayLineFilter<float>;
  template class UniversalVariableDelayLineFilter<double>;
}
