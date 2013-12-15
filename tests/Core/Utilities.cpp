/**
 * \file Utilities.cpp
 */

#include <ATK/Core/Utilities.h>

#include <vector>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int16_t_int16_t )
{
  std::vector<std::int16_t> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, std::int16_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(input[0], output[0]);
  BOOST_CHECK_EQUAL(input[1], output[1]);
  BOOST_CHECK_EQUAL(input[2], output[2]);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int32_t_int32_t )
{
  std::vector<std::int32_t> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, std::int32_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(input[0], output[0]);
  BOOST_CHECK_EQUAL(input[1], output[1]);
  BOOST_CHECK_EQUAL(input[2], output[2]);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int64_t_int64_t )
{
  std::vector<std::int64_t> input(3);
  std::vector<std::int64_t> output(3);
  input[0] = std::numeric_limits<std::int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int64_t>::max();
  
  ATK::ConversionUtilities<std::int64_t, std::int64_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(input[0], output[0]);
  BOOST_CHECK_EQUAL(input[1], output[1]);
  BOOST_CHECK_EQUAL(input[2], output[2]);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_float_float )
{
  std::vector<float> input(3);
  std::vector<float> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<float, float>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(input[0], output[0]);
  BOOST_CHECK_EQUAL(input[1], output[1]);
  BOOST_CHECK_EQUAL(input[2], output[2]);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_double_double )
{
  std::vector<double> input(3);
  std::vector<double> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<double, double>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(input[0], output[0]);
  BOOST_CHECK_EQUAL(input[1], output[1]);
  BOOST_CHECK_EQUAL(input[2], output[2]);
}
