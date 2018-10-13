/**
 * \ file AllPassReverbFilter.cpp
 */

#include <ATK/Reverberation/AllPassReverbFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_delay_test )
{
  ATK::AllPassReverbFilter<float> filter(128);
  filter.set_delay(10);
  BOOST_CHECK_EQUAL(filter.get_delay(), 10);
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_delay_range_test )
{
  ATK::AllPassReverbFilter<float> filter(128);
  BOOST_CHECK_THROW(filter.set_delay(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_delay_range2_test )
{
  ATK::AllPassReverbFilter<float> filter(128);
  BOOST_CHECK_THROW(filter.set_delay(128), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_feedback_test )
{
  ATK::AllPassReverbFilter<float> filter(128);
  filter.set_feedback(0.5);
  BOOST_CHECK_EQUAL(filter.get_feedback(), 0.5);
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_feedback_range_test )
{
  ATK::AllPassReverbFilter<float> filter(128);
  BOOST_CHECK_THROW(filter.set_feedback(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_feedback_range2_test )
{
  ATK::AllPassReverbFilter<float> filter(128);
  BOOST_CHECK_THROW(filter.set_feedback(-1), std::out_of_range);
}

namespace
{
  void compare(float v1, float v2)
  {
    if(std::abs(v1) < 1e-5 || std::abs(v2) < 1e-5)
    {
      BOOST_REQUIRE_SMALL(v1, static_cast<float>(1e-5));
      BOOST_REQUIRE_SMALL(v2, static_cast<float>(1e-5));
    }
    else
    {
      BOOST_REQUIRE_CLOSE(v1, v2, 0.001);
    }
  }
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_line100_delay50_test )
{
  std::vector<float> data(PROCESSSIZE);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  std::vector<float> ref(PROCESSSIZE);
  for(int64_t i = 50; i < PROCESSSIZE; ++i)
  {
    ref[i] = data[i - 50];
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<float> outdata(PROCESSSIZE);

  ATK::AllPassReverbFilter<float> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(50);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    compare(outdata[i], ref[i]);
  }
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_line25_delay24_feedback_0_5_test )
{
  std::vector<float> data(PROCESSSIZE);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  std::vector<float> ref(PROCESSSIZE);
  for(int64_t i = 0; i < 24; ++i)
  {
    ref[i] = -0.5*data[i];
  }
  for(int64_t i = 24; i < PROCESSSIZE; ++i)
  {
    ref[i] = 0.5 * (ref[i - 24] - data[i]) + data[i - 24];
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<float> outdata(PROCESSSIZE);

  ATK::AllPassReverbFilter<float> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(24);
  filter.set_feedback(0.5);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    compare(outdata[i], ref[i]);
  }
}

BOOST_AUTO_TEST_CASE( AllPassReverbFilter_sinus_line25_delay24_feedback_1_test )
{
  std::vector<float> data(PROCESSSIZE);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  std::vector<float> ref(PROCESSSIZE);
  for(int64_t i = 0; i < 24; ++i)
  {
    ref[i] = -data[i];
  }
  for(int64_t i = 24; i < PROCESSSIZE; ++i)
  {
    ref[i] = (ref[i - 24] - data[i]) + data[i - 24];
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<float> outdata(PROCESSSIZE);

  ATK::AllPassReverbFilter<float> filter(25);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(24);
  filter.set_feedback(.999999);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);

  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    compare(outdata[i], ref[i]);
  }
}
