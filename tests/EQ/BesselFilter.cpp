/**
 * \ file BesselFilter.cpp
 */

#include <iostream>
#include <ATK/EQ/BesselFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const size_t PROCESSSIZE = 1024*64;


BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_order_all_test )
{
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;

  for(unsigned int order = 1; order < 14; ++order)
  {
    filter.set_order(order);
  }
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
  BOOST_CHECK_THROW(filter.set_order(14), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_cut_frequency(20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequency(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequency(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_order_test )
{
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  filter.set_cut_frequency(20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequency(), 20);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequency(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_order_test )
{
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_order_range_test )
{
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  filter.set_cut_frequencies(20, 100);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().first, 20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().second, 100);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(0, 100), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_frequency_range2_test )
{
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(100, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_order_test )
{
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_order_range_test )
{
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_frequency_test )
{
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  filter.set_cut_frequencies(20, 100);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().first, 20);
  BOOST_CHECK_EQUAL(filter.get_cut_frequencies().second, 100);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_frequency_range_test )
{
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(0, 100), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_frequency_range2_test )
{
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_cut_frequencies(100, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_order_test )
{
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  filter.set_order(3);
  BOOST_CHECK_EQUAL(filter.get_order(), 3);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_order_range_test )
{
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_order(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.03150874916131525));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRTDF2Filter_BesselLowPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRTDF2Filter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.03150874916131525));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.6984126292895364));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.01112234417159909));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselLowPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.3285828399406346));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.9969240497367295));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.698412629282942));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.9992346889783681));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.9224070311673804));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.6982307944678048));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.26007771924713086));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.25916093406445906));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.6984126947004053));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.6982861807111302));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.945306052772074));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.9455314427571081));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequencies(std::make_pair(200, 1000));
  filter.set_order(3);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.6984125919453916));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
