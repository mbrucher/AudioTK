/**
 * \file TriangleCheckerFilter.cpp
 */

#include "TriangleCheckerFilter.h"

namespace ATK
{
  TriangleCheckerFilter::TriangleCheckerFilter()
  :TypedBaseFilter<std::int64_t>(1, 0), state(0), ascending(true)
  {
  }
  
  TriangleCheckerFilter::~TriangleCheckerFilter()
  {
  }
  
  void TriangleCheckerFilter::process_impl(int size)
  {
  }
}
