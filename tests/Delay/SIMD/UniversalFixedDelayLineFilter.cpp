/**
 * \ file UniversalFixedDelayLineFilter.cpp
 */

#include <ATK/Delay/UniversalFixedDelayLineFilter.h>
#include <ATK/Delay/SIMD/UniversalFixedDelayLineFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Tools/SIMD/BroadcastFilter.h>
#include <ATK/Tools/SIMD/ReduceFilter.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(SIMDPP_ARCH_NAMESPACE, UniversalFixedDelayLineFilter_sinus_line100_delay50_test ))
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::BroadcastFilter<float, simdpp::float32<4>> broadcaster;
  broadcaster.set_input_sampling_rate(48000);
  broadcaster.set_input_port(0, &generator, 0);

  ATK::UniversalFixedDelayLineFilter<simdpp::float32<4>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &broadcaster, 0);
  filter.set_delay(50);

  ATK::ReduceFilter<simdpp::float32<4>, float> reducer;
  reducer.set_input_sampling_rate(48000);
  reducer.set_input_port(0, &filter, 0);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &reducer, 0);

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
    BOOST_REQUIRE_EQUAL(data[i - 50] * 4, outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(SIMDPP_ARCH_NAMESPACE, UniversalFixedDelayLineFilter_sinus_line25_delay24_blend_1_feedforward_1_feedback_0_test))
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  ATK::BroadcastFilter<float, simdpp::float32<4>> broadcaster;
  broadcaster.set_input_sampling_rate(48000);
  broadcaster.set_input_port(0, &generator, 0);

  std::array<float, PROCESSSIZE> outdata;

  ATK::UniversalFixedDelayLineFilter<simdpp::float32<4>> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &broadcaster, 0);
  filter.set_delay(24);
  filter.set_blend(1);
  filter.set_feedback(0);
  filter.set_feedforward(1);

  ATK::ReduceFilter<simdpp::float32<4>, float> reducer;
  reducer.set_input_sampling_rate(48000);
  reducer.set_input_port(0, &filter, 0);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &reducer, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001f);
  }
}

BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(SIMDPP_ARCH_NAMESPACE, UniversalFixedDelayLineFilter_sinus_line25_delay24_blend_0_feedforward_0_feedback_1_test))
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  ATK::BroadcastFilter<float, simdpp::float32<4>> broadcaster;
  broadcaster.set_input_sampling_rate(48000);
  broadcaster.set_input_port(0, &generator, 0);

  std::array<float, PROCESSSIZE> outdata;

  ATK::UniversalFixedDelayLineFilter<simdpp::float32<4>> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &broadcaster, 0);
  filter.set_delay(24);
  filter.set_blend(0);
  filter.set_feedback(1);
  filter.set_feedforward(0);

  ATK::ReduceFilter<simdpp::float32<4>, float> reducer;
  reducer.set_input_sampling_rate(48000);
  reducer.set_input_port(0, &filter, 0);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &reducer, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(ptrdiff_t i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001f);
  }
}
