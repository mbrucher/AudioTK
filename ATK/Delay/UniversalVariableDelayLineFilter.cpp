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
  template<typename DataType>
  class UniversalVariableDelayLineFilter<DataType>::UVDLF_Impl
  {
  public:
    /// Delay line contains the last size elements + max_delay of the last delay line
    std::vector<DataType> delay_line;
    std::vector<DataType> processed_input;

    /// Integer portion of the delay for the last processed chunk
    std::vector<int64_t> integer_delay;
    /// Fractional portion of the delay for the last processed chunk, used for the interpolation
    std::vector<DataType> fractional_delay;
    DataType last_delay;

    UVDLF_Impl(int max_delay)
      :processed_input(max_delay, 0), last_delay(0)
    {
    }

    void update_delay_line(int64_t max_delay, int64_t size)
    {
      auto array_size = processed_input.size();
      // Update delay line
      ATK_VECTORIZE for (int64_t i = 0; i < max_delay; ++i)
      {
        processed_input[i] = processed_input[array_size + i - max_delay];
      }
      delay_line.resize(size);
      processed_input.resize(size + max_delay);
      integer_delay.resize(size);
      fractional_delay.resize(size);
    }
  };

  template<typename DataType_>
  UniversalVariableDelayLineFilter<DataType_>::UniversalVariableDelayLineFilter(int max_delay)
    :Parent(2, 1), impl(new UVDLF_Impl(max_delay)), max_delay(max_delay), central_delay(max_delay/2), blend(0), feedback(0), feedforward(1)
  {
  }
  
  template<typename DataType_>
  UniversalVariableDelayLineFilter<DataType_>::~UniversalVariableDelayLineFilter()
  {
    
  }

  template<typename DataType_>
  void UniversalVariableDelayLineFilter<DataType_>::set_central_delay(int central_delay)
  {
    this->central_delay = central_delay;
  }

  template<typename DataType_>
  int UniversalVariableDelayLineFilter<DataType_>::get_central_delay() const
  {
    return central_delay;
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
  void UniversalVariableDelayLineFilter<DataType_>::full_setup()
  {
    // reset the delay line
    impl->processed_input.assign(max_delay, 0);
    impl->last_delay = 0;
  }

  template<typename DataType_>
  void UniversalVariableDelayLineFilter<DataType_>::process_impl(int64_t size) const
  {
    impl->update_delay_line(max_delay, size);
    const DataType* ATK_RESTRICT input1 = converted_inputs[0]; // samples
    const DataType* ATK_RESTRICT input2 = converted_inputs[1]; // delay
    DataType* ATK_RESTRICT output = outputs[0];

    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();
    DataType* ATK_RESTRICT processed_input = impl->processed_input.data();
    int64_t* ATK_RESTRICT integer_delay = impl->integer_delay.data();
    DataType* ATK_RESTRICT fractional_delay = impl->fractional_delay.data();

    // Update the delay line
    ATK_VECTORIZE for(int64_t i = 0; i < size; ++i)
    {
      integer_delay[i] = static_cast<int64_t>(input2[i]);
      assert(integer_delay[i] > 0);
      assert(integer_delay[i] < (max_delay - 1));
      fractional_delay[i] = input2[i] - integer_delay[i];
    }

    ATK_VECTORIZE for(int64_t i = 0; i < size; ++i)
    {
      delay_line[i] = (processed_input[i + max_delay - integer_delay[i]] - impl->last_delay) * (1 - fractional_delay[i]) + processed_input[i + max_delay - integer_delay[i] - 1] * fractional_delay[i];
      processed_input[max_delay + i] = input1[i] + feedback * processed_input[max_delay + i - central_delay]; // FB only uses the central delay and is not varying
      output[i] = blend * processed_input[max_delay + i] + feedforward * delay_line[i];
      impl->last_delay = delay_line[i]; // the reason why the test is not that simple!
    }
  }
  
  template class UniversalVariableDelayLineFilter<float>;
  template class UniversalVariableDelayLineFilter<double>;
}
