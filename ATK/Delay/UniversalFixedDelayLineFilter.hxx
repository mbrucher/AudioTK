/**
 * \file UniversalFixedDelayLineFilter.hxx
 */

#include "UniversalFixedDelayLineFilter.h"
#include <ATK/Core/Utilities.h>

#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType>
  class UniversalFixedDelayLineFilter<DataType>::UFDLF_Impl
  {
  public:
    std::vector<DataType> delay_line;
    gsl::index index{0};

    explicit UFDLF_Impl(gsl::index max_delay)
      :delay_line(max_delay, TypeTraits<DataType>::Zero())
    {
    }
  };

  template<typename DataType_>
  UniversalFixedDelayLineFilter<DataType_>::UniversalFixedDelayLineFilter(gsl::index max_delay)
    :Parent(1, 2), impl(std::make_unique<UFDLF_Impl>(max_delay))
  {
  }
  
  template<typename DataType_>
  UniversalFixedDelayLineFilter<DataType_>::~UniversalFixedDelayLineFilter()
  {
  }
  
  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_delay(gsl::index delay)
  {
    if(delay == 0)
    {
      throw ATK::RuntimeError("Delay must be strictly positive");
    }
    if(delay >= impl->delay_line.size())
    {
      throw ATK::RuntimeError("Delay must be less than delay line size");
    }

    this->delay = delay;
  }

  template<typename DataType_>
  gsl::index UniversalFixedDelayLineFilter<DataType_>::get_delay() const
  {
    return delay;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_blend(Scalar blend)
  {
    this->blend = blend;
  }

  template<typename DataType_>
  typename UniversalFixedDelayLineFilter<DataType_>::Scalar UniversalFixedDelayLineFilter<DataType_>::get_blend() const
  {
    return blend;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_feedback(Scalar feedback)
  {
    if(std::abs(feedback) >= 1)
    {
      throw ATK::RuntimeError("Feedback must be between -1 and 1 to avoid divergence");
    }
    this->feedback = feedback;
  }

  template<typename DataType_>
  typename UniversalFixedDelayLineFilter<DataType_>::Scalar UniversalFixedDelayLineFilter<DataType_>::get_feedback() const
  {
    return feedback;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::set_feedforward(Scalar feedforward)
  {
    this->feedforward = feedforward;
  }

  template<typename DataType_>
  typename UniversalFixedDelayLineFilter<DataType_>::Scalar UniversalFixedDelayLineFilter<DataType_>::get_feedforward() const
  {
    return feedforward;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::full_setup()
  {
    // reset the delay line
    impl->delay_line.assign(impl->delay_line.size(), TypeTraits<DataType>::Zero());
    impl->index = 0;
  }

  template<typename DataType_>
  void UniversalFixedDelayLineFilter<DataType_>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    DataType* ATK_RESTRICT processed_input = outputs[1];

    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();
    auto delay_line_size = static_cast<gsl::index>(impl->delay_line.size());

    auto max_index1 = size > delay - impl->index ? size - (delay - impl->index) : 0;
    auto max_index2 = impl->index < delay ? max_index1 : std::min(size, delay);
    auto size_before_index = std::min(impl->index, max_index2);
    auto size_after_index = impl->index < delay ? std::min(size, delay - impl->index) : 0;

    // Update intermediate input
    ATK_VECTORIZE for (gsl::index i = 0; i < size_after_index; ++i)
    {
      processed_input[i] = input[i] + feedback * delay_line[delay_line_size + i - (delay - impl->index)];
    }
    ATK_VECTORIZE for (gsl::index i = 0; i < size_before_index; ++i)
    {
      processed_input[i + size_after_index] = input[i + size_after_index] + feedback * delay_line[i + size_after_index + impl->index - delay];
    }
    ATK_VECTORIZE for(gsl::index i = delay; i < size; ++i)
    {
      processed_input[i] = input[i] + feedback * processed_input[i - delay];
    }

    //update output
    ATK_VECTORIZE for (gsl::index i = 0; i < size_after_index; ++i)
    {
      output[i] = blend * processed_input[i] + feedforward * delay_line[delay_line_size + i - (delay - impl->index)];
    }
    ATK_VECTORIZE for (gsl::index i = 0; i < size_before_index; ++i)
    {
      output[i + size_after_index] = blend * processed_input[i + size_after_index] + feedforward * delay_line[i + size_after_index + impl->index - delay];
    }
    ATK_VECTORIZE for (gsl::index i = delay; i < size; ++i)
    {
      output[i] = blend * processed_input[i] + feedforward * processed_input[i - delay];
    }


    if (size > delay_line_size)
    {
      impl->index = 0;
      memcpy(reinterpret_cast<void*>(delay_line), reinterpret_cast<const void*>(processed_input + size - delay_line_size), delay_line_size * sizeof(DataType_));
    }
    else
    {
      auto new_index = std::min(impl->index + size, delay_line_size);
      auto first_size = new_index - impl->index;
      memcpy(reinterpret_cast<void*>(delay_line + impl->index), reinterpret_cast<const void*>(processed_input), first_size * sizeof(DataType_));
      auto second_size = size - first_size;

      if (impl->index + size > delay_line_size)
      {
        impl->index = second_size;
        memcpy(reinterpret_cast<void*>(delay_line), reinterpret_cast<const void*>(processed_input + first_size), second_size * sizeof(DataType_));
      }
      else
      {
        impl->index = new_index;
      }
    }
  }
}
