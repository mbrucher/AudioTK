/**
 * \file UniversalFixedDelayLineFilter.cpp
 */

#include "UniversalFixedDelayLineFilter.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace ATK
{
  template<typename DataType>
  class UniversalFixedDelayLineFilter<DataType>::UFDLF_Impl
  {
  public:
    std::vector<DataType> delay_line;
    std::vector<DataType> processed_input;

    UFDLF_Impl(std::size_t max_delay)
      :delay_line(max_delay, 0)
    {
    }
  };

  template<typename DataType_>
  UniversalFixedDelayLineFilter<DataType_>::UniversalFixedDelayLineFilter(std::size_t max_delay)
    :Parent(1, 1), impl(new UFDLF_Impl(max_delay)), delay(0), blend(0), feedback(0), feedforward(1)
  {
  }
  
  template<typename DataType_>
  UniversalFixedDelayLineFilter<DataType_>::~UniversalFixedDelayLineFilter()
  {
  }
  
  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_delay(std::size_t delay)
  {
    if(delay == 0)
    {
      throw std::out_of_range("Delay must be strictly positive");
    }
    if(delay >= impl->delay_line.size())
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    this->delay = delay;
  }

  template<typename DataType_>
  std::size_t UniversalFixedDelayLineFilter<DataType_>::get_delay() const
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
  void UniversalFixedDelayLineFilter<DataType_>::full_setup()
  {
    // reset the delay line
    impl->delay_line.assign(impl->delay_line.size(), 0);
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::process_impl(std::size_t size) const
  {
    impl->processed_input.resize(size);

    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];

    DataType* ATK_RESTRICT processed_input = impl->processed_input.data();
    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();
    auto delay_line_size = impl->delay_line.size();

    std::size_t delay_line_usage = std::min(delay, size);

    // Update intermediate input
    ATK_VECTORIZE for(std::size_t i = 0; i < delay_line_usage; ++i)
    {
      processed_input[i] = input[i] + feedback * delay_line[delay_line_size + i - delay];
    }
    ATK_VECTORIZE for(std::size_t i = delay; i < size; ++i)
    {
      processed_input[i] = input[i] + feedback * processed_input[i - delay];
    }

    //update output
    ATK_VECTORIZE for(std::size_t i = 0; i < delay_line_usage; ++i)
    {
      output[i] = blend * processed_input[i] + feedforward *  delay_line[delay_line_size + i - delay];
    }
    ATK_VECTORIZE for(std::size_t i = delay; i < size; ++i)
    {
      output[i] = blend * processed_input[i] + feedforward * processed_input[i - delay];
    }

    auto minimum = delay_line_size > size ? delay_line_size - size : 0;
    // Update delay line
    ATK_VECTORIZE for (std::size_t i = 0; i < minimum; ++i)
    {
      delay_line[i] = delay_line[i + size];
    }
    ATK_VECTORIZE for (std::size_t i = minimum; i < delay_line_size; ++i)
    {
      delay_line[i] = processed_input[size + i - delay_line_size];
    }
  }

  template class UniversalFixedDelayLineFilter<float>;
  template class UniversalFixedDelayLineFilter<double>;
}
