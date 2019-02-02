/**
 * \ file BufferFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/BufferFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024;

BOOST_AUTO_TEST_CASE( BufferFilter_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::BufferFilter<double> bufferfilter;
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &bufferfilter, 0);
  checker.process(PROCESSSIZE);
}
