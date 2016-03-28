/**
 * \ file ToneStackFilter.cpp
 */

#include <ATK/EQ/ToneStackFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)
#define SAMPLINGRATE (1024*64)

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilterCoefficients_throw_low_1_test )
{
  ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_low(1.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilterCoefficients_throw_low_0_test )
{
  ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_low(-0.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilterCoefficients_throw_middle_1_test )
{
  ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_middle(1.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilterCoefficients_throw_middle_0_test )
{
  ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_middle(-0.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilterCoefficients_throw_high_1_test )
{
  ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_high(1.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilterCoefficients_throw_high_0_test )
{
  ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_high(-0.001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low0_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.520546902788));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low0_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.592829286291));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low0_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.780334219515));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low1_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.893700657602));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low1_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.535008479213));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low1_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.779778536574));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low05_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.883754524105));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low05_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.536676386406));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low05_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_low(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.779785204548));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle0_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.893445607385));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle0_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.3017133765430397));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle0_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.694818332337));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle1_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.880607047186));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle1_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.645182601381));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle1_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.827511818981));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle05_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.883754524105));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle05_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.536676386406));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_middle05_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_middle(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.779785204548));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high0_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.886723470765));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high0_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.519869436363));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high0_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(0);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.496368627553));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high1_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.880785350602));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high1_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.60150892675));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high1_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.98673661586));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high05_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.883754524105));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high05_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.536676386406));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_high05_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);

  std::unique_ptr<ATK::ToneStackFilterCoefficients<double> > filter(ATK::ToneStackFilterCoefficients<double>::buildBassmanStack());
  filter->set_input_sampling_rate(SAMPLINGRATE);
  filter->set_output_sampling_rate(SAMPLINGRATE);
  filter->set_high(.5);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.779785204548));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}
