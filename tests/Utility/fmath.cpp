/**
 * \ file fmath.cpp
 */

#include <cmath>

#include <ATK/Utility/fmath.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(fmath_exp_float_test)
{
  for (int i = 0; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::exp(float(i)), fmath::exp(float(i)), 0.0001);
  }
}

BOOST_AUTO_TEST_CASE(fmath_exp_double_test)
{
  for (int i = 0; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::exp(double(i)), fmath::exp(double(i)), 0.0001);
  }
}

BOOST_AUTO_TEST_CASE(fmath_log_float_test)
{
  for (int i = 1; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::log(float(i)), fmath::log(float(i)), 0.0001);
  }
}

BOOST_AUTO_TEST_CASE(fmath_log_double_test)
{
  for (int i = 1; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::log(double(i)), fmath::log(double(i)), 0.0001);
  }
}

BOOST_AUTO_TEST_CASE(fmath_log10_float_test)
{
  for (int i = 1; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::log10(float(i)), fmath::log10(float(i)), 0.0001);
  }
}

BOOST_AUTO_TEST_CASE(fmath_log10_double_test)
{
  for (int i = 1; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::log10(double(i)), fmath::log10(double(i)), 0.0001);
  }
}

BOOST_AUTO_TEST_CASE(fmath_pow_float_test)
{
  for (int i = 1; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::pow(10, float(i)), fmath::pow(10, float(i)), 0.001);
  }
}

BOOST_AUTO_TEST_CASE(fmath_pow_double_test)
{
  for (int i = 1; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(std::pow(10, double(i)), fmath::pow(10, double(i)), 0.0001);
  }
}