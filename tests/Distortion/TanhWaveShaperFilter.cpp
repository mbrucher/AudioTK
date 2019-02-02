/**
 * \ file TanhShaperFilter.cpp
 */

#include <array>
#include <fstream>

#include <ATK/config.h>

#include <ATK/Distortion/TanhShaperFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1000;

BOOST_AUTO_TEST_CASE( TanhShaperFilter_coeff_test )
{
  ATK::TanhShaperFilter<double> shaper;
  shaper.set_coefficient(10);
  BOOST_CHECK_EQUAL(shaper.get_coefficient(), 10);
}

BOOST_AUTO_TEST_CASE( TanhShaperFilter_coeff_range_test )
{
  ATK::TanhShaperFilter<double> shaper;
  BOOST_CHECK_THROW(shaper.set_coefficient(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( TanhShaperFilter_const_sin1k )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TanhShaperFilter<double> shaper;
  shaper.set_input_sampling_rate(1024*64);
  shaper.set_output_sampling_rate(1024*64);
  
  shaper.set_input_port(0, generator, 0);
  shaper.process(PROCESSSIZE);
  
  auto sin = generator.get_output_array(0);
  auto array = shaper.get_output_array(0);
  
  for(size_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(array[i], std::tanh(sin[i]), 0.00001);
  }
}

BOOST_AUTO_TEST_CASE( TanhShaperFilter_const_2_sin1k )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TanhShaperFilter<double> shaper;
  shaper.set_input_sampling_rate(1024*64);
  shaper.set_output_sampling_rate(1024*64);
  shaper.set_coefficient(2);
  
  shaper.set_input_port(0, generator, 0);
  shaper.process(PROCESSSIZE);
  
  auto sin = generator.get_output_array(0);
  auto array = shaper.get_output_array(0);
  
  for(size_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(array[i], std::tanh(2 * sin[i]) / 2, 0.00001);
  }
}
