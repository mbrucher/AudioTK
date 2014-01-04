/**
 * \file TriangleGeneratorFilter.cpp
 */

#include "TriangleGeneratorFilter.h"

namespace ATK
{
  template<class DataType_>
  TriangleGeneratorFilter<DataType_>::TriangleGeneratorFilter()
  :TypedBaseFilter<DataType_>(0, 1), state(0), ascending(true), amplitude(1), frequency(1)
  {
  }
  
  template<class DataType_>
  TriangleGeneratorFilter<DataType_>::~TriangleGeneratorFilter()
  {
  }
  
  template<class DataType_>
  void TriangleGeneratorFilter<DataType_>::set_amplitude(DataType_ amplitude)
  {
    this->amplitude = amplitude;
  }

  template<class DataType_>
  void TriangleGeneratorFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }
  
  template<class DataType_>
  void TriangleGeneratorFilter<DataType_>::process_impl(int size)
  {
    if(outputs_size[0] < size)
    {
      outputs[0].reset(new DataType[size]);
      outputs_size[0] = size;
    }
    
    double real_increment = 2. * amplitude / output_sampling_rate * frequency;
    
    for(int i = 0; i < size; ++i)
    {
      state += real_increment * (ascending ? 1 : -1);
      if(state >= amplitude)
      {
        state -= 2 * real_increment;
        ascending = !ascending;
      }
      else if(state <= -amplitude)
      {
        state += 2 * real_increment;
        ascending = !ascending;
      }
      outputs[0][i] = state;
    }
  }
  
  template class TriangleGeneratorFilter<std::int16_t>;
  template class TriangleGeneratorFilter<std::int32_t>;
  template class TriangleGeneratorFilter<std::int64_t>;
  template class TriangleGeneratorFilter<float>;
  template class TriangleGeneratorFilter<double>;
}
