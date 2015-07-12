/**
 * \ file InPointerFilter.cpp
 */

#include <cmath>

#include <boost/math/constants/constants.hpp>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/scoped_array.hpp>

#define PROCESSSIZE (10)

BOOST_AUTO_TEST_CASE( OutPointerFloat_sin1k_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);

  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE( OutPointerDouble_sin1k_test )
{
  boost::scoped_array<double> data(new double[PROCESSSIZE]);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<double> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  boost::scoped_array<double> outdata(new double[PROCESSSIZE]);
  
  ATK::OutPointerFilter<double> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  
  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE( OutPointerFloat_sin1k2k_interleaved_test )
{
  boost::scoped_array<float> data(new float[2*PROCESSSIZE]);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[2*i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
    data[2*i+1] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.get(), PROCESSSIZE, 2, true);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<double> outdata(new double[2*PROCESSSIZE]);
  
  ATK::OutPointerFilter<double> output(outdata.get(), PROCESSSIZE, 2, true);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  output.set_input_port(1, &generator, 1);
  
  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(int64_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE( OutPointerFloat_sin1k2k_noninterleaved_test )
{
  boost::scoped_array<float> data(new float[2*PROCESSSIZE]);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i+PROCESSSIZE] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.get(), 2, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  boost::scoped_array<double> outdata(new double[2*PROCESSSIZE]);
  
  ATK::OutPointerFilter<double> output(outdata.get(), 2, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  output.set_input_port(1, &generator, 1);

  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(int64_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}
