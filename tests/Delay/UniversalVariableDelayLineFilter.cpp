/**
 * \ file UniversalVariableDelayLineFilter.cpp
 */

#include <iostream>

#include <ATK/Delay/UniversalVariableDelayLineFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Tools/CachedSinusGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( UniversalVariableDelayLineFilter_sinus_line16000_delaysinus_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  boost::scoped_array<float> datadelay(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    datadelay[i] = 1 + i * .25f;
  }

  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  ATK::InPointerFilter<float> generatordelay(datadelay.get(), 1, PROCESSSIZE, false);
  generatordelay.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::UniversalVariableDelayLineFilter<float> filter(48000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generatordelay, 0);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(1);
  output.process(49);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  for(std::int64_t i = 1; i < PROCESSSIZE/4; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i*4 - i - 1], outdata[i*4]);
  }
  for(std::int64_t i = 1; i < PROCESSSIZE/4; ++i)
  {
    std::int64_t current = 4*i+1;
    BOOST_REQUIRE_EQUAL((data[current - i-1]*3 + data[current - i-2])/4, outdata[current]);
  }
  for(std::int64_t i = 1; i < PROCESSSIZE/4; ++i)
  {
    std::int64_t current = 4*i+2;
    BOOST_REQUIRE_EQUAL((data[current - i-1] + data[current - i-2])/2, outdata[current]);
  }
  for(std::int64_t i = 1; i < PROCESSSIZE/4; ++i)
  {
    std::int64_t current = 4*i+3;
    BOOST_REQUIRE_EQUAL((data[current - i-1] + data[current - i-2]*3)/4, outdata[current]);
  }
}

BOOST_AUTO_TEST_CASE( UniversalVariableDelayLineFilter_sinus_cachedgenerator_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(std::int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> sinus(data.get(), 1, PROCESSSIZE, false);
  sinus.set_output_sampling_rate(48000);
  ATK::CachedSinusGeneratorFilter<float> generator(1, 1);
  generator.set_output_sampling_rate(48000);
  generator.set_volume((1e-3)*48000);
  generator.set_offset((1.5e-3)*48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::UniversalVariableDelayLineFilter<float> filter(128);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &sinus, 0);
  filter.set_input_port(1, &generator, 0);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(1);
  output.process(49);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
}
