/**
 * \ file SimpleOverdriveFilter.cpp
 */

#include <ATK/Distortion/SimpleOverdriveFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SinusGeneratorFilter.h>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*64)

/*BOOST_AUTO_TEST_CASE( FirstOrderFilter_BandPassCoefficients_1k_test )
{
  ATK::SinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::FirstOrderFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(1000);
  filter.select(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.7070507157689713));
  frequency_checks.push_back(std::make_pair(2000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}*/
