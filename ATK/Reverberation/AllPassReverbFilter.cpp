/**
 * \file AllPassReverbFilter.cpp
 */

#include "AllPassReverbFilter.h"
#include <ATK/Core/Utilities.h>

#include <iostream>
#include <cmath>

namespace ATK
{
  template<typename DataType_>
  AllPassReverbFilter<DataType_>::AllPassReverbFilter(gsl::index max_delay)
    :Parent(1, 1)
  {
    output_delay = max_delay;
    input_delay = max_delay;
  }
  
  template<typename DataType_>
  void AllPassReverbFilter<DataType_>::set_delay(gsl::index delay)
  {
    if(delay == 0)
    {
      throw ATK::RuntimeError("Delay must be strictly positive");
    }
    if(delay >= output_delay)
    {
      throw ATK::RuntimeError("Delay must be less than delay line size");
    }

    this->delay = delay;
  }

  template<typename DataType_>
  gsl::index AllPassReverbFilter<DataType_>::get_delay() const
  {
    return delay;
  }

  template<typename DataType_>
  void AllPassReverbFilter<DataType_>::set_feedback(DataType_ feedback)
  {
    if(std::abs(feedback) >= 1)
    {
      throw ATK::RuntimeError("Feedback must be between -1 and 1 to avoid divergence");
    }
    this->feedback = feedback;
  }

  template<typename DataType_>
  DataType_ AllPassReverbFilter<DataType_>::get_feedback() const
  {
    return feedback;
  }

  template<typename DataType_>
  void AllPassReverbFilter<DataType_>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    for(gsl::index i = 0; i < size; ++i)
    {
      output[i] = feedback * (output[i - delay] - input[i]) + input[i - delay];
    }
  }

#if ATK_ENABLE_INSTANTIATION
  template class AllPassReverbFilter<float>;
#endif
  template class AllPassReverbFilter<double>;
}
