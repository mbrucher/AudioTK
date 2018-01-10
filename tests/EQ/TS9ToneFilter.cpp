/**
 * \ file TS9ToneFilter.cpp
 */

#include <ATK/EQ/PedalToneStackFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const size_t PROCESSSIZE = 1024*1026;
const size_t SAMPLINGRATE = 1024*64;

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_tone_test )
{
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_tone(.5);
  BOOST_CHECK_EQUAL(filter.get_tone(), .5);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_throw_1_test )
{
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_tone(1.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_throw_0_test )
{
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_tone(-0.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha0_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.95511927));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha0_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.16067427));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha0_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.14668446));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha1_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.95349053));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha1_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.95619999));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha1_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 1.03180903));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha05_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.95386498));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha05_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.97251369));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_TS9ToneCoefficients_alpha05_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::TS9ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.59163051));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
