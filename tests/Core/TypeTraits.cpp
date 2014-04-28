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
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int64_t>::to_double(std::numeric_limits<std::int64_t>::min()), -1);
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
  BOOST_CHECK_EQUAL(ATK::TypeTraits<std::int64_t>::from_double(-1), std::numeric_limits<std::int64_t>::min());
}
