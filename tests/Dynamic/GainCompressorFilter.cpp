/**
 * \ file GainCompressorFilter.cpp
 */

#include <ATK/Dynamic/GainCompressorFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 64;

BOOST_AUTO_TEST_CASE( GainFilter_threshold_test )
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_threshold(10);
  BOOST_CHECK_EQUAL(filter.get_threshold(), 10);
}

BOOST_AUTO_TEST_CASE( GainFilter_threshold_db_test )
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_threshold_db(20);
  BOOST_CHECK_EQUAL(filter.get_threshold(), 100);
}

BOOST_AUTO_TEST_CASE( GainFilter_threshold_range_test )
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  BOOST_CHECK_THROW(filter.set_threshold(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( GainFilter_ratio_test )
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_ratio(10);
  BOOST_CHECK_EQUAL(filter.get_ratio(), 10);
}

BOOST_AUTO_TEST_CASE( GainFilter_ratio_range_test )
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  BOOST_CHECK_THROW(filter.set_ratio(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( GainCompressorFilter_softness_test )
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_softness(0.5);
  BOOST_CHECK_EQUAL(filter.get_softness(), 0.5);
}

BOOST_AUTO_TEST_CASE( GainCompressorFilter_softness_range_test )
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  BOOST_CHECK_THROW(filter.set_softness(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( GainCompressorFilter_const_1_test )
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(10);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(1, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainCompressorFilter_const_0_test )
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(1, outdata[i], 0.1); // if input is zero, we still need a gain of 1 to have a progression of 1 for values < threshold
  }
}

BOOST_AUTO_TEST_CASE( GainCompressorFilter_const_1_threshold_05_ratio_2_test )
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(2);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.836990654, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE(GainCompressorFilter_const_1_threshold_05_ratio_2_test_LUT)
{
  std::array<double, PROCESSSIZE> data;
  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(2);
  filter.set_softness(1);
  filter.wait_for_LUT_completion();

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.836990654, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE( GainCompressorFilter_const_1_threshold_05_ratio_4_test )
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(4);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.765739262, outdata[i], 0.1);
  }
}

BOOST_AUTO_TEST_CASE(GainCompressorFilter_const_1_threshold_05_ratio_4_test_LUT)
{
  std::array<double, PROCESSSIZE> data;
  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(4);
  filter.set_softness(1);
  filter.wait_for_LUT_completion();

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(0.765739262, outdata[i], 0.1);
  }
}
