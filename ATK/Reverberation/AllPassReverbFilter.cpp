/**
 * \file AllPassReverbFilter.cpp
 */

#include "AllPassReverbFilter.h"

#include <iostream>
#include <cmath>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  AllPassReverbFilter<DataType_>::AllPassReverbFilter(int max_delay)
    :Parent(1, 1), delay(0), feedback(0)
  {
    output_delay = max_delay;
    input_delay = max_delay;
  }
  
  template<typename DataType_>
  AllPassReverbFilter<DataType_>::~AllPassReverbFilter()
  {
  }
  
  template<typename DataType_>
  void AllPassReverbFilter<DataType_>::set_delay(int64_t delay)
  {
    if(delay < 0)
    {
      throw std::out_of_range("Delay must be positive");
    }
    if(delay >= static_cast<int64_t>(output_delay))
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    this->delay = delay;
  }

  template<typename DataType_>
  int64_t AllPassReverbFilter<DataType_>::get_delay() const
  {
    return delay;
  }

  template<typename DataType_>
  void AllPassReverbFilter<DataType_>::set_feedback(DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    this->feedback = feedback;
  }

  template<typename DataType_>
  DataType_ AllPassReverbFilter<DataType_>::get_feedback() const
  {
    return feedback;
  }

  template<typename DataType_>
  void AllPassReverbFilter<DataType_>::process_impl(int64_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(int64_t i = 0; i < size; ++i)
    {
      output[i] = feedback * (output[i - delay] - input[i]) + input[i - delay];
    }
  }

  template class AllPassReverbFilter<float>;
  template class AllPassReverbFilter<double>;
}
