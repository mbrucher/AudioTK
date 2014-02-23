/**
 * \ file InWavFilter.cpp
 */

#include <ATK/IO/InWavFilter.h>

#include <ATK/config.h>

#include <ATK/Mock/SinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( InWavFilter_In_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(-1);
  generator.set_frequency(1000);
  
  ATK::InWavFilter<double> filter(ATK_SOURCE_TREE "/tests/data/sinus1k.wav");
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

