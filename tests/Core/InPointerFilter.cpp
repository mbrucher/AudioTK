/**
 * \ file InPointerFilter.cpp
 */

#include <cmath>

#include <boost/math/constants/constants.hpp>

#include <ATK/Core/InPointerFilter.h>

#include <ATK/Mock/SinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (100)

BOOST_AUTO_TEST_CASE( InPointerFloat_sin1k_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  ATK::SinusGeneratorFilter<float> check;
  check.set_output_sampling_rate(48000);
  check.set_amplitude(-1);
  check.set_frequency(1000);
  
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &generator, 0);
  sum.set_input_port(1, &check, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( InPointerDouble_sin1k_test )
{
  boost::scoped_array<double> data(new double[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<double> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  ATK::SinusGeneratorFilter<double> check;
  check.set_output_sampling_rate(48000);
  check.set_amplitude(-1);
  check.set_frequency(1000);
  
  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &generator, 0);
  sum.set_input_port(1, &check, 0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( InPointerFloat_sin1k2k_interleaved_test )
{
  boost::scoped_array<float> data(new float[2*PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[2*i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
    data[2*i+1] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.get(), 2, PROCESSSIZE, true);
  generator.set_output_sampling_rate(48000);
  
  ATK::SinusGeneratorFilter<float> check1;
  check1.set_output_sampling_rate(48000);
  check1.set_amplitude(-1);
  check1.set_frequency(1000);
  
  ATK::SinusGeneratorFilter<float> check2;
  check2.set_output_sampling_rate(48000);
  check2.set_amplitude(-1);
  check2.set_frequency(2000);
  
  ATK::SumFilter<float> sum1;
  sum1.set_input_sampling_rate(48000);
  sum1.set_input_port(0, &generator, 0);
  sum1.set_input_port(1, &check1, 0);
  ATK::SumFilter<float> sum2;
  sum2.set_input_sampling_rate(48000);
  sum2.set_input_port(0, &generator, 1);
  sum2.set_input_port(1, &check2, 0);
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &sum1, 0);
  sum.set_input_port(1, &sum2, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( InPointerFloat_sin1k2k_noninterleaved_test )
{
  boost::scoped_array<float> data(new float[2*PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i+PROCESSSIZE] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.get(), 2, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  ATK::SinusGeneratorFilter<float> check1;
  check1.set_output_sampling_rate(48000);
  check1.set_amplitude(-1);
  check1.set_frequency(1000);
  
  ATK::SinusGeneratorFilter<float> check2;
  check2.set_output_sampling_rate(48000);
  check2.set_amplitude(-1);
  check2.set_frequency(2000);
  
  ATK::SumFilter<float> sum1;
  sum1.set_input_sampling_rate(48000);
  sum1.set_input_port(0, &generator, 0);
  sum1.set_input_port(1, &check1, 0);
  ATK::SumFilter<float> sum2;
  sum2.set_input_sampling_rate(48000);
  sum2.set_input_port(0, &generator, 1);
  sum2.set_input_port(1, &check2, 0);
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &sum1, 0);
  sum.set_input_port(1, &sum2, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);
  
  checker.process(PROCESSSIZE);
}
