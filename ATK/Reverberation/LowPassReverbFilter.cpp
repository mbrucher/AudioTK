/**
 * \file LowPassReverbFilter.cpp
 */

#include <ATK/Reverberation/LowPassReverbFilter.h>

#include <iostream>
#include <cmath>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  LowPassReverbFilter<DataType_>::LowPassReverbFilter(std::size_t max_delay)
    :Parent(1, 1), delay(0), feedback(0), cutoff(0)
  {
    output_delay = max_delay;
    input_delay = max_delay;
  }
  
  template<typename DataType_>
  LowPassReverbFilter<DataType_>::~LowPassReverbFilter()
  {
  }
  
  template<typename DataType_>
  void LowPassReverbFilter<DataType_>::set_delay(std::size_t delay)
  {
    if(delay == 0)
    {
      throw std::out_of_range("Delay must be strictly positive");
    }
    if(delay + 1 >= output_delay)
    {
      throw std::out_of_range("Delay must be less than delay line size - 1");
    }

    this->delay = delay;
  }

  template<typename DataType_>
  std::size_t LowPassReverbFilter<DataType_>::get_delay() const
  {
    return delay;
  }
  
  template<typename DataType_>
  void LowPassReverbFilter<DataType_>::set_feedback(DataType_ feedback)
  {
    if(std::abs(feedback + cutoff) > 1)
    {
      throw std::out_of_range("Sum of Feedback and Cutoff must be between -1 and 1 to avoid divergence");
    }
    this->feedback = feedback;
  }
  
  template<typename DataType_>
  DataType_ LowPassReverbFilter<DataType_>::get_feedback() const
  {
    return feedback;
  }
  
  template<typename DataType_>
  void LowPassReverbFilter<DataType_>::set_cutoff(DataType_ cutoff)
  {
    if(std::abs(feedback + cutoff) > 1)
    {
      throw std::out_of_range("Sum of Feedback and Cutoff must be between -1 and 1 to avoid divergence");
    }
    this->cutoff = cutoff;
  }
  
  template<typename DataType_>
  DataType_ LowPassReverbFilter<DataType_>::get_cutoff() const
  {
    return cutoff;
  }

  template<typename DataType_>
  void LowPassReverbFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(std::size_t i = 0; i < size; ++i)
    {
      output[i] = feedback * output[i - delay] + input[i - delay] + cutoff * (output[i - 1] - input[i - delay - 1]);
    }
  }

  template class LowPassReverbFilter<float>;
  template class LowPassReverbFilter<double>;
}
