/**
 * \ file MaxFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/MaxFilter.h>
#include <ATK/Tools/VolumeFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( MaxFilter_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::MaxFilter<double> MaxFilter;
  MaxFilter.set_input_sampling_rate(48000);
  MaxFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(3);
  checker.set_frequency(1000);
  
  MaxFilter.set_input_port(0, &generator, 0);
  MaxFilter.set_input_port(1, &generator2, 0);
  checker.set_input_port(0, &MaxFilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MaxFilter_VolumeFilter_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume(2);
  
  ATK::MaxFilter<double> MaxFilter;
  MaxFilter.set_input_sampling_rate(48000);
  MaxFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(3);
  checker.set_frequency(1000);
  
  MaxFilter.set_input_port(0, &generator, 0);
  volumefilter.set_input_port(0, &generator, 0);
  MaxFilter.set_input_port(1, &volumefilter, 0);
  checker.set_input_port(0, &MaxFilter, 0);
  checker.process(PROCESSSIZE);
}
