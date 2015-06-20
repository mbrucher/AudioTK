/**
 * \file Utilities.cpp
 */

#include <ATK/Core/Utilities.h>

#include <cstdint>
#include <vector>

#define BOOST_TEST_DYN_LINK
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

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int16_t_int32_t )
{
  std::vector<std::int16_t> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, std::int32_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int32_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<std::int32_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int16_t_int64_t )
{
  std::vector<std::int16_t> input(3);
  std::vector<int64_t> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, int64_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<int64_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<int64_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int16_t_float )
{
  std::vector<std::int16_t> input(3);
  std::vector<float> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, float>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_CLOSE(-1, output[0], 0.01);
  BOOST_CHECK_CLOSE(0, output[1], 0.01);
  BOOST_CHECK_CLOSE(1, output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int16_t_double )
{
  std::vector<std::int16_t> input(3);
  std::vector<double> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, double>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_CLOSE(-1, output[0], 0.01);
  BOOST_CHECK_CLOSE(0, output[1], 0.01);
  BOOST_CHECK_CLOSE(1, output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int32_t_int16_t )
{
  std::vector<std::int32_t> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, std::int16_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int16_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int16_t>::max(), output[2]);
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

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int32_t_int64_t )
{
  std::vector<std::int32_t> input(3);
  std::vector<int64_t> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, int64_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<int64_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<int64_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int32_t_float )
{
  std::vector<std::int32_t> input(3);
  std::vector<float> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, float>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(-1, output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(1, output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int32_t_double )
{
  std::vector<std::int32_t> input(3);
  std::vector<double> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, double>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(-1, output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(1, output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int64_t_int16_t )
{
  std::vector<int64_t> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max() - (static_cast<int64_t>(1) << 48);
  
  ATK::ConversionUtilities<int64_t, std::int16_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int16_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<std::int16_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int64_t_int32_t )
{
  std::vector<int64_t> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max() - (1L << 16);
  
  ATK::ConversionUtilities<int64_t, std::int32_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int32_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<std::int32_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int64_t_int64_t )
{
  std::vector<int64_t> input(3);
  std::vector<int64_t> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max();
  
  ATK::ConversionUtilities<int64_t, int64_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(input[0], output[0]);
  BOOST_CHECK_EQUAL(input[1], output[1]);
  BOOST_CHECK_EQUAL(input[2], output[2]);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int64_t_float )
{
  std::vector<int64_t> input(3);
  std::vector<float> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max();
  
  ATK::ConversionUtilities<int64_t, float>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(-1, output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(1, output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_int64_t_double )
{
  std::vector<int64_t> input(3);
  std::vector<double> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max();
  
  ATK::ConversionUtilities<int64_t, double>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(-1, output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(1, output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_float_int16_t )
{
  std::vector<float> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999;
  
  ATK::ConversionUtilities<float, std::int16_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int16_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<std::int16_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_float_int32_t )
{
  std::vector<float> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .999999;
  
  ATK::ConversionUtilities<float, std::int32_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int32_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<std::int32_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_float_int64_t )
{
  std::vector<float> input(3);
  std::vector<int64_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999999;
  
  ATK::ConversionUtilities<float, int64_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<int64_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<int64_t>::max()), output[2], 0.01);
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

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_float_double )
{
  std::vector<float> input(3);
  std::vector<double> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<float, double>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(input[0], output[0]);
  BOOST_CHECK_EQUAL(input[1], output[1]);
  BOOST_CHECK_EQUAL(input[2], output[2]);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_double_int16_t )
{
  std::vector<double> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999;
  
  ATK::ConversionUtilities<double, std::int16_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int16_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<std::int16_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_double_int32_t )
{
  std::vector<double> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .999999;
  
  ATK::ConversionUtilities<double, std::int32_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<std::int32_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<std::int32_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_double_int64_t )
{
  std::vector<double> input(3);
  std::vector<int64_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999999;
  
  ATK::ConversionUtilities<double, int64_t>::convert_array(&input[0], &output[0], 3);
  
  BOOST_CHECK_EQUAL(std::numeric_limits<int64_t>::min(), output[0]);
  BOOST_CHECK_EQUAL(0, output[1]);
  BOOST_CHECK_CLOSE(static_cast<double>(std::numeric_limits<int64_t>::max()), output[2], 0.01);
}

BOOST_AUTO_TEST_CASE( Utilities_test_convert_array_double_float )
{
  std::vector<double> input(3);
  std::vector<float> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<double, float>::convert_array(&input[0], &output[0], 3);
  
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
