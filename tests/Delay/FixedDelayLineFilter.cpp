/**
 * \ file FixedDelayLineFilter.cpp
 */

#include <ATK/Delay/FixedDelayLineFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( FixedDelayLineFilter_line100_delay_1_test )
{
  ATK::FixedDelayLineFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_delay(-1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( FixedDelayLineFilter_line100_delay_100_test )
{
  ATK::FixedDelayLineFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_delay(100), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( FixedDelayLineFilter_sinus_line100_delay50_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::FixedDelayLineFilter<float> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(50);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(1);
  output.process(49);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  for(std::int64_t i = 0; i < 50; ++i)
  {
    BOOST_REQUIRE_EQUAL(0, outdata[i]);
  }
  
  for(std::int64_t i = 50; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i - 50], outdata[i]);
  }
}
