/**
 * \file TypedBaseFilter.cpp
 */

#include <ATK/Core/TypedBaseFilter.h>

#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_MODULE ATKCore_TypedBaseFilter_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int16_t )
{
  ATK::TypedBaseFilter<std::int16_t> filter(0, 0);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int32_t )
{
  ATK::TypedBaseFilter<std::int32_t> filter(0, 0);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int64_t )
{
  ATK::TypedBaseFilter<std::int64_t> filter(0, 0);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_float )
{
  ATK::TypedBaseFilter<float> filter(0, 0);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_double )
{
  ATK::TypedBaseFilter<double> filter(0, 0);
}

