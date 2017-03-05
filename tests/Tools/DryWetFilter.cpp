/**
 * \ file DryWetFilter.cpp
 */

#include <cmath>

#include <ATK/Core/InPointerFilter.h>

#include <ATK/Tools/DryWetFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024)

BOOST_AUTO_TEST_CASE( DryWetFilter_1_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::DryWetFilter<double> drywetfilter;
  drywetfilter.set_input_sampling_rate(48000);
  drywetfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  drywetfilter.set_input_port(0, &generator, 0);
  drywetfilter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &drywetfilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( DryWetFilter_0_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::DryWetFilter<double> drywetfilter;
  drywetfilter.set_input_sampling_rate(48000);
  drywetfilter.set_output_sampling_rate(48000);
  drywetfilter.set_dry(0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  drywetfilter.set_input_port(0, &generator, 0);
  drywetfilter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &drywetfilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( DryWetFilter_0_5_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::DryWetFilter<double> drywetfilter;
  drywetfilter.set_input_sampling_rate(48000);
  drywetfilter.set_output_sampling_rate(48000);
  drywetfilter.set_dry(.5);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  drywetfilter.set_input_port(0, &generator, 0);
  drywetfilter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &drywetfilter, 0);
  checker.process(PROCESSSIZE);
}
