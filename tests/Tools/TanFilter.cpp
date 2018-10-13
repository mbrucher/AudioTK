/**
 * \ file TanFilter.cpp
 */

#include <array>
#include <fstream>

#include <ATK/config.h>

#include <ATK/Tools/TanFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <boost/math/constants/constants.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1000;
constexpr gsl::index SAMPLING_RATE = 1024*64;

BOOST_AUTO_TEST_CASE( TanFilter_const_sin1k )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLING_RATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TanFilter<double> filter;
  filter.set_input_sampling_rate(SAMPLING_RATE);
  filter.set_output_sampling_rate(SAMPLING_RATE);
  
  filter.set_input_port(0, generator, 0);
  filter.process(PROCESSSIZE);
  
  auto sin = generator.get_output_array(0);
  auto array = filter.get_output_array(0);
  
  for(size_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(array[i], std::tan(sin[i] * boost::math::constants::pi<double>() / SAMPLING_RATE), 0.00001);
  }
}
