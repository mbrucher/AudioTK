/**
 * \file OversamplingFilter.cpp
 */

#include <ATK/Tools/OversamplingFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SinusGeneratorFilter.h>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( OversamplingFilter_sinus_2_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::OversamplingFilter<double, ATK::Oversampling6points5order_2<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*128);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*128);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( OversamplingFilter_sinus_4_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::OversamplingFilter<double, ATK::Oversampling6points5order_4<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64*4);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64*4);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( OversamplingFilter_sinus_8_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::OversamplingFilter<double, ATK::Oversampling6points5order_8<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64*8);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64*8);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( OversamplingFilter_sinus_16_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::OversamplingFilter<double, ATK::Oversampling6points5order_16<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64*16);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64*16);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( OversamplingFilter_sinus_32_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::OversamplingFilter<double, ATK::Oversampling6points5order_32<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64*32);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64*32);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}
