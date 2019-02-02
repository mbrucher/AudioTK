/**
 * \ file MultipleUniversalFixedDelayLineFilter.cpp
 */

#include <ATK/Delay/MultipleUniversalFixedDelayLineFilter.h>

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

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_linel100_delay50_test )
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_feedforward(0, 0, 1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(gsl::index i = 0; i < 50; ++i)
  {
    BOOST_REQUIRE_EQUAL(0, outdata[i]);
  }

  for(gsl::index i = 50; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i - 50], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE(StereoUniversalFixedDelayLineFilter_sinus_line100_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_feedforward(0, 0, 1);
  filter.process(50);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 1; i < 100; ++i)
  {
    output.process(i);
  }
}

BOOST_AUTO_TEST_CASE(StereoUniversalFixedDelayLineFilter_sinus_line1000_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(1000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_feedforward(0, 0, 1);
  filter.process(50);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 50; i < 1000; ++i)
  {
    output.process(i);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_linel25_delay24_blend_1_feedforward_1_feedback_0_test )
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 24);
  filter.set_blend(0, 1);
  filter.set_feedback(0, 0, 0);
  filter.set_feedforward(0, 0, 1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(gsl::index i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_linel25_delay24_blend_0_feedforward_0_feedback_1_test )
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(0, 24);
  filter.set_blend(0, 0);
  filter.set_feedback(0, 0, .999999);
  filter.set_feedforward(0, 0, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(gsl::index i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_liner100_delay50_test )
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_feedforward(1, 1, 1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 1);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(gsl::index i = 0; i < 50; ++i)
  {
    BOOST_REQUIRE_EQUAL(0, outdata[i]);
  }

  for(gsl::index i = 50; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i - 50], outdata[i]);
  }
}

BOOST_AUTO_TEST_CASE(StereoUniversalFixedDelayLineFilter_sinus_liner100_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_feedforward(1, 1, 1);
  filter.process(50);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 1);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 1; i < 100; ++i)
  {
    output.process(i);
  }
}

BOOST_AUTO_TEST_CASE(StereoUniversalFixedDelayLineFilter_sinus_liner1000_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(1000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_feedforward(1, 1, 1);
  filter.process(50);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 1);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 50; i < 1000; ++i)
  {
    output.process(i);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_liner25_delay24_blend_1_feedforward_1_feedback_0_test )
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 24);
  filter.set_blend(1, 1);
  filter.set_feedback(1, 1, 0);
  filter.set_feedforward(1, 1, 1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 1);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(gsl::index i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_liner25_delay24_blend_0_feedforward_0_feedback_1_test )
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  filter.set_delay(1, 24);
  filter.set_blend(1, 0);
  filter.set_feedback(1, 1, .999999);
  filter.set_feedforward(1, 1, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 1);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(gsl::index i = 24; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.0001);
  }
}

const int OTHERPROCESSSIZE = 9600;

BOOST_AUTO_TEST_CASE(StereoUniversalFixedDelayLineFilter_sinus_lr_complex_test)
{
  std::vector<double> datal(OTHERPROCESSSIZE);
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_lstereo.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(datal.data()), OTHERPROCESSSIZE * sizeof(double));
  }
  std::vector<double> datar(OTHERPROCESSSIZE);
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_rstereo.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(datar.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  ATK::InPointerFilter<double> generatorl(datal.data(), 1, OTHERPROCESSSIZE, false);
  generatorl.set_output_sampling_rate(96000);
  ATK::InPointerFilter<double> generatorr(datar.data(), 1, OTHERPROCESSSIZE, false);
  generatorr.set_output_sampling_rate(96000);

  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(100000);
  filter.set_input_sampling_rate(96000);
  filter.set_input_port(0, &generatorl, 0);
  filter.set_input_port(1, &generatorr, 0);
  filter.set_delay(0, 4800);
  filter.set_delay(1, 3600);
  filter.set_blend(0, 1);
  filter.set_blend(1, 1);
  filter.set_feedforward(0, 0, -1);
  filter.set_feedforward(0, 1, .1);
  filter.set_feedforward(1, 0, .7);
  filter.set_feedforward(1, 1, -1);
  filter.set_feedback(0, 0, -.5);
  filter.set_feedback(0, 1, .1);
  filter.set_feedback(1, 0, .3);
  filter.set_feedback(1, 1, -.1);

  filter.process(OTHERPROCESSSIZE);

  std::vector<double> outdatal(OTHERPROCESSSIZE);
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_lstereo.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(outdatal.data()), OTHERPROCESSSIZE * sizeof(double));
  }
  std::vector<double> outdatar(OTHERPROCESSSIZE);
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_rstereo.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(outdatar.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < OTHERPROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(outdatal[i], filter.get_output_array(0)[i], 0.0001);
    BOOST_CHECK_CLOSE(outdatar[i], filter.get_output_array(1)[i], 0.0001);
  }
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_delay_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  filter.set_delay(0, 10);
  BOOST_CHECK_EQUAL(filter.get_delay(0), 10);
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_delay_range_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  BOOST_CHECK_THROW(filter.set_delay(0, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_delay_range2_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  BOOST_CHECK_THROW(filter.set_delay(0, 128), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_blend_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  filter.set_blend(0, 0.5);
  BOOST_CHECK_EQUAL(filter.get_blend(0), 0.5);
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_feedforward_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  filter.set_feedforward(0, 0, 0.5);
  BOOST_CHECK_EQUAL(filter.get_feedforward(0, 0), 0.5);
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_feedback_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  filter.set_feedback(0, 0, 0.5);
  BOOST_CHECK_EQUAL(filter.get_feedback(0, 0), 0.5);
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_feedback_range_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  BOOST_CHECK_THROW(filter.set_feedback(0, 0, 1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( StereoUniversalFixedDelayLineFilter_sinus_feedback_range2_test )
{
  ATK::MultipleUniversalFixedDelayLineFilter<double, 2> filter(128);
  BOOST_CHECK_THROW(filter.set_feedback(0, 0, -1), std::out_of_range);
}
