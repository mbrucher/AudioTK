/**
 * \file TriangleCheckerFilter.cpp
 */

#include "TriangleCheckerFilter.h"

#include <cstdlib>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

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
    for(int i = 0; i < (size - 1); ++i)
    {
      BOOST_CHECK_EQUAL(std::abs(converted_inputs[0][i] - converted_inputs[0][i + 1]), 100);
    }
  }
}
