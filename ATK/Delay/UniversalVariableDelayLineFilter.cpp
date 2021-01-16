/**
 * \file UniversalVariableDelayLineFilter.cpp
 */

#include "UniversalVariableDelayLineFilter.h"
#include <ATK/Core/Utilities.h>

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>

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
    std::vector<gsl::index> integer_delay;
    /// Fractional portion of the delay for the last processed chunk, used for the interpolation
    std::vector<DataType> fractional_delay;
    DataType last_delay{0};

    explicit UVDLF_Impl(gsl::index max_delay)
      :processed_input(max_delay, 0)
    {
    }

    void update_delay_line(gsl::index max_delay, gsl::index size)
    {
      auto array_size = processed_input.size();
      // Update delay line
      ATK_VECTORIZE for (gsl::index i = 0; i < max_delay; ++i)
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
  UniversalVariableDelayLineFilter<DataType_>::UniversalVariableDelayLineFilter(gsl::index max_delay)
    :Parent(2, 1), impl(std::make_unique<UVDLF_Impl>(max_delay)), max_delay(max_delay), central_delay(max_delay / 2)
  {
  }
  
  template<typename DataType_>
  UniversalVariableDelayLineFilter<DataType_>::~UniversalVariableDelayLineFilter()
  {
    
  }

  template<typename DataType_>
  void UniversalVariableDelayLineFilter<DataType_>::set_central_delay(gsl::index central_delay)
  {
    this->central_delay = central_delay;
  }

  template<typename DataType_>
  gsl::index UniversalVariableDelayLineFilter<DataType_>::get_central_delay() const
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
    if(std::abs(feedback) >= 1)
    {
      throw ATK::RuntimeError("Feedback must be between -1 and 1 to avoid divergence");
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
  void UniversalVariableDelayLineFilter<DataType_>::process_impl(gsl::index size) const
  {
    impl->update_delay_line(max_delay, size);
    const DataType* ATK_RESTRICT input1 = converted_inputs[0]; // samples
    const DataType* ATK_RESTRICT input2 = converted_inputs[1]; // delay
    DataType* ATK_RESTRICT output = outputs[0];

    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();
    DataType* ATK_RESTRICT processed_input = impl->processed_input.data();
    gsl::index* ATK_RESTRICT integer_delay = impl->integer_delay.data();
    DataType* ATK_RESTRICT fractional_delay = impl->fractional_delay.data();

    // Update the delay line
    ATK_VECTORIZE for(gsl::index i = 0; i < size; ++i)
    {
      auto rounded = static_cast<gsl::index>(input2[i]);
      integer_delay[i] = rounded >= max_delay ? 0 : rounded;
      fractional_delay[i] = input2[i] - integer_delay[i];
    }

    ATK_VECTORIZE for(gsl::index i = 0; i < size; ++i)
    {
      delay_line[i] = (processed_input[i + max_delay - integer_delay[i]] - impl->last_delay) * (1 - fractional_delay[i]) + processed_input[i + max_delay - integer_delay[i] - 1];
      processed_input[max_delay + i] = input1[i] + feedback * processed_input[max_delay + i - central_delay]; // FB only uses the central delay and is not varying
      output[i] = blend * processed_input[max_delay + i] + feedforward * delay_line[i];
      impl->last_delay = delay_line[i]; // the reason why the test is not that simple!
    }
  }
  
  template class UniversalVariableDelayLineFilter<double>;
#if ATK_ENABLE_INSTANTIATION
  template class UniversalVariableDelayLineFilter<float>;
#endif
}
