/**
 * \file TypedBaseFilter.cpp
 */

#include <complex>
#include <cstdint>

#include <ATK/Core/TypedBaseFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>
#include <ATK/Tools/SumFilter.h>

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

BOOST_AUTO_TEST_CASE(TypedBaseFilter_constructor_test_float)
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<float> filter(0, 0));
}

BOOST_AUTO_TEST_CASE(TypedBaseFilter_constructor_test_double)
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<double> filter(0, 0));
}

BOOST_AUTO_TEST_CASE(TypedBaseFilter_constructor_test_complex_float)
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<std::complex<float>> filter(0, 0));
}

BOOST_AUTO_TEST_CASE(TypedBaseFilter_constructor_test_complex_double)
{
  BOOST_CHECK_NO_THROW(ATK::TypedBaseFilter<std::complex<double>> filter(0, 0));
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_check_out_sampling_rate_test )
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  BOOST_CHECK_THROW(filter.process(100), std::runtime_error);
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

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_input_delay_test )
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  BOOST_CHECK_EQUAL(filter.get_input_delay(), 0);
  filter.set_input_delay(1);
  BOOST_CHECK_EQUAL(filter.get_input_delay(), 1);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_set_output_delay_test )
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  BOOST_CHECK_EQUAL(filter.get_output_delay(), 0);
  filter.set_output_delay(1);
  BOOST_CHECK_EQUAL(filter.get_output_delay(), 1);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline64bits_dryrun_test )
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  generator.dryrun(PROCESSSIZE);
  BOOST_CHECK(generator.get_output_array(0));
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

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline64bits_input_delay_test )
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  checker.set_input_delay(0);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);

  checker.set_input_delay(2);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline_no_such_input_test )
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  BOOST_CHECK_THROW(checker.set_input_port(1, &generator, 0), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline_no_such_output_test )
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  BOOST_CHECK_THROW(checker.set_input_port(0, &generator, 1), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline_bad_sampling_rate_test )
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48001);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  BOOST_CHECK_THROW(checker.set_input_port(0, &generator, 0), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( TypedBaseFilter_pipeline64bits_output_delay_test )
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  generator.set_output_delay(0);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
  
  generator.set_output_delay(2);
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

BOOST_AUTO_TEST_CASE(TypedBaseFilter_int_connect_to_complex_test)
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1 << 30);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::complex<float>> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);

  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(TypedBaseFilter_complex_connect_to_complex_test)
{
  ATK::TriangleGeneratorFilter<std::complex<float>> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(.5);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::complex<float>> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);

  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(TypedBaseFilter_complex_connect_to_int_test)
{
  ATK::TriangleGeneratorFilter<std::complex<float>> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1 << 30);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::int32_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(65536);
  checker.set_frequency(1000);

  checker.set_input_port(0, &generator, 0);
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

BOOST_AUTO_TEST_CASE( TypedBaseFilter_global_latency_throw_test )
{
  ATK::TriangleCheckerFilter<float> checker;
  
  BOOST_CHECK_THROW(checker.get_global_latency(), std::runtime_error);
}

#if ATK_USE_THREADPOOL == 1
BOOST_AUTO_TEST_CASE(TypedBaseFilter_parallel)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);

  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  sumfilter.set_output_sampling_rate(48000);

  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(3);
  checker.set_frequency(1000);

  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &generator2, 0);
  checker.set_input_port(0, &sumfilter, 0);
  checker.process_parallel(PROCESSSIZE);
}
#endif

