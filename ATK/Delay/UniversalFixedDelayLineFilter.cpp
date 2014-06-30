/**
 * \file UniversalFixedDelayLineFilter.cpp
 */

#include "UniversalFixedDelayLineFilter.h"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  UniversalFixedDelayLineFilter<DataType_>::UniversalFixedDelayLineFilter(int max_delay)
    :Parent(1, 1), processed_input(max_delay, 0), max_delay(max_delay), delay(0), blend(0), feedback(0), feedforward(1)
  {
  }
  
  template<typename DataType_>
  UniversalFixedDelayLineFilter<DataType_>::~UniversalFixedDelayLineFilter()
  {
    
  }
  
  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_delay(std::int64_t delay)
  {
    if(delay < 0)
    {
      throw std::out_of_range("Delay must be positive");
    }
    if(delay >= delay_line.size())
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    this->delay = delay;
  }

  template<typename DataType_>
  std::int64_t UniversalFixedDelayLineFilter<DataType_>::get_delay() const
  {
    return delay;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_blend(DataType_ blend)
  {
    this->blend = blend;
  }

  template<typename DataType_>
  DataType_ UniversalFixedDelayLineFilter<DataType_>::get_blend() const
  {
    return blend;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_feedback(DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    this->feedback = feedback;
  }

  template<typename DataType_>
  DataType_ UniversalFixedDelayLineFilter<DataType_>::get_feedback() const
  {
    return feedback;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_feedforward(DataType_ feedforward)
  {
    this->feedforward = feedforward;
  }

  template<typename DataType_>
  DataType_ UniversalFixedDelayLineFilter<DataType_>::get_feedforward() const
  {
    return feedforward;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::process_impl(std::int64_t size)
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0]; // samples
    DataType* ATK_RESTRICT output = outputs[0];

    // Update delay line
    for (std::int64_t i = 0; i < max_delay; ++i)
    {
      processed_input[i] = processed_input[processed_input.size() + i - max_delay];
    }
    delay_line.resize(size);
    processed_input.resize(size + max_delay);

    DataType* ATK_RESTRICT delay_line_ptr = delay_line.data();
    DataType* ATK_RESTRICT processed_input_ptr = processed_input.data() + max_delay;

    for (std::int64_t i = 0; i < size; ++i)
    {
      delay_line_ptr[i] = processed_input_ptr[i - delay];
      processed_input_ptr[i] = input[i] + feedback * delay_line_ptr[i];
      output[i] = blend * processed_input_ptr[i] + feedforward * delay_line_ptr[i];
    }
  }
  
  template class UniversalFixedDelayLineFilter<float>;
  template class UniversalFixedDelayLineFilter<double>;
}
