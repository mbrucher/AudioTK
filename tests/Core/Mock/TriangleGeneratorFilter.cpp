/**
 * \file TriangleGeneratorFilter.cpp
 */

#include "TriangleGeneratorFilter.h"

namespace ATK
{
  TriangleGeneratorFilter::TriangleGeneratorFilter()
  :TypedBaseFilter<std::int64_t>(0, 1), state(0), ascending(true), amplitude(1), frequency(1)
  {
  }
  
  TriangleGeneratorFilter::~TriangleGeneratorFilter()
  {
  }
  
  void TriangleGeneratorFilter::set_amplitude(std::int64_t amplitude)
  {
    this->amplitude = amplitude;
  }

  void TriangleGeneratorFilter::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }
  
  void TriangleGeneratorFilter::process_impl(int size)
  {
    if(outputs_size[0] < size)
    {
      outputs[0].reset(new DataType[size]);
      outputs_size[0] = size;
    }
    
    float real_increment = 2. * amplitude / output_sampling_rate * frequency;
    
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
}
