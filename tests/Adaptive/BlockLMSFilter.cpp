/**
 * \ file BlockLMSFilter.cpp
 */

#include <array>
#include <fstream>
#include <iostream>

#include <ATK/Adaptive/BlockLMSFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <Eigen/Core>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1200;

BOOST_AUTO_TEST_CASE(BlockLMSFilter_destructor_test)
{
  BOOST_CHECK_NO_THROW(std::make_unique<ATK::BlockLMSFilter<double>>(100));
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_size_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  BOOST_CHECK_THROW(filter.set_size(0), ATK::RuntimeError);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_size_set_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_size(10);
  BOOST_CHECK_EQUAL(filter.get_size(), 10);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_build_throw_test)
{
  BOOST_CHECK_THROW(ATK::BlockLMSFilter<double> filter(0), ATK::RuntimeError);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_blocksize_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  BOOST_CHECK_THROW(filter.set_block_size(0), ATK::RuntimeError);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_blocksize_set_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_block_size(10);
  BOOST_CHECK_EQUAL(filter.get_block_size(), 10);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_memory_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(0), ATK::RuntimeError);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_memory_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_memory(0.5);
  BOOST_CHECK_EQUAL(filter.get_memory(), 0.5);
}

BOOST_AUTO_TEST_CASE( BlockLMSFilter_memory_positive1_test )
{
  ATK::BlockLMSFilter<double> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(1), ATK::RuntimeError);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_mu_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  BOOST_CHECK_THROW(filter.set_mu(0), ATK::RuntimeError);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_mu_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_mu(0.5);
  BOOST_CHECK_EQUAL(filter.get_mu(), 0.5);
}

BOOST_AUTO_TEST_CASE( BlockLMSFilter_mu_positive1_test )
{
  ATK::BlockLMSFilter<double> filter(100);
  BOOST_CHECK_THROW(filter.set_mu(1), ATK::RuntimeError);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_learning_set_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  BOOST_CHECK_EQUAL(filter.get_learning(), true);
  filter.set_learning(false);
  BOOST_CHECK_EQUAL(filter.get_learning(), false);
}

BOOST_AUTO_TEST_CASE( BlockLMSFilter_memory_999_test )
{
  std::array<double, PROCESSSIZE> data;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_lms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.data()), PROCESSSIZE * sizeof(double));
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  ATK::BlockLMSFilter<double> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.999);
  filter.set_mu(.0001);

  std::array<double, PROCESSSIZE> outdata;
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_output_sampling_rate(48000);

  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  output.set_input_port(0, &filter, 0);

  filter.process(100);
  output.process(PROCESSSIZE);
  BOOST_CHECK_NE(filter.get_w(), nullptr);

  std::array<double, PROCESSSIZE> ref;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_blocklms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(ref.data()), PROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(outdata[i], ref[i], 0.0001);
  }
}
