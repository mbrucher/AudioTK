/**
 * \ file VolumeFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/VolumeFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024;

BOOST_AUTO_TEST_CASE( VolumeFilter_volume_test )
{
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_volume(10);
  BOOST_CHECK_EQUAL(volumefilter.get_volume(), 10);
}

BOOST_AUTO_TEST_CASE( VolumeFilter_1_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( VolumeFilter_0dB_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume_db(0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( VolumeFilter_2_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume(2);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(2);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( VolumeFilter_6dB_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume_db(6);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1.995262);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( VolumeFilter_0_5_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume(.5);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( VolumeFilter__6dB_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume_db(-6);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1/1.995262);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}
