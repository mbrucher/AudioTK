/**
 * \file TriangleCheckerFilter.cpp
 */

#include "TriangleCheckerFilter.h"

#include <cstdlib>

#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

namespace
{
  template<class DataType>
  typename boost::enable_if<typename boost::is_floating_point<DataType>::type>::type compare(DataType v1, DataType v2)
  {
    if(v1 * v2 == 0)
    {
      BOOST_REQUIRE_SMALL(v1, static_cast<DataType>(0.0001));
      BOOST_REQUIRE_SMALL(v2, static_cast<DataType>(0.0001));
    }
    else
    {
      BOOST_REQUIRE_CLOSE(v1, v2, 0.0001);
    }
  }

  template<class DataType>
  typename boost::disable_if<typename boost::is_floating_point<DataType>::type>::type compare(DataType v1, DataType v2)
  {
    BOOST_REQUIRE_EQUAL(v1, v2);
  }
}

namespace ATK
{
  template<class DataType_>
  TriangleCheckerFilter<DataType_>::TriangleCheckerFilter()
  :TypedBaseFilter<DataType_>(1, 0), state(0), ascending(true), amplitude(1), frequency(1)
  {
  }
  
  template<class DataType_>
  TriangleCheckerFilter<DataType_>::~TriangleCheckerFilter()
  {
  }
  
  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::set_amplitude(DataType amplitude)
  {
    this->amplitude = amplitude;
  }
  
  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }

  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::process_impl(int size)
  {
    
    double real_increment = 2. * amplitude / input_sampling_rate * frequency;
    
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
      compare(converted_inputs[0][i], static_cast<DataType>(state));
    }
  }

  template class TriangleCheckerFilter<std::int16_t>;
  template class TriangleCheckerFilter<std::int32_t>;
  template class TriangleCheckerFilter<std::int64_t>;
  template class TriangleCheckerFilter<float>;
  template class TriangleCheckerFilter<double>;
}
