/**
 * \ file SimpleOverdriveFilter.cpp
 */

#include <ATK/Distortion/SimpleOverdriveFilter.h>

#include <ATK/Mock/SinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( SimpleOverdriveFilter_sin1k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::SimpleOverdriveFilter<double> filter;
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  checker.process(PROCESSSIZE);
}
