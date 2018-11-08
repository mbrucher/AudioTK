/**
 * \ file AttackReleaseHysteresisFilter.cpp
 */

#include <ATK/Dynamic/AttackReleaseHysteresisFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_attack_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  filter.set_attack(0.5);
  BOOST_CHECK_EQUAL(filter.get_attack(), 0.5);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_attack_range_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_attack(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_attack_range2_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_attack(1.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_release_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  filter.set_release(0.5);
  BOOST_CHECK_EQUAL(filter.get_release(), 0.5);
}

BOOST_AUTO_TEST_CASE( AttackRelease_Hysteresisrelease_range_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_release(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_release_range2_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_release(1.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_attack_hysteresis_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  filter.set_release_hysteresis(0.1);
  filter.set_attack_hysteresis(0.5);
  BOOST_CHECK_EQUAL(filter.get_attack_hysteresis(), 0.5);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_attack_hysteresis_db_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  filter.set_release_hysteresis(0.001);
  filter.set_attack_hysteresis_db(-20);
  BOOST_CHECK_CLOSE(filter.get_attack_hysteresis(), 0.1, 0.1);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_attack_hysteresis_range_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  filter.set_release_hysteresis(.5);
  BOOST_CHECK_THROW(filter.set_attack_hysteresis(.5-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_attack_hysteresis_range2_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_attack_hysteresis(1.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_hysteresis_release_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  filter.set_release_hysteresis(0.5);
  BOOST_CHECK_EQUAL(filter.get_release_hysteresis(), 0.5);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_release_hysteresis_db_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  filter.set_release_hysteresis_db(-20);
  BOOST_CHECK_CLOSE(filter.get_release_hysteresis(), 0.1, 0.1);
}

BOOST_AUTO_TEST_CASE( AttackRelease_Hysteresisrelease_hysteresis_range_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_release_hysteresis(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresis_release_hysteresis_range2_test )
{
  ATK::AttackReleaseHysteresisFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_release_hysteresis(1.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresisFilter_triangle_test )
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    data[i] = i / 48000;
  }
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    data[PROCESSSIZE/2 + i] = (PROCESSSIZE/2 - i) / 48000;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::AttackReleaseHysteresisFilter<double> filter(1);
  filter.set_attack(std::exp(-1./(48000 * 1e-3)));
  filter.set_release(std::exp(-1./(48000 * 100e-3)));
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    BOOST_REQUIRE_GE(data[i], outdata[i]);
  }
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    BOOST_REQUIRE_GE(outdata[PROCESSSIZE/2+i], outdata[PROCESSSIZE/2+i-1]);
  }
}

#define CUSTOMPROCESSSIZE 7

BOOST_AUTO_TEST_CASE( AttackReleaseHysteresisFilter_release_custom_test )
{
  double data[] = {0., 1., .5, .4, .3, .2, .1};
  double target[] = {0., 1., 1., .46, .46, .226, .1126};
  
  ATK::InPointerFilter<double> generator(data, 1, CUSTOMPROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::array<double, CUSTOMPROCESSSIZE> outdata;
  
  ATK::AttackReleaseHysteresisFilter<double> filter(1);
  filter.set_attack(0);
  filter.set_release(.1);
  filter.set_release_hysteresis(.5);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  
  ATK::OutPointerFilter<double> output(outdata.data(), 1, CUSTOMPROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);
  
  output.process(CUSTOMPROCESSSIZE);
  
  for(gsl::index i = 0; i < CUSTOMPROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_CLOSE(target[i], outdata[i], .001);
  }
}
