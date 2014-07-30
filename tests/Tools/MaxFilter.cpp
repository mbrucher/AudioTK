/**
 * \ file MaxFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/MaxFilter.h>
#include <ATK/Tools/OffsetVolumeFilter.h>
#include <ATK/Tools/SumFilter.h>

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
  ATK::OffsetVolumeFilter<double> inversefilter;
  inversefilter.set_input_sampling_rate(48000);
  inversefilter.set_volume(-1);
  
  ATK::MaxFilter<double> maxfilter;
  maxfilter.set_input_sampling_rate(48000);
  maxfilter.set_output_sampling_rate(48000);

  ATK::OffsetVolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_volume(2);
  volumefilter.set_offset(-1);

  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(2000);
  
  inversefilter.set_input_port(0, &generator, 0);
  maxfilter.set_input_port(0, &inversefilter, 0);
  maxfilter.set_input_port(1, &generator, 0);
  volumefilter.set_input_port(0, &maxfilter, 0);
  checker.set_input_port(0, &volumefilter, 0);
  volumefilter.process(48000/1000/4);
  checker.process(12);
}
