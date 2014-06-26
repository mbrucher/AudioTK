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
    if(delay >= delay_line.size())
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

    for(std::int64_t i = 0; i < delay_line_usage; ++i)
    {
      output[i] = delay_line[delay_line.size() - 1 - i];
    }
    for(std::int64_t i = delay; i < size; ++i)
    {
      output[i] = input[i - delay];
    }

    for(std::int64_t i = 0; i < std::int64_t(delay_line.size()) - size; ++i)
    {
      delay_line[i] = delay_line[i + size];
    }
    std::int64_t minimum = std::max(std::int64_t(0), std::int64_t(delay_line.size()) - size);
    for(std::int64_t i = minimum; i < delay_line.size(); ++i)
    {
      delay_line[i] = input[i - minimum];
    }
  }
  
  template class FixedDelayLineFilter<float>;
  template class FixedDelayLineFilter<double>;
}
