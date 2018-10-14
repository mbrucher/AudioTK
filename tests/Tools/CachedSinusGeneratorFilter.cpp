/**
 * \ file CachedSinusGeneratorFilter.cpp
 */

#include <ATK/config.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/CachedSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;

BOOST_AUTO_TEST_CASE( CachedSinusGeneratorFilter_volume_test )
{
  ATK::CachedSinusGeneratorFilter<double> filter(10000, 10);
  filter.set_volume(10);
  BOOST_CHECK_EQUAL(filter.get_volume(), 10);
}

BOOST_AUTO_TEST_CASE( CachedSinusGeneratorFilter_offset_test )
{
  ATK::CachedSinusGeneratorFilter<double> filter(10000, 10);
  filter.set_offset(10);
  BOOST_CHECK_EQUAL(filter.get_offset(), 10);
}

BOOST_AUTO_TEST_CASE( CachedSinusGeneratorFilter_frequency_test )
{
  ATK::CachedSinusGeneratorFilter<double> filter(10000, 10);
  filter.set_frequency(1000, 1);
  BOOST_CHECK_EQUAL(filter.get_frequency().first, 1000);
  BOOST_CHECK_EQUAL(filter.get_frequency().second, 1);
}

BOOST_AUTO_TEST_CASE( CachedSinusGeneratorFilter_frequency_range_test )
{
  ATK::CachedSinusGeneratorFilter<double> filter(10000, 10);
  BOOST_CHECK_THROW(filter.set_frequency(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( CachedSinusGeneratorFilter_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(-1);
  generator.set_frequency(1000);
  
  ATK::CachedSinusGeneratorFilter<double> filter(10000, 10);
  filter.set_output_sampling_rate(48000);
  
  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &filter, 0);
  
  checker.set_input_port(0, &sumfilter, 0);
  
  checker.process(PROCESSSIZE);
}
