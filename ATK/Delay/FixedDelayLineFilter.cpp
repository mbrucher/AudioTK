/**
 * \file FixedDelayLineFilter.cpp
 */

#include "FixedDelayLineFilter.h"

#include <algorithm>
#include <cstring>
#include <complex>
#include <stdexcept>
#include <iostream>

namespace ATK
{
  template<typename DataType>
  class FixedDelayLineFilter<DataType>::FDLF_Impl
  {
  public:
    std::vector<DataType> delay_line;
    std::size_t index;

    FDLF_Impl(std::size_t max_delay)
      :delay_line(max_delay, 0), index(0)
    {
    }
  };

  template<typename DataType_>
  FixedDelayLineFilter<DataType_>::FixedDelayLineFilter(std::size_t max_delay)
    :Parent(1, 1), impl(new FDLF_Impl(max_delay)), delay(0)
  {
  }
  
  template<typename DataType_>
  FixedDelayLineFilter<DataType_>::~FixedDelayLineFilter()
  {
    
  }
  
  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::set_delay(std::size_t delay)
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
  std::size_t FixedDelayLineFilter<DataType_>::get_delay() const
  {
    return delay;
  }

  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::full_setup()
  {
    // reset the delay line
    impl->delay_line.assign(impl->delay_line.size(), 0);
    impl->index = 0;
  }

  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();
    auto delay_line_size = impl->delay_line.size();

    auto size_before_index = impl->index < delay ? std::max(int64_t(0), static_cast<int64_t>(delay) - static_cast<int64_t>(delay_line_size - impl->index)) : std::min(size, delay + size - impl->index);
    auto size_after_index = impl->index < delay ? std::min(delay - impl->index, impl->index) : 0;

    std::cout << "size" << size << std::endl;
    std::cout << "index" << impl->index << std::endl;
    std::cout << "after index" << size_after_index << std::endl;
    std::cout << "before index" << size_before_index << std::endl;
    
    for(std::size_t i = impl->index; i < delay_line_size; ++i)
    {
      std::cout << delay_line[i] << "\t";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for(std::size_t i = 0; i < impl->index; ++i)
    {
      std::cout << delay_line[i] << "\t";
    }
    std::cout << std::endl;

    memcpy(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(delay_line + delay_line_size - size_after_index), static_cast<std::size_t>(size_after_index * sizeof(DataType_)));
/*    if(size_after_index > 0)
    {
      std::cout << "first output" << output[0] << std::endl;
      std::cout << "index of first" << impl->index << std::endl;
      std::cout << "index of first" << (delay_line_size - size_after_index) << std::endl;
      std::cout << "index of before" << (impl->index - size_before_index) << std::endl;
      std::cout << "address of delay" << delay_line << std::endl;
      std::cout << "address of first index" << delay_line[impl->index] << std::endl;
      std::cout << "address of first index ops " << delay_line[delay_line_size - size_after_index] << std::endl;
    }*/
    memcpy(reinterpret_cast<void*>(output + size_after_index), reinterpret_cast<const void*>(delay_line), static_cast<std::size_t>(size_before_index * sizeof(DataType_)));
/*    if(size_before_index > 0)
    {
      std::cout << "second output" << output[size_after_index] << std::endl;
    }*/

    if(size > delay)
    {
      memcpy(reinterpret_cast<void*>(output + delay), reinterpret_cast<const void*>(input), static_cast<std::size_t>((size - delay) * sizeof(DataType_)));
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
  
  template class FixedDelayLineFilter<float>;
  template class FixedDelayLineFilter<double>;
  template class FixedDelayLineFilter<std::complex<float>>;
  template class FixedDelayLineFilter<std::complex<double>>;
}
