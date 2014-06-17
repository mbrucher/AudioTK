/**
 * \ file ToneStackFilter.cpp
 */

#include <ATK/EQ/ToneStackFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)
#define SAMPLINGRATE (1024*64)

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low0_100_test )
{
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(100, 0.539546227384));
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
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(1000, 0.639908258891));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low0_10k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(10000, 0.785483116609));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low1_100_test )
{
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(100, 1.21437059728));
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
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(1000, 0.526240477328));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low1_10k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(10000, 0.778758646157));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low05_100_test )
{
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(100, 1.27317612576));
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
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(1000, 0.528928508155));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( IIRFilter_ToneStackFilter_Bassman_low05_10k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
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
  frequency_checks.push_back(std::make_pair(10000, 0.778820213842));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, filter.get(), 0);
  filter->set_input_port(0, &generator, 0);

  filter->process(1024*64);

  checker.process(PROCESSSIZE);
}
