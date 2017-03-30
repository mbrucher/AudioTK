/**
 * \file TriangleCheckerFilter.cpp
 */

#include "TriangleCheckerFilter.h"

#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <ATK/Core/TypeTraits.h>

namespace
{
  template<class DataType>
  std::enable_if_t<!std::is_integral_v<DataType>> compare(DataType v1, DataType v2)
  {
    if(std::abs(v1) < 1e-5 || std::abs(v2) < 1e-5)
    {
      auto absv1 = std::abs(static_cast<typename ATK::TypeTraits<DataType>::Scalar>(v1));
      auto absv2 = std::abs(static_cast<typename ATK::TypeTraits<DataType>::Scalar>(v2));
      BOOST_REQUIRE_SMALL(absv1, 1e-5);
      BOOST_REQUIRE_SMALL(absv2, 1e-5);
    }
    else
    {
      auto diff = std::abs(static_cast<typename ATK::TypeTraits<DataType>::Scalar>((v1 - v2) / (v1 + v2)));
      BOOST_REQUIRE_SMALL(diff, 1e-5);
    }
  }

  template<class DataType>
  std::enable_if_t<std::is_integral_v<DataType>> compare(DataType v1, DataType v2)
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
  void TriangleCheckerFilter<DataType_>::set_amplitude(DataType_ amplitude)
  {
    this->amplitude = amplitude;
  }
  
  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }

  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::process_impl(std::size_t size) const
  {
    double real_increment = 2. / input_sampling_rate * frequency;
    
    for(std::size_t i = 0; i < size; ++i)
    {
      state += real_increment * (ascending ? 1 : -1);
      if(state >= 1)
      {
        state -= 2 * real_increment;
        ascending = !ascending;
      }
      else if(state <= -1)
      {
        state += 2 * real_increment;
        ascending = !ascending;
      }
      compare(converted_inputs[0][i], static_cast<DataType>(static_cast<typename TypeTraits<DataType>::Scalar>(amplitude) * state));
    }
  }

  template class TriangleCheckerFilter<std::int16_t>;
  template class TriangleCheckerFilter<std::int32_t>;
  template class TriangleCheckerFilter<std::int64_t>;
  template class TriangleCheckerFilter<float>;
  template class TriangleCheckerFilter<double>;
  template class TriangleCheckerFilter<std::complex<float>>;
  template class TriangleCheckerFilter<std::complex<double>>;
}
