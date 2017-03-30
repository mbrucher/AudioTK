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
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);

  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE( OutPointerDouble_sin1k_test )
{
  std::array<double, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::array<double, PROCESSSIZE> outdata;
  
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  
  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE(OutPointerDouble_check_bound_test)
{
  std::array<double, PROCESSSIZE> data;
  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i + 1.) / 48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, 2*PROCESSSIZE> outdata;
  std::fill(outdata.begin(), outdata.end(), -1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, 3*PROCESSSIZE/2, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);

  output.process(2*PROCESSSIZE);

  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
  for (ptrdiff_t i = 0; i < PROCESSSIZE / 2; ++i)
  {
    BOOST_REQUIRE_EQUAL(0, outdata[PROCESSSIZE + i]); // check that input is now 0
  }
  for (ptrdiff_t i = 0; i < PROCESSSIZE / 2; ++i)
  {
    BOOST_REQUIRE_EQUAL(-1, outdata[3 * PROCESSSIZE /2 + i]); // check that we don't write after what we declare was allocated
  }
}

BOOST_AUTO_TEST_CASE( OutPointerFloat_sin1k2k_interleaved_test )
{
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[2*i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
    data[2*i+1] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), PROCESSSIZE, 2, true);
  generator.set_output_sampling_rate(48000);

  std::array<double, 2*PROCESSSIZE> outdata;
  
  ATK::OutPointerFilter<double> output(outdata.data(), PROCESSSIZE, 2, true);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  output.set_input_port(1, &generator, 1);
  
  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE( OutPointerFloat_sin1k2k_noninterleaved_test )
{
  std::array<float, 2*PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i+PROCESSSIZE] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 2, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::array<double, 2*PROCESSSIZE> outdata;
  
  ATK::OutPointerFilter<double> output(outdata.data(), 2, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  output.set_input_port(1, &generator, 1);

  output.process(2);
  output.process(PROCESSSIZE - 2);
  
  for(ptrdiff_t i = 0; i < 2*PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i], outdata[i]);
  }
}
