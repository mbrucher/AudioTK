/**
 * \ file BesselFilter.cpp
 */

#include <iostream>

#include <simdpp/simd.h>

#include <ATK/Core/PipelineGlobalSinkFilter.h>
#include <ATK/Core/SIMD/QuaternionConvertFilter.h>

#include <ATK/EQ/BesselFilter.h>
#include <ATK/EQ/SimpleIIRFilter.h>
#include <ATK/EQ/SIMD/BesselFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(SIMDPP_ARCH_NAMESPACE, IIRFilter_BesselLowPassCoefficients_test))
{
  ATK::SimpleSinusGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(PROCESSSIZE);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  ATK::SimpleSinusGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(PROCESSSIZE);
  generator2.set_amplitude(1);
  generator2.set_frequency(100);
  ATK::SimpleSinusGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(PROCESSSIZE);
  generator3.set_amplitude(1);
  generator3.set_frequency(2000);
  ATK::SimpleSinusGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(PROCESSSIZE);
  generator4.set_amplitude(1);
  generator4.set_frequency(200);

  ATK::RealToQuaternionFilter<double, simdpp::float64<4> > forwardConvert;
  forwardConvert.set_output_delay(3);
  forwardConvert.set_input_sampling_rate(PROCESSSIZE);
  forwardConvert.set_output_sampling_rate(PROCESSSIZE);
  forwardConvert.set_input_port(0, &generator1, 0);
  forwardConvert.set_input_port(1, &generator2, 0);
  forwardConvert.set_input_port(2, &generator3, 0);
  forwardConvert.set_input_port(3, &generator4, 0);

  ATK::SimpleIIRFilter<ATK::BesselLowPassCoefficients<simdpp::float64<4> > > filter;
  filter.set_input_sampling_rate(PROCESSSIZE);
  filter.set_output_sampling_rate(PROCESSSIZE);
  filter.set_cut_frequency(100);
  filter.set_order(3);
  filter.set_input_port(0, &forwardConvert, 0);

  ATK::QuaternionToRealFilter<simdpp::float64<4>, double> backwardConvert;
  backwardConvert.set_input_sampling_rate(PROCESSSIZE);
  backwardConvert.set_output_sampling_rate(PROCESSSIZE);
  backwardConvert.set_input_port(0, &filter, 0);
  
  ATK::FFTCheckerFilter<double> checker1;
  checker1.set_input_sampling_rate(PROCESSSIZE);
  checker1.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks1;
  frequency_checks1.push_back(std::make_pair(100, 0));
  frequency_checks1.push_back(std::make_pair(1000, 0.03150874916131525));
  frequency_checks1.push_back(std::make_pair(10000, 0));
  checker1.set_checks(frequency_checks1);
  checker1.set_input_port(0, &backwardConvert, 0);
  ATK::FFTCheckerFilter<double> checker2;
  checker2.set_input_sampling_rate(PROCESSSIZE);
  checker2.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks2;
  frequency_checks2.push_back(std::make_pair(10, 0));
  frequency_checks2.push_back(std::make_pair(100, 0.6984126292895364));
  frequency_checks2.push_back(std::make_pair(1000, 0));
  checker2.set_checks(frequency_checks2);
  checker2.set_input_port(0, &backwardConvert, 1);
  ATK::FFTCheckerFilter<double> checker3;
  checker3.set_input_sampling_rate(PROCESSSIZE);
  checker3.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks3;
  frequency_checks3.push_back(std::make_pair(100, 0));
  frequency_checks3.push_back(std::make_pair(1000, 0));
  frequency_checks3.push_back(std::make_pair(2000, 0.01112234417159909));
  checker3.set_checks(frequency_checks3);
  checker3.set_input_port(0, &backwardConvert, 2);
  ATK::FFTCheckerFilter<double> checker4;
  checker4.set_input_sampling_rate(PROCESSSIZE);
  checker4.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks4;
  frequency_checks4.push_back(std::make_pair(100, 0));
  frequency_checks4.push_back(std::make_pair(200, 0.3285828399406346));
  frequency_checks4.push_back(std::make_pair(1000, 0));
  checker4.set_checks(frequency_checks4);
  checker4.set_input_port(0, &backwardConvert, 3);

  ATK::PipelineGlobalSinkFilter sink;
  sink.set_input_sampling_rate(PROCESSSIZE);
  sink.set_output_sampling_rate(PROCESSSIZE);
  sink.add_filter(&checker1);
  sink.add_filter(&checker2);
  sink.add_filter(&checker3);
  sink.add_filter(&checker4);

  backwardConvert.process(PROCESSSIZE);

  sink.process(PROCESSSIZE);
}
/*

 BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_1k_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(1000);
 
 ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequency(100);
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(1000, 0.9969240497367295));
 frequency_checks.push_back(std::make_pair(10000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_100_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(100);
 
 ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequency(100);
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(10, 0));
 frequency_checks.push_back(std::make_pair(100, 0.698412629282942));
 frequency_checks.push_back(std::make_pair(1000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_2k_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(2000);
 
 ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequency(100);
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(1000, 0));
 frequency_checks.push_back(std::make_pair(2000, 0.9992346889783681));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselHighPassCoefficients_200_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(200);
 
 ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequency(100);
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(200, 0.9224070311673804));
 frequency_checks.push_back(std::make_pair(1000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_1k_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(1000);
 
 ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(1000, 0.6982307944678048));
 frequency_checks.push_back(std::make_pair(10000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_100_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(100);
 
 ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(10, 0));
 frequency_checks.push_back(std::make_pair(100, 0.26007771924713086));
 frequency_checks.push_back(std::make_pair(1000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_2k_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(2000);
 
 ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(1000, 0));
 frequency_checks.push_back(std::make_pair(2000, 0.25916093406445906));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandPassCoefficients_200_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(200);
 
 ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(200, 0.6984126947004053));
 frequency_checks.push_back(std::make_pair(1000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_1k_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(1000);
 
 ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(1000, 0.6982861807111302));
 frequency_checks.push_back(std::make_pair(10000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_100_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(100);
 
 ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(10, 0));
 frequency_checks.push_back(std::make_pair(100, 0.945306052772074));
 frequency_checks.push_back(std::make_pair(1000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_2k_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(2000);
 
 ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(1000, 0));
 frequency_checks.push_back(std::make_pair(2000, 0.9455314427571081));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 
 BOOST_AUTO_TEST_CASE( IIRFilter_BesselBandStopCoefficients_200_test )
 {
 ATK::SimpleSinusGeneratorFilter<double> generator;
 generator.set_output_sampling_rate(PROCESSSIZE);
 generator.set_amplitude(1);
 generator.set_frequency(200);
 
 ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> > filter;
 filter.set_input_sampling_rate(PROCESSSIZE);
 filter.set_output_sampling_rate(PROCESSSIZE);
 filter.set_cut_frequencies(std::make_pair(200, 1000));
 filter.set_order(3);
 
 ATK::FFTCheckerFilter<double> checker;
 checker.set_input_sampling_rate(PROCESSSIZE);
 std::vector<std::pair<int, double> > frequency_checks;
 frequency_checks.push_back(std::make_pair(100, 0));
 frequency_checks.push_back(std::make_pair(200, 0.6984125919453916));
 frequency_checks.push_back(std::make_pair(1000, 0));
 checker.set_checks(frequency_checks);
 
 checker.set_input_port(0, &filter, 0);
 filter.set_input_port(0, &generator, 0);
 
 filter.process(PROCESSSIZE);
 
 checker.process(PROCESSSIZE);
 }
 */

#ifdef SIMDPP_EMIT_DISPATCHER
BOOST_AUTO_TEST_CASE(IIRFilter_BesselLowPassCoefficients_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(PROCESSSIZE);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  ATK::SimpleSinusGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(PROCESSSIZE);
  generator2.set_amplitude(1);
  generator2.set_frequency(100);
  ATK::SimpleSinusGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(PROCESSSIZE);
  generator3.set_amplitude(1);
  generator3.set_frequency(2000);
  ATK::SimpleSinusGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(PROCESSSIZE);
  generator4.set_amplitude(1);
  generator4.set_frequency(200);
  
  auto forwardConvert = ATK::createRealToQuaternionFilter<float>();
  forwardConvert->set_output_delay(3);
  forwardConvert->set_input_sampling_rate(PROCESSSIZE);
  forwardConvert->set_output_sampling_rate(PROCESSSIZE);
  forwardConvert->set_input_port(0, &generator1, 0);
  forwardConvert->set_input_port(1, &generator2, 0);
  forwardConvert->set_input_port(2, &generator3, 0);
  forwardConvert->set_input_port(3, &generator4, 0);
  
  auto filter = ATK::createLowPassBesselFilter<float, 4>();
  filter->set_input_sampling_rate(PROCESSSIZE);
  filter->set_output_sampling_rate(PROCESSSIZE);
  dynamic_cast<ATK::SingleCutFrequencyInterface<float>*>(filter.get())->set_cut_frequency(100);
  dynamic_cast<ATK::OrderInterface*>(filter.get())->set_order(3);
  filter->set_input_port(0, forwardConvert.get(), 0);
  
  auto backwardConvert = ATK::createQuaternionToRealFilter<float>();
  backwardConvert->set_input_sampling_rate(PROCESSSIZE);
  backwardConvert->set_output_sampling_rate(PROCESSSIZE);
  backwardConvert->set_input_port(0, filter.get(), 0);
  
  ATK::FFTCheckerFilter<double> checker1;
  checker1.set_input_sampling_rate(PROCESSSIZE);
  checker1.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks1;
  frequency_checks1.push_back(std::make_pair(100, 0));
  frequency_checks1.push_back(std::make_pair(1000, 0.03150874916131525));
  frequency_checks1.push_back(std::make_pair(10000, 0));
  checker1.set_checks(frequency_checks1);
  checker1.set_input_port(0, backwardConvert.get(), 0);
  ATK::FFTCheckerFilter<double> checker2;
  checker2.set_input_sampling_rate(PROCESSSIZE);
  checker2.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks2;
  frequency_checks2.push_back(std::make_pair(10, 0));
  frequency_checks2.push_back(std::make_pair(100, 0.6984126292895364));
  frequency_checks2.push_back(std::make_pair(1000, 0));
  checker2.set_checks(frequency_checks2);
  checker2.set_input_port(0, backwardConvert.get(), 1);
  ATK::FFTCheckerFilter<double> checker3;
  checker3.set_input_sampling_rate(PROCESSSIZE);
  checker3.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks3;
  frequency_checks3.push_back(std::make_pair(100, 0));
  frequency_checks3.push_back(std::make_pair(1000, 0));
  frequency_checks3.push_back(std::make_pair(2000, 0.01112234417159909));
  checker3.set_checks(frequency_checks3);
  checker3.set_input_port(0, backwardConvert.get(), 2);
  ATK::FFTCheckerFilter<double> checker4;
  checker4.set_input_sampling_rate(PROCESSSIZE);
  checker4.set_output_sampling_rate(PROCESSSIZE);
  std::vector<std::pair<int, double> > frequency_checks4;
  frequency_checks4.push_back(std::make_pair(100, 0));
  frequency_checks4.push_back(std::make_pair(200, 0.3285828399406346));
  frequency_checks4.push_back(std::make_pair(1000, 0));
  checker4.set_checks(frequency_checks4);
  checker4.set_input_port(0, backwardConvert.get(), 3);
  
  ATK::PipelineGlobalSinkFilter sink;
  sink.set_input_sampling_rate(PROCESSSIZE);
  sink.set_output_sampling_rate(PROCESSSIZE);
  sink.add_filter(&checker1);
  //sink.add_filter(&checker2);
  sink.add_filter(&checker3);
  //sink.add_filter(&checker4);
  
  backwardConvert->process(PROCESSSIZE);
  
  sink.process(PROCESSSIZE);
}
#endif
