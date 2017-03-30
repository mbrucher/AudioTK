/**
 * \file FixedDelayLineFilter.cpp
 */

#include "FixedDelayLineFilter.h"

#include <algorithm>
#include <complex>
#include <stdexcept>

namespace ATK
{
  template<typename DataType>
  class FixedDelayLineFilter<DataType>::FDLF_Impl
  {
  public:
    std::vector<DataType> delay_line;

    FDLF_Impl(std::size_t max_delay)
      :delay_line(max_delay, 0)
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
    if(delay < 0)
    {
      throw std::out_of_range("Delay must be positive");
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
  }

  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();
    auto delay_line_size = impl->delay_line.size();

    std::size_t delay_line_usage = std::min(delay, size);

    memcpy(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(delay_line + delay_line_size - delay), static_cast<std::size_t>(delay_line_usage * sizeof(DataType_)));
    if(size > delay)
    {
      memcpy(reinterpret_cast<void*>(output + delay), reinterpret_cast<const void*>(input), static_cast<std::size_t>((size - delay) * sizeof(DataType_)));
    }

    auto minimum = delay_line_size > size ? delay_line_size - size : 0;
    ATK_VECTORIZE for(std::size_t i = 0; i < minimum; ++i)
    {
      delay_line[i] = delay_line[i + size];
    }
    if (delay_line_size > minimum)
    {
      memcpy(reinterpret_cast<void*>(delay_line + minimum), reinterpret_cast<const void*>(input + size + minimum - delay_line_size), (delay_line_size - minimum) * sizeof(DataType_));
    }
  }
  
  template class FixedDelayLineFilter<float>;
  template class FixedDelayLineFilter<double>;
  template class FixedDelayLineFilter<std::complex<float>>;
  template class FixedDelayLineFilter<std::complex<double>>;
}
