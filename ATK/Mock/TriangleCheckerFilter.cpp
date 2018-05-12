/**
 * \file TriangleCheckerFilter.cpp
 */

#include <ATK/Mock/TriangleCheckerFilter.h>

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
  typename std::enable_if<!std::is_integral<DataType>::value>::type compare(DataType v1, DataType v2)
  {
    if(std::abs(v1) < 1e-5 || std::abs(v2) < 1e-5)
    {
      auto absv1 = std::abs(v1);
      auto absv2 = std::abs(v2);
      BOOST_REQUIRE_SMALL(absv1, typename ATK::TypeTraits<DataType>::Scalar(1e-5));
      BOOST_REQUIRE_SMALL(absv2, typename ATK::TypeTraits<DataType>::Scalar(1e-5));
    }
    else
    {
      auto diff = std::abs((v1 - v2) / (v1 + v2));
      BOOST_REQUIRE_SMALL(diff, typename ATK::TypeTraits<DataType>::Scalar(1e-5));
    }
  }

  template<class DataType>
  typename std::enable_if<std::is_integral<DataType>::value>::type compare(DataType v1, DataType v2)
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
    
    for(gsl::index i = 0; i < size; ++i)
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
      compare(converted_inputs[0][i], TypeTraits<DataType>::from_double(TypeTraits<DataType>::to_double(amplitude) * state));
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
