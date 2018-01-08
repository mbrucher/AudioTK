/**
 * \ file LinkwitzRileyFilter.cpp
 */

#include <ATK/EQ/LinkwitzRileyFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const size_t PROCESSSIZE = 1024*64;

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyLowPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> > filter;
  filter.set_cut_frequency(20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequency(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRiley4LowPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<double> > filter;
  filter.set_cut_frequency(20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequency(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyLowPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.09942899724462938));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyLowPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.7071067811865476));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyLowPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.04978527826193893));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyLowPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.44720537393460674));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyHighPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.9950446595540061));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyHighPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.7071067811865476));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyHighPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.9987599441649563));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_LinkwitzRileyHighPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.8944313017355006));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4LowPassCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.00998434));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4LowPassCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.7071067811865476));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4LowPassCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);

  ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.00248472));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4LowPassCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(200);

  ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.24252513));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4HighPassCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.99995016));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4HighPassCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.7071067811865476));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4HighPassCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);

  ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.99999691));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(IIRFilter_LinkwitzRiley4HighPassCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(200);

  ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.97014512));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}
