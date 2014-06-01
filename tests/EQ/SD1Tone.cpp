/**
 * \ file SD1ToneFilter.cpp
 */

#include <ATK/EQ/SD1ToneFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha1_1k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(64);
  //filter.process(1024*64);
  
  //checker.process(PROCESSSIZE);
}
