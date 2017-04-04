/**
 * \ file BlockLMSFilter.cpp
 */

#include <ATK/Adaptive/BlockLMSFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <Eigen/Core>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#define PROCESSSIZE (1024)

BOOST_AUTO_TEST_CASE(BlockLMSFilter_size_negative_test)
{
  ATK::BlockLMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_size(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_size_set_test)
{
  ATK::BlockLMSFilter<float> filter(100);
  filter.set_size(10);
}

BOOST_AUTO_TEST_CASE(BlockLMSFilter_memory_negative_test)
{
  ATK::BlockLMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( BlockLMSFilter_memory_positive1_test )
{
  ATK::BlockLMSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( BlockLMSFilter_memory_99_test )
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::BlockLMSFilter<float> filter(10);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.99);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  //checker.process(PROCESSSIZE);
}
