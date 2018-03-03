/**
 * \ file WhiteNoiseGeneratorFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/WhiteNoiseGeneratorFilter.h>

#include <array>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const size_t PROCESSSIZE = 1024*1024;

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

BOOST_AUTO_TEST_CASE( WhiteNoiseGeneratorFilter_mean_test )
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_output_sampling_rate(PROCESSSIZE);
  noisefilter.process(PROCESSSIZE);
  
  auto noise = noisefilter.get_output_array(0);
  BOOST_CHECK_CLOSE(std::accumulate(noise, noise + PROCESSSIZE, 0.) / PROCESSSIZE, 0, 0.0001);
}
