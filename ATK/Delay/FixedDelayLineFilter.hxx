/**
 * \file FixedDelayLineFilter.hxx
 */

#include "FixedDelayLineFilter.h"
#include <ATK/Core/Utilities.h>

#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType>
  class FixedDelayLineFilter<DataType>::FDLF_Impl
  {
  public:
    typename FixedDelayLineFilter<DataType>::AlignedOutVector delay_line;
    gsl::index index{0};

    explicit FDLF_Impl(gsl::index max_delay)
      :delay_line(max_delay, TypeTraits<DataType>::Zero())
    {
    }
  };

  template<typename DataType_>
  FixedDelayLineFilter<DataType_>::FixedDelayLineFilter(gsl::index max_delay)
    :Parent(1, 1), impl(std::make_unique<FDLF_Impl>(max_delay))
  {
  }
  
  template<typename DataType_>
  FixedDelayLineFilter<DataType_>::~FixedDelayLineFilter()
  {
    
  }
  
  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::set_delay(gsl::index delay)
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
  gsl::index FixedDelayLineFilter<DataType_>::get_delay() const
  {
    return delay;
  }

  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::full_setup()
  {
    // reset the delay line
    impl->delay_line.assign(impl->delay_line.size(), TypeTraits<DataType>::Zero());
    impl->index = 0;
  }

  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();
    auto delay_line_size = static_cast<gsl::index>(impl->delay_line.size());

    auto max_index1 = size > delay - impl->index ? size - (delay - impl->index) : 0;
    auto max_index2 = impl->index < delay ? max_index1 : std::min(size, delay);
    auto size_before_index = std::min(impl->index, max_index2);
    auto size_after_index = impl->index < delay ? std::min(size, delay - impl->index) : 0;

    memcpy(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(delay_line + delay_line_size - (delay - impl->index)), static_cast<gsl::index>(size_after_index * sizeof(DataType_)));
    memcpy(reinterpret_cast<void*>(output + size_after_index), reinterpret_cast<const void*>(delay_line + size_after_index + impl->index - delay), static_cast<gsl::index>(size_before_index * sizeof(DataType_)));

    if(size > delay)
    {
      memcpy(reinterpret_cast<void*>(output + delay), reinterpret_cast<const void*>(input), static_cast<gsl::index>((size - delay) * sizeof(DataType_)));
    }

    if(size > delay_line_size)
    {
      impl->index = 0;
      memcpy(reinterpret_cast<void*>(delay_line), reinterpret_cast<const void*>(input + size - delay_line_size), delay_line_size * sizeof(DataType_));
    }
    else
    {
      auto new_index = std::min(impl->index + size, delay_line_size);
      auto first_size = new_index - impl->index;
      memcpy(reinterpret_cast<void*>(delay_line + impl->index), reinterpret_cast<const void*>(input), first_size * sizeof(DataType_));
      auto second_size = size - first_size;
      
      if(impl->index + size > delay_line_size)
      {
        impl->index = second_size;
        memcpy(reinterpret_cast<void*>(delay_line), reinterpret_cast<const void*>(input + first_size), second_size * sizeof(DataType_));
      }
      else
      {
        impl->index = new_index;
      }
    }
  }
}
