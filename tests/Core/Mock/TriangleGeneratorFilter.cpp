/**
 * \file TriangleGeneratorFilter.cpp
 */

#include "TriangleGeneratorFilter.h"

namespace ATK
{
  TriangleGeneratorFilter::TriangleGeneratorFilter()
  :TypedBaseFilter<std::int64_t>(0, 1), state(0), ascending(true)
  {
  }
  
  TriangleGeneratorFilter::~TriangleGeneratorFilter()
  {
  }
  
  void TriangleGeneratorFilter::process_impl(int size)
  {
    if(outputs_size[0] < size)
    {
      outputs[0].reset(new DataType[size]);
      outputs_size[0] = size;
    }
    
    int i = 0;
    for(i = 0; i < std::min(size, output_sampling_rate - state); ++i)
    {
      outputs[0][i] = 100 * (state + i) * (ascending ? 1 : -1);
    }
    if(i == output_sampling_rate - state)
    {
      ascending = !ascending;
      state = (ascending ? 1 : -1) * -output_sampling_rate;
    }
    int j = 0;
    for(;i < size; ++i, ++j)
    {
      outputs[0][i] = 100 * (state + j) * (ascending ? 1 : -1);
    }
  }
}
