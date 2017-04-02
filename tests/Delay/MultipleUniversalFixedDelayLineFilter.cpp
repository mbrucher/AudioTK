/**
 * \ file MultipleUniversalFixedDelayLineFilter
 */

#include <ATK/Delay/MultipleUniversalFixedDelayLineFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_linel100_delay50_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::MultipleUniversalFixedDelayLineFilter<float, 2> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_feedforward(0, 0, 1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 0; i < 50; ++i)
  {
    BOOST_REQUIRE_EQUAL(0, outdata[i]);
  }

  for(ptrdiff_t i = 50; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i - 50], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_linel25_delay24_blend_1_feedforward_1_feedback_0_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::MultipleUniversalFixedDelayLineFilter<float, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 24);
  filter.set_blend(0, 1);
  filter.set_feedback(0, 0, 0);
  filter.set_feedforward(0, 0, 1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001f);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_linel25_delay24_blend_0_feedforward_0_feedback_1_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::MultipleUniversalFixedDelayLineFilter<float, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 24);
  filter.set_blend(0, 0);
  filter.set_feedback(0, 0, 1);
  filter.set_feedforward(0, 0, 0);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001f);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_liner100_delay50_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::MultipleUniversalFixedDelayLineFilter<float, 2> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_feedforward(1, 1, 1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 1);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 0; i < 50; ++i)
  {
    BOOST_REQUIRE_EQUAL(0, outdata[i]);
  }

  for(ptrdiff_t i = 50; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i - 50], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_liner25_delay24_blend_1_feedforward_1_feedback_0_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::MultipleUniversalFixedDelayLineFilter<float, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 24);
  filter.set_blend(1, 1);
  filter.set_feedback(1, 1, 0);
  filter.set_feedforward(1, 1, 1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 1);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001f);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_liner25_delay24_blend_0_feedforward_0_feedback_1_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::MultipleUniversalFixedDelayLineFilter<float, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 24);
  filter.set_blend(1, 0);
  filter.set_feedback(1, 1, 1);
  filter.set_feedforward(1, 1, 0);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 1);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001f);
  }
}
