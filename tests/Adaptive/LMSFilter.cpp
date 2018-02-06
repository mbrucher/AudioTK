/**
 * \ file LMSFilter.cpp
 */

#include <array>
#include <fstream>

#include <ATK/Adaptive/LMSFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <Eigen/Core>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

const size_t PROCESSSIZE = 1200;

BOOST_AUTO_TEST_CASE(LMSFilter_size_negative_test)
{
  ATK::LMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_size(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(LMSFilter_size_set_test)
{
  ATK::LMSFilter<float> filter(100);
  filter.set_size(10);
  BOOST_CHECK_EQUAL(filter.get_size(), 10);
}

BOOST_AUTO_TEST_CASE(LMSFilter_mode_set_test)
{
  ATK::LMSFilter<float> filter(100);
  filter.set_mode(ATK::LMSFilter<float>::Mode::NORMALIZED);
  BOOST_CHECK(filter.get_mode() == ATK::LMSFilter<float>::Mode::NORMALIZED);
}

BOOST_AUTO_TEST_CASE(LMSFilter_memory_negative_test)
{
  ATK::LMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(LMSFilter_memory_test)
{
  ATK::LMSFilter<float> filter(100);
  filter.set_memory(0.5);
  BOOST_CHECK_EQUAL(filter.get_memory(), 0.5);
}

BOOST_AUTO_TEST_CASE( LMSFilter_memory_positive1_test )
{
  ATK::LMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(LMSFilter_mu_negative_test)
{
  ATK::LMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_mu(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(LMSFilter_mu_test)
{
  ATK::LMSFilter<float> filter(100);
  filter.set_mu(0.5);
  BOOST_CHECK_EQUAL(filter.get_mu(), 0.5);
}

BOOST_AUTO_TEST_CASE( LMSFilter_mu_positive1_test )
{
  ATK::LMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_mu(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(LMSFilter_learning_set_test)
{
  ATK::LMSFilter<float> filter(100);
  BOOST_CHECK_EQUAL(filter.get_learning(), true);
  filter.set_learning(false);
  BOOST_CHECK_EQUAL(filter.get_learning(), false);
}

BOOST_AUTO_TEST_CASE( LMSFilter_memory_99_test )
{
  std::array<double, PROCESSSIZE> data;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_lms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.data()), PROCESSSIZE * sizeof(double));
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  ATK::LMSFilter<double> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.999);
  filter.set_mu(.01);
  
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(PROCESSSIZE);

  std::array<double, PROCESSSIZE> outdata;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_lms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(outdata.data()), PROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(outdata[i], filter.get_output_array(0)[i], 0.0001);
  }
}
