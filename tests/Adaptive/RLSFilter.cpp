/**
 * \ file RLSFilter.cpp
 */

#include <ATK/Adaptive/RLSFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( RLSFilter_memory_negative_test )
{
  ATK::RLSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( RLSFilter_memory_positive1_test )
{
  ATK::RLSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(1), std::out_of_range);
}
