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
  :TypedBaseFilter<std::int64_t>(1, 0), state(0), ascending(true), amplitude(1), frequency(1)
  {
  }
  
  TriangleCheckerFilter::~TriangleCheckerFilter()
  {
  }
  
  void TriangleCheckerFilter::set_amplitude(std::int64_t amplitude)
  {
    this->amplitude = amplitude;
  }
  
  void TriangleCheckerFilter::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }

  void TriangleCheckerFilter::process_impl(int size)
  {
    
    float real_increment = 2. * amplitude / input_sampling_rate * frequency;
    
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
      BOOST_CHECK_EQUAL(converted_inputs[0][i], static_cast<std::int64_t>(state));
    }
  }
}
