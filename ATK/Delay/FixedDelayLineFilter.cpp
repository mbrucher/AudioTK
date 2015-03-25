/**
 * \file FixedDelayLineFilter.cpp
 */

#include "FixedDelayLineFilter.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  FixedDelayLineFilter<DataType_>::FixedDelayLineFilter(int max_delay)
  :Parent(1, 1), delay_line(max_delay, 0), delay(0)
  {
  }
  
  template<typename DataType_>
  FixedDelayLineFilter<DataType_>::~FixedDelayLineFilter()
  {
    
  }
  
  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::set_delay(std::int64_t delay)
  {
    if(delay < 0)
    {
      throw std::out_of_range("Delay must be positive");
    }
    if(delay >= static_cast<std::int64_t>(delay_line.size()))
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    this->delay = delay;
  }

  template<typename DataType_>
  std::int64_t FixedDelayLineFilter<DataType_>::get_delay() const
  {
    return delay;
  }

  template<typename DataType_>
  void FixedDelayLineFilter<DataType_>::process_impl(std::int64_t size)
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];

    std::int64_t delay_line_usage = std::min(delay, size);

    memcpy(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(delay_line.data() + delay_line.size() - delay), delay_line_usage * sizeof(DataType_));
    if(size - delay > 0)
    {
      memcpy(reinterpret_cast<void*>(output + delay), reinterpret_cast<const void*>(input), (size - delay) * sizeof(DataType_));
    }

    for(std::int64_t i = 0; i < std::int64_t(delay_line.size()) - size; ++i)
    {
      delay_line[i] = delay_line[i + size];
    }
    std::int64_t minimum = std::max(std::int64_t(0), std::int64_t(delay_line.size()) - size);
    if(static_cast<std::int64_t>(delay_line.size()) > minimum)
    {
      memcpy(reinterpret_cast<void*>(delay_line.data() + minimum), reinterpret_cast<const void*>(input + size + minimum - delay_line.size()), (delay_line.size() - minimum) * sizeof(DataType_));
    }
  }
  
  template class FixedDelayLineFilter<float>;
  template class FixedDelayLineFilter<double>;
}
