/**
 * \file TypeTraits.cpp
 */

#include <ATK/Core/TypeTraits.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TypeTraits_test_to_double_int16_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int16_t>::to_double(std::numeric_limits<std::int16_t>::min()), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_to_double_int32_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int32_t>::to_double(std::numeric_limits<std::int32_t>::min()), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_to_double_int64_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<int64_t>::to_double(std::numeric_limits<int64_t>::min()), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_from_double_int16_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int16_t>::from_double(-1), std::numeric_limits<std::int16_t>::min());
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_from_double_int32_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int32_t>::from_double(-1), std::numeric_limits<std::int32_t>::min());
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_from_double_int64_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<int64_t>::from_double(-1), std::numeric_limits<int64_t>::min());
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_conj_int16_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int16_t>::conj(-1), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_conj_int32_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int32_t>::conj(-1), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_conj_int64_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<int64_t>::conj(-1), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_conj_float )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<float>::conj(-1), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_conj_double )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<double>::conj(-1), -1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_zero_int16_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int16_t>::Zero(), 0);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_zero_int32_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int32_t>::Zero(), 0);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_zero_int64_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<int64_t>::Zero(), 0);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_zero_float )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<float>::Zero(), 0);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_zero_double )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<double>::Zero(), 0);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_one_int16_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int16_t>::One(), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_one_int32_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int32_t>::One(), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_one_int64_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<int64_t>::One(), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_one_float )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<float>::One(), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_one_double )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<double>::One(), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_max_int16_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int16_t>::max(0, 1), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_max_int32_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int32_t>::max(0, 1), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_max_int64_t )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<int64_t>::max(0, 1), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_max_float )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<float>::max(0, 1), 1);
}

BOOST_AUTO_TEST_CASE( TypeTraits_test_max_double )
{
  BOOST_CHECK_EQUAL(ATK::TypeTraits<double>::max(0, 1), 1);
}
