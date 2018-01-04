/**
 * \ file HadamardFeedbackDelayNetworkFilter.cpp
 */

#include <ATK/Delay/FeedbackDelayNetworkFilter.h>
#include <ATK/Delay/HadamardMixture.h>

#ifndef EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

#include <array>
#include <fstream>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( HadamardFeedbackDelayNetworkFilter_sinus_linel100_delay50_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_ingain(0, 1);
  filter.set_outgain(0, 1);

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

BOOST_AUTO_TEST_CASE(HadamardFeedbackDelayNetworkFilter_sinus_line100_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_ingain(0, 1);
  filter.set_outgain(0, 1);
  filter.process(50);

  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<float> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 1; i < 100; ++i)
  {
    output.process(i);
  }
}

BOOST_AUTO_TEST_CASE(HadamardFeedbackDelayNetworkFilter_sinus_line1000_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>> filter(1000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_ingain(0, 1);
  filter.set_outgain(0, 1);
  filter.process(50);

  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<float> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 50; i < 1000; ++i)
  {
    output.process(i);
  }
}

BOOST_AUTO_TEST_CASE( HadamardFeedbackDelayNetworkFilter_sinus_liner100_delay50_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_ingain(1, 1);
  filter.set_outgain(1, 1);

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

BOOST_AUTO_TEST_CASE(HadamardFeedbackDelayNetworkFilter_sinus_liner100_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_ingain(1, 1);
  filter.set_outgain(1, 1);
  filter.process(50);

  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<float> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 1; i < 100; ++i)
  {
    output.process(i);
  }
}

BOOST_AUTO_TEST_CASE(HadamardFeedbackDelayNetworkFilter_sinus_liner1000_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>> filter(1000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_ingain(1, 1);
  filter.set_outgain(1, 1);
  filter.process(50);

  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<float> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 50; i < 1000; ++i)
  {
    output.process(i);
  }
}

const int OTHERPROCESSSIZE = 9600;

BOOST_AUTO_TEST_CASE(HadamardFeedbackDelayNetworkFilter_sinus_complex_test)
{
  std::array<double, OTHERPROCESSSIZE> data;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_hadamard.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, OTHERPROCESSSIZE, false);
  generator.set_output_sampling_rate(96000);

  ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 2>> filter(100000);
  filter.set_input_sampling_rate(96000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 4800);
  filter.set_delay(1, 3600);
  filter.set_delay(2, 2400);
  filter.set_delay(3, 1200);
  filter.set_ingain(0, 1);
  filter.set_ingain(1, .2);
  filter.set_ingain(2, 1);
  filter.set_ingain(3, 1);
  filter.set_outgain(0, 1);
  filter.set_outgain(1, 1);
  filter.set_outgain(2, 1);
  filter.set_outgain(3, .5);
  filter.set_feedback(0, .2);
  filter.set_feedback(1, .8);
  filter.set_feedback(2, .4);
  filter.set_feedback(3, .2);

  filter.process(OTHERPROCESSSIZE);

  std::array<double, OTHERPROCESSSIZE> outdata;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_hadamard.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(outdata.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < OTHERPROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(outdata[i], filter.get_output_array(0)[i], 0.0001);
  }
}
#endif
