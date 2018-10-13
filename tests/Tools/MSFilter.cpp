/**
 * \ file SumFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/MSFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024;

BOOST_AUTO_TEST_CASE( MSFilter_middle_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::MiddleSideFilter<double> middlesidefilter;
  middlesidefilter.set_input_sampling_rate(48000);
  middlesidefilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(3);
  checker.set_frequency(1000);
  
  middlesidefilter.set_input_port(0, &generator, 0);
  middlesidefilter.set_input_port(1, &generator2, 0);
  checker.set_input_port(0, &middlesidefilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MSFilter_side_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::MiddleSideFilter<double> middlesidefilter;
  middlesidefilter.set_input_sampling_rate(48000);
  middlesidefilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(-1);
  checker.set_frequency(1000);
  
  middlesidefilter.set_input_port(0, &generator, 0);
  middlesidefilter.set_input_port(1, &generator2, 0);
  checker.set_input_port(0, &middlesidefilter, 1);
  checker.process(PROCESSSIZE);
}
