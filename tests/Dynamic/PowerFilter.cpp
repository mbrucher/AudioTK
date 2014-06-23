/**
 * \ file PowerFilter.cpp
 */

#include <ATK/Dynamic/PowerFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_0_1k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.5)); // Power will multiple frequency by 2
  frequency_checks.push_back(std::make_pair(4000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_throw_memory_0_test )
{
  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  BOOST_CHECK_THROW(filter.set_memory(-1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_throw_memory_1_test )
{
  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  BOOST_CHECK_THROW(filter.set_memory(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_05_1k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.6947103730615206));
  frequency_checks.push_back(std::make_pair(4000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}
