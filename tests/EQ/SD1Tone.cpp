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

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha0_100_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.24849356625414518));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha0_1k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.2372881019675525));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha0_10k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.2142359339618558));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha1_100_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.21866707240547373));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

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
  frequency_checks.push_back(std::make_pair(1000, 0.9101780576686395));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha1_10k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.23236933665054216));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha05_100_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.24849356625414518));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha05_1k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.2372881019675525));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_SD1ToneCoefficients_alpha05_10k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*1024);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*1024);
  filter.set_output_sampling_rate(1024*1024);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*1024);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.2142359339618558));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
