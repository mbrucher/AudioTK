/**
 * \ file GainExpanderFilter.cpp
 */

#include <ATK/Dynamic/GainExpanderFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 64;

BOOST_AUTO_TEST_CASE( GainExpanderFilter_softness_test )
{
  ATK::GainFilter<ATK::GainExpanderFilter<float>> filter;
  filter.set_softness(0.5);
  BOOST_CHECK_EQUAL(filter.get_softness(), 0.5);
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_softness_range_test )
{
  ATK::GainFilter<ATK::GainExpanderFilter<float>> filter;
  BOOST_CHECK_THROW(filter.set_softness(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_1_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(1, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_0_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.1);
  filter.set_ratio(2);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 0.001f);
  }
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_1_threshold_2_ratio_2_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(2);
  filter.set_softness(1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.700553358, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_1_threshold_2_ratio_4_test )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(4);
  filter.set_softness(1);

  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.343814075, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainExpanderFilter_const_1_threshold_2_ratio_4_test_twice )
{
  std::array<float, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::array<float, PROCESSSIZE> outdata;
  
  ATK::GainFilter<ATK::GainExpanderFilter<float>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(4);
  filter.set_softness(1);
  
  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);
  
  output.process(PROCESSSIZE);
  
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.343814075, outdata[i], 0.1);
  }
  
  generator.set_pointer(data.data(), PROCESSSIZE);
  output.set_pointer(outdata.data(), PROCESSSIZE);
  
  output.process(PROCESSSIZE);
  
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.343814075, outdata[i], 0.1);
  }
}

