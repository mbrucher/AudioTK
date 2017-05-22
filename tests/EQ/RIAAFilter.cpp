/**
 * \ file RIAAFilter.cpp
 */

#include <ATK/EQ/RIAAFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const int PROCESSSIZE = 1024*64;
const int SAMPLINGRATE = 96000;

BOOST_AUTO_TEST_CASE( IIRFilter_RIAACoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::RIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 2.01060845));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_RIAACoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::RIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1.89328793));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_RIAACoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1420);
  
  ATK::IIRFilter<ATK::RIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1420, 1.00011655));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_RIAACoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::RIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.87855133));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_RIAACoefficients_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::RIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.59615476));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_InverseRIAACoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::InverseRIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1/2.01060845));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_InverseRIAACoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::InverseRIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1/1.89328793));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_InverseRIAACoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1420);
  
  ATK::IIRFilter<ATK::InverseRIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1420, 1/1.00011655));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_InverseRIAACoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::InverseRIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1/0.87855133));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_InverseRIAACoefficients_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::InverseRIAACoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 1/0.59615476));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(PROCESSSIZE);
  
  checker.process(PROCESSSIZE);
}

