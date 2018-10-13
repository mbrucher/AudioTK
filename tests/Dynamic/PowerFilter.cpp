/**
 * \ file PowerFilter.cpp
 */

#include <ATK/Dynamic/PowerFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_memory_test )
{
  ATK::PowerFilter<float> filter;
  filter.set_memory(0.5);
  BOOST_CHECK_EQUAL(filter.get_memory(), 0.5);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_throw_memory_0_test )
{
  ATK::PowerFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_memory(-1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_throw_memory_1_test )
{
  ATK::PowerFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_memory(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_0_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.7071067811865475244)); // Power will multiple frequency by 2
  frequency_checks.push_back(std::make_pair(4000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_05_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(0, 1));
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

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_09_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0.9);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.49107208814492116)); // cos power=1/(1+memory**2-2*memory*cos(2*pi*f/fs))
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_0_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.7071067811865475244)); // Power will multiple frequency by 2
  frequency_checks.push_back(std::make_pair(400, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_05_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.7069768533999591));
  frequency_checks.push_back(std::make_pair(400, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_09_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0.9);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.7013753920393636));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_0_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  frequency_checks.push_back(std::make_pair(20000, 0.7071067811865475244)); // Power will multiple frequency by 2
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_05_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  frequency_checks.push_back(std::make_pair(20000, 0.4452828409472382));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PowerFilter_RMS_09_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  ATK::PowerFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_memory(0.9);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(0, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  frequency_checks.push_back(std::make_pair(20000, 0.1792501270985228));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}
