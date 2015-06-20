/**
 * \file VariableDelayLineFilter.cpp
 */

#include "VariableDelayLineFilter.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType>
  class VDLF_Impl
  {
  public:
    /// Delay line contains the last size elements + max_delay of the last delay line
    std::vector<DataType> delay_line;

    /// Integer portion of the delay for the last processed chunk
    std::vector<int64_t> integer_delay;
    /// Fractional portion of the delay for the last processed chunk, used for the interpolation
    std::vector<DataType> fractional_delay;

    VDLF_Impl(int max_delay)
      :delay_line(max_delay, 0)
    {
    }

    void update_delay_line(int64_t max_delay, int64_t size)
    {
      // Update delay line
      for (int64_t i = 0; i < max_delay; ++i)
      {
        delay_line[i] = delay_line[delay_line.size() + i - max_delay];
      }
      delay_line.resize(size + max_delay);

      integer_delay.resize(size);
      fractional_delay.resize(size);
    }
  };


  template<typename DataType_>
  VariableDelayLineFilter<DataType_>::VariableDelayLineFilter(int max_delay)
    :Parent(2, 1), impl(new VDLF_Impl<DataType_>(max_delay)), max_delay(max_delay)
  {
  }
  
  template<typename DataType_>
  VariableDelayLineFilter<DataType_>::~VariableDelayLineFilter()
  {
    
  }

  template<typename DataType_>
  void VariableDelayLineFilter<DataType_>::full_setup()
  {
    // reset the delay line
    impl->delay_line.assign(max_delay, 0);
  }

  template<typename DataType_>
  void VariableDelayLineFilter<DataType_>::process_impl(int64_t size) const
  {
    impl->update_delay_line(max_delay, size);

    const DataType* ATK_RESTRICT input1 = converted_inputs[0]; // samples
    const DataType* ATK_RESTRICT input2 = converted_inputs[1]; // delay
    DataType* ATK_RESTRICT output = outputs[0];

    int64_t* ATK_RESTRICT integer_delay = impl->integer_delay.data();
    DataType* ATK_RESTRICT fractional_delay = impl->fractional_delay.data();
    DataType* ATK_RESTRICT delay_line = impl->delay_line.data();

    memcpy(reinterpret_cast<void*>(delay_line + max_delay), reinterpret_cast<const void*>(input1), size * sizeof(DataType));

    for(int64_t i = 0; i < size; ++i)
    {
      integer_delay[i] = static_cast<int64_t>(input2[i]);
      fractional_delay[i] = input2[i] - integer_delay[i];
    }

    for(int64_t i = 0; i < size; ++i)
    {
      output[i] = delay_line[i + max_delay - integer_delay[i]] * (1 - fractional_delay[i]) + delay_line[i + max_delay - integer_delay[i] - 1] * fractional_delay[i];
    }
  }
  
  template class VariableDelayLineFilter<float>;
  template class VariableDelayLineFilter<double>;
}
