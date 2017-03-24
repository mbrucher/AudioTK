/**
 * \ file RLSFilter.cpp
 */

#include <ATK/Adaptive/RLSFilter.h>

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

BOOST_AUTO_TEST_CASE(RLSFilter_size_negative_test)
{
  ATK::RLSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_size(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(RLSFilter_size_set_test)
{
  ATK::RLSFilter<float> filter(100);
  filter.set_size(10);
}

BOOST_AUTO_TEST_CASE(RLSFilter_memory_negative_test)
{
  ATK::RLSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( RLSFilter_memory_positive1_test )
{
  ATK::RLSFilter<float> filter(100);
  BOOST_CHECK_THROW(filter.set_memory(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( RLSFilter_memory_99_test )
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::RLSFilter<float> filter(10);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.99);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( RLSFilter_constant_test )
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::SimpleSinusGeneratorFilter<float> reference;
  reference.set_output_sampling_rate(48000);
  reference.set_amplitude(-1);
  reference.set_frequency(1000);

  ATK::RLSFilter<float> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.99);
  Eigen::Matrix<float, Eigen::Dynamic, 1> w(1);
  w << 1;
  filter.set_w(w);

  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  filter.set_input_port(0, &generator, 0);
  sum.set_input_port(0, &reference, 0);
  sum.set_input_port(1, &filter, 0);
  checker.set_input_port(0, &sum, 0);
  
  filter.process(1); // to start everything, the filter is supposed to be one sample late
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( RLSFilter_learning_test )
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::SimpleSinusGeneratorFilter<float> reference;
  reference.set_output_sampling_rate(48000);
  reference.set_amplitude(-1);
  reference.set_frequency(1000);
  
  ATK::RLSFilter<float> filter(10);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(0.9999);
  filter.set_learning(true);
  
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_output_sampling_rate(48000);
  
  std::array<float, PROCESSSIZE> outdata;
  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  
  filter.set_input_port(0, &generator, 0);
  sum.set_input_port(0, &reference, 0);
  sum.set_input_port(1, &filter, 0);
  output.set_input_port(0, &sum, 0);
  
  output.process(PROCESSSIZE);
  
  for(std::int64_t i = 100; i < PROCESSSIZE; ++i) // let the RLS filter start learning first
  {
    BOOST_REQUIRE_SMALL(std::abs(outdata[i]), 0.1f);
  }
}

BOOST_AUTO_TEST_CASE(RLSFilter_learning_training_test)
{
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::SimpleSinusGeneratorFilter<float> reference;
  reference.set_output_sampling_rate(48000);
  reference.set_amplitude(-1);
  reference.set_frequency(1000);

  ATK::RLSFilter<float> filter(10);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(0.9999);
  filter.set_learning(true);

  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_output_sampling_rate(48000);

  std::array<float, PROCESSSIZE> outdata;
  ATK::OutPointerFilter<float> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);

  filter.set_input_port(0, &generator, 0);
  sum.set_input_port(0, &reference, 0);
  sum.set_input_port(1, &filter, 0);
  output.set_input_port(0, &sum, 0);

  output.process(1000);
  filter.set_learning(false);
  output.process(PROCESSSIZE - 1000);

  for (std::int64_t i = 100; i < PROCESSSIZE; ++i) // let the RLS filter start learning first
  {
    BOOST_REQUIRE_SMALL(std::abs(outdata[i]), 0.1f);
  }

}
