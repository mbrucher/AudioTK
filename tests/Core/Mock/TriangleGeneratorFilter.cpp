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
  }
}
