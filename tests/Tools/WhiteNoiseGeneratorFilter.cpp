/**
 * \ file WhiteNoiseGeneratorFilter.cpp
 */

#include <cmath>

#include <ATK/Core/InPointerFilter.h>

#include <ATK/Tools/WhiteNoiseGeneratorFilter.h>

#include <array>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const size_t PROCESSSIZE = 1024;

BOOST_AUTO_TEST_CASE( WhiteNoiseGeneratorFilter_volume_test )
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_volume(10);
  BOOST_CHECK_EQUAL(noisefilter.get_volume(), 10);
}

BOOST_AUTO_TEST_CASE( WhiteNoiseGeneratorFilter_offset_test )
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_offset(10);
  BOOST_CHECK_EQUAL(noisefilter.get_offset(), 10);
}
