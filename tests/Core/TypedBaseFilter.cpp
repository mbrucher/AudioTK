/**
 * \file TypedBaseFilter.cpp
 */

#include <ATK/Core/TypedBaseFilter.h>

#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_MODULE ATKCore_TypedBaseFilter_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int16_t )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<std::int16_t> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int32_t )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<std::int32_t> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int64_t )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<std::int64_t> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_float )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<float> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_double )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<double> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_int16_t )
{
  ATK::TypedBaseFilter<std::int16_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_int32_t )
{
  ATK::TypedBaseFilter<std::int32_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_int64_t )
{
  ATK::TypedBaseFilter<std::int64_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_float )
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_double )
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_int16_t )
{
  ATK::TypedBaseFilter<std::int16_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_int32_t )
{
  ATK::TypedBaseFilter<std::int32_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_int64_t )
{
  ATK::TypedBaseFilter<std::int64_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_float )
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_double )
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

