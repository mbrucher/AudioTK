/**
 * \ file TimeVaryingSecondOrderSVFFilter.cpp
 */

#include <ATK/Core/InPointerFilter.h>

#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <array>

#include <boost/math/constants/constants.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;
constexpr gsl::index input_sampling_rate = 1024*64;

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFBandPassCoefficients_Q_test )
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_Q(0.5);
  BOOST_CHECK_EQUAL(filter.get_Q(), 0.5);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFBandPassCoefficients_Q_range_test )
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_Q(0.), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFBellCoefficients_gain_test )
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_gain(0.5);
  BOOST_CHECK_EQUAL(filter.get_gain(), 0.5);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFBellCoefficients_gain_range_test )
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  BOOST_CHECK_THROW(filter.set_gain(0.), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowShelfCoefficients_Q_test )
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_gain(0.5);
  BOOST_CHECK_EQUAL(filter.get_gain(), 0.5);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighShelfCoefficients_Q_test )
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_gain(0.5);
  BOOST_CHECK_EQUAL(filter.get_gain(), 0.5);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFBandPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_Q(1);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.3168938774681514));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFBandPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_Q(1);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFBandPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_Q(1);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.22340318032490636));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.10017263357405178));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.04987802660970978));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.5266273548331198));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighPassCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0024866672050896));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighPassCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighPassCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1.0006206013284984));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighPassCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1.0532789138212624));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFNotchCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.997469278));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFNotchCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 2.43511333e-04));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFNotchCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.999376691));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFNotchCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.912173284));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFPeakCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.98735801));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFPeakCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1.41421356));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFPeakCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.99688421));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFPeakCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.52667576));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFBellCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.19195065));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFBellCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 10));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFBellCoefficients_2k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1.05730389));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFFilter_SVFBellCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 2.59346645));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowShelvingCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0018539205036439));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowShelvingCoefficients_100_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.949414461057972));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFLowShelvingCoefficients_200_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);

  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1.037173648834839));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighShelvingCoefficients_1k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 1000 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.7905890936892349));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighShelvingCoefficients_10k_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 1000 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.5062960600823273));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TimeVaryingSecondOrderSVFHighShelvingCoefficients_500_test )
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(500);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 1000 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(500, 0.9220383944187385));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
