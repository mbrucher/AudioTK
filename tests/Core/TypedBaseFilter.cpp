/**
 * \file TypedBaseFilter.cpp
 */

#include <cstdint>

#include <ATK/Core/TypedBaseFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int16_t )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<std::int16_t> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int32_t )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<std::int32_t> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_int64_t )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<int64_t> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_float )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<float> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_constructor_test_double )
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<double> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_int16_t )
{
  ATK::TypedBaseFilter<std::int16_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_EQUAL(filter.get_nb_input_ports(), 0);
  BOOST_CHECK_EQUAL(filter.get_nb_output_ports(), 0);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_int32_t )
{
  ATK::TypedBaseFilter<std::int32_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_int64_t )
{
  ATK::TypedBaseFilter<int64_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_float )
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_sampling_rate_test_double )
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_input_sampling_rate(), 44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_int16_t )
{
  ATK::TypedBaseFilter<std::int16_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_int32_t )
{
  ATK::TypedBaseFilter<std::int32_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_int64_t )
{
  ATK::TypedBaseFilter<int64_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_float )
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_sampling_rate_test_double )
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  BOOST_CHECK_EQUAL(filter.get_output_sampling_rate(), 44100);
  BOOST_CHECK_NE(filter.get_input_sampling_rate(), 44100);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline64bits_triangle_test )
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline32bits_triangle_test )
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<std::int32_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline64bitsfloat_triangle_test )
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1<<30);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_throw_triangle_test )
{
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  BOOST_CHECK_THROW(checker.process(PROCESSSIZE), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_latency_set_test )
{
  ATK::TriangleCheckerFilter<int64_t> checker;
  BOOST_CHECK_EQUAL(checker.get_latency(), 0);
  checker.set_latency(1);
  BOOST_CHECK_EQUAL(checker.get_latency(), 1);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_global_latency_test )
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_port(0, &generator, 0);

  BOOST_CHECK_EQUAL(checker.get_global_latency(), 0);
  checker.set_latency(1);
  BOOST_CHECK_EQUAL(checker.get_global_latency(), 1);
  generator.set_latency(2);
  BOOST_CHECK_EQUAL(checker.get_global_latency(), 3);
}
