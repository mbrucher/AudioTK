/**
 * \ file FixedDelayLineFilter.cpp
 */

#include <iostream>

#include <ATK/Delay/FixedDelayLineFilter.h>
#include <ATK/Delay/SIMD/FixedDelayLineFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Tools/SIMD/BroadcastFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(SIMDPP_ARCH_NAMESPACE, FixedDelayLineFilter_sinus_line100_delay50_test))
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
  
  std::array<simdpp::float32<4>, PROCESSSIZE> outdata;
  ATK::FixedDelayLineFilter<simdpp::float32<4>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &broadcaster, 0);
  filter.set_delay(50);

  ATK::OutPointerFilter<simdpp::float32<4>> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(1);
  output.process(49);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  auto zero = ATK::TypeTraits<simdpp::float32<4>>::Zero();
  for(ptrdiff_t i = 0; i < 50; ++i)
  {
    bool res = std::memcmp(&outdata[i], &zero, sizeof(simdpp::float32<4>)) == 0;
    BOOST_CHECK(res);
  }
  
  for(ptrdiff_t i = 50; i < PROCESSSIZE; ++i)
  {
    bool res = std::memcmp(&outdata[i], data.data() + i - 50, sizeof(simdpp::float32<4>)) == 0;
    BOOST_CHECK(res);
  }
}

#ifdef SIMDPP_EMIT_DISPATCHER
#endif
