/**
 * \ file GainMaxCompressorFilter.cpp
 */

#include <iostream>

#include <ATK/Dynamic/GainMaxCompressorFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 64;

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_softness_test )
{
  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter;
  filter.set_softness(0.5);
  BOOST_CHECK_EQUAL(filter.get_softness(), 0.5);
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_softness_range_test )
{
  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter;
  BOOST_CHECK_THROW(filter.set_softness(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_maxreduc_test )
{
  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter;
  filter.set_max_reduction(0.5);
  BOOST_CHECK_EQUAL(filter.get_max_reduction(), 0.5);
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_maxreduc_db_test )
{
  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter;
  filter.set_max_reduction_db(20);
  BOOST_CHECK_EQUAL(filter.get_max_reduction(), 100);
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_maxreduc_range_test )
{
  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter;
  BOOST_CHECK_THROW(filter.set_max_reduction(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_const_1_test )
{
  std::array<double, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(10);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(1, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_const_0_test )
{
  std::array<double, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(outdata[i], 1, 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_const_1_threshold_05_ratio_2_test )
{
  std::array<double, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(2);
  filter.set_softness(1);
  filter.set_max_reduction(0.0001);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.836990714, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_const_1_threshold_05_ratio_4_test )
{
  std::array<double, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(2);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.836990654, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainMaxCompressorFilter_const_1_threshold_05_ratio_4_max_reduction_test )
{
  std::array<double, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainMaxCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(4);
  filter.set_softness(0.0001);
  filter.set_max_reduction(.1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(ptrdiff_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_GE(outdata[i], .1);
  }
}
