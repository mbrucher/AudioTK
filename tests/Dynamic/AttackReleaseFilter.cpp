/**
 * \ file AttackReleaseFilter.cpp
 */

#include <ATK/Dynamic/AttackReleaseFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;

BOOST_AUTO_TEST_CASE( AttackRelease_attack_test )
{
  ATK::AttackReleaseFilter<double> filter;
  filter.set_attack(0.5);
  BOOST_CHECK_EQUAL(filter.get_attack(), 0.5);
}

BOOST_AUTO_TEST_CASE( AttackRelease_attack_range_test )
{
  ATK::AttackReleaseFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_attack(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackRelease_attack_range2_test )
{
  ATK::AttackReleaseFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_attack(1.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackRelease_release_test )
{
  ATK::AttackReleaseFilter<double> filter;
  filter.set_release(0.5);
  BOOST_CHECK_EQUAL(filter.get_release(), 0.5);
}

BOOST_AUTO_TEST_CASE( AttackRelease_release_range_test )
{
  ATK::AttackReleaseFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_release(-0.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackRelease_release_range2_test )
{
  ATK::AttackReleaseFilter<double> filter;
  BOOST_CHECK_THROW(filter.set_release(1.000001), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AttackReleaseFilter_triangle_test )
{
  std::array<double, PROCESSSIZE> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE/2; ++i)
  {
    data[i] = i / 48000;
  }
  for(ptrdiff_t i = 0; i < PROCESSSIZE/2; ++i)
  {
    data[PROCESSSIZE/2 + i] = (PROCESSSIZE/2 - i) / 48000;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::AttackReleaseFilter<double> filter(1);
  filter.set_attack(std::exp(-1./(48000 * 1e-3)));
  filter.set_release(std::exp(-1./(48000 * 100e-3)));
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(ptrdiff_t i = 0; i < PROCESSSIZE/2; ++i)
  {
    BOOST_REQUIRE_GE(data[i], outdata[i]);
  }
  for(ptrdiff_t i = 0; i < PROCESSSIZE/2; ++i)
  {
    BOOST_REQUIRE_GE(outdata[PROCESSSIZE/2+i], outdata[PROCESSSIZE/2+i-1]);
  }
}
