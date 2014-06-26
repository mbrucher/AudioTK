/**
 * \file UniversalFixedDelayLineFilter.cpp
 */

#include "UniversalFixedDelayLineFilter.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  UniversalFixedDelayLineFilter<DataType_>::UniversalFixedDelayLineFilter(int max_delay)
  :Parent(1, 1), delay_line(max_delay, 0), delay(0), blend(0), feedback(0), feedforward(1)
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
  void UniversalFixedDelayLineFilter<DataType_>::set_blend(DataType blend)
  {
    this->blend = blend;
  }

  template<typename DataType_>
  DataType_ UniversalFixedDelayLineFilter<DataType_>::get_blend() const
  {
    return blend;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_feedback(DataType feedback)
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
  void UniversalFixedDelayLineFilter<DataType_>::set_feedforward(DataType feedforward)
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
    processed_input.resize(size);

    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];

    std::int64_t delay_line_usage = std::min(delay, size);

    // Update intermediate input
    for(std::int64_t i = 0; i < delay_line_usage; ++i)
    {
      processed_input[i] = input[i] + feedback * delay_line[delay_line.size() + i - delay];
    }
    for(std::int64_t i = delay; i < size; ++i)
    {
      processed_input[i] = input[i] + feedback * processed_input[i - delay];
    }

    //update output
    for(std::int64_t i = 0; i < delay_line_usage; ++i)
    {
      output[i] = blend * processed_input[i] + feedforward *  delay_line[delay_line.size() + i - delay];
    }
    for(std::int64_t i = delay; i < size; ++i)
    {
      output[i] = blend * processed_input[i] + feedforward * processed_input[i - delay];
    }

    // Update delay line
    for(std::int64_t i = 0; i < std::int64_t(delay_line.size()) - size; ++i)
    {
      delay_line[i] = delay_line[i + size];
    }
    std::int64_t minimum = std::max(std::int64_t(0), std::int64_t(delay_line.size()) - size);
    for(std::int64_t i = minimum; i < delay_line.size(); ++i)
    {
      delay_line[i] = processed_input[size + i - delay_line.size()];
    }
  }
  
  template class UniversalFixedDelayLineFilter<float>;
  template class UniversalFixedDelayLineFilter<double>;
}
