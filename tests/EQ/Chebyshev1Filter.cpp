/**
 * \ file Chebyshev1Filter.cpp
 */

#include <ATK/EQ/Chebyshev1Filter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  filter.set_cut_frequency(20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequency(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequency(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_order_test )
{
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_ripple_test )
{
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  filter.set_ripple(20);
  BOOST_CHECK_EQUAL(filter.get_ripple(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_order_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  filter.set_cut_frequency(20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequency(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequency(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_ripple_test )
{
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  filter.set_ripple(20);
  BOOST_CHECK_EQUAL(filter.get_ripple(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_order_test )
{
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_order_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  filter.set_cut_frequencies(20, 100);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().first, 20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().second, 100);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(0, 100), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_frequency_range2_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(100, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_ripple_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  filter.set_ripple(20);
  BOOST_CHECK_EQUAL(filter.get_ripple(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_order_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_order_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  filter.set_cut_frequencies(20, 100);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().first, 20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().second, 100);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(0, 100), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_frequency_range2_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(100, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_ripple_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  filter.set_ripple(20);
  BOOST_CHECK_EQUAL(filter.get_ripple(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_order_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_order_range_test )
{
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.01587182644655375));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.8413951421002385));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.005576397202690614));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1LowPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.1962613670420864));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.9792933050029933));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.841395141674365));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.994533852735074));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1HighPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.841014519725825));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.84139514149622));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.14682528623369445));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.1462850319776135));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.8413951007802791));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.8413951401352051));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.8485500087021252));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.8490125934799859));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_Chebyshev1BandStopCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_ripple(3);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.8413953236422822));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
