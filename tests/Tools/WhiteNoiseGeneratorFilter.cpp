/**
 * \ file WhiteNoiseGeneratorFilter.cpp
 */

#include <iostream>

#include <ATK/Tools/WhiteNoiseGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024*1024*4;

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
  noisefilter.set_input_sampling_rate(PROCESSSIZE);
  noisefilter.set_output_sampling_rate(PROCESSSIZE);
  noisefilter.process(PROCESSSIZE);

  auto noise = noisefilter.get_output_array(0);
  auto mean = std::accumulate(noise, noise + PROCESSSIZE, 0.) / PROCESSSIZE;
  BOOST_CHECK_SMALL(mean, 0.001);
}

BOOST_AUTO_TEST_CASE( WhiteNoiseGeneratorFilter_std_test )
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_input_sampling_rate(PROCESSSIZE);
  noisefilter.set_output_sampling_rate(PROCESSSIZE);
  noisefilter.process(PROCESSSIZE);
  
  auto noise = noisefilter.get_output_array(0);
  auto std = (std::accumulate(noise, noise + PROCESSSIZE, 0., [](double a, double b) {return a + b*b;}) / PROCESSSIZE);
  BOOST_CHECK_CLOSE(std, 1./3, 0.05);
}
