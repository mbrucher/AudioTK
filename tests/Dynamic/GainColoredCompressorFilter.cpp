/**
* \ file GainColoredCompressorFilter.cpp
*/

#include <ATK/Dynamic/GainColoredCompressorFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>
#include <boost/scoped_array.hpp>

#define PROCESSSIZE (64)

BOOST_AUTO_TEST_CASE(GainColoredCompressorFilter_const_1_test)
{
  std::array<float, PROCESSSIZE> data;
  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredCompressorFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(10);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(1, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE(GainColoredCompressorFilter_const_0_test)
{
  std::array<float, PROCESSSIZE> data;
  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredCompressorFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(1, outdata[i], 0.1); // if input is zero, we still need a gain of 1 to have a progression of 1 for values < threshold
  }
}

BOOST_AUTO_TEST_CASE(GainColoredCompressorFilter_const_1_threshold_05_ratio_2_test)
{
  std::array<float, PROCESSSIZE> data;
  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredCompressorFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(2);
  filter.set_softness(1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.836990654, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE(GainColoredCompressorFilter_const_1_threshold_05_ratio_4_test)
{
  std::array<float, PROCESSSIZE> data;
  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredCompressorFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(4);
  filter.set_softness(1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.765739262, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE(GainColoredCompressorFilter_always_more_1_test)
{
  std::array<float, PROCESSSIZE> data;
  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = i / 1024.;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredCompressorFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(1);
  filter.set_quality(.1);
  filter.set_color(.1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_GE(outdata[i], 1);
  }
}

BOOST_AUTO_TEST_CASE(GainColoredCompressorFilter_always_less_1_test)
{
  std::array<float, PROCESSSIZE> data;
  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = i / 1024.;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredCompressorFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(1);
  filter.set_quality(.1);
  filter.set_color(-.1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_LE(outdata[i], 1);
  }
}
