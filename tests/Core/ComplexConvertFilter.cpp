/**
 * \file ComplexConvertFilter.cpp
 */

#include <complex>
#include <cstdint>

#include <ATK/Core/ComplexConvertFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Core/PipelineGlobalSinkFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( ConvertBasedFilter_triangle_real_to_complex_test )
{
  ATK::TriangleGeneratorFilter<float> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(1000);
  
  ATK::RealToComplexFilter<float> converter;
  converter.set_input_sampling_rate(48000);
  converter.set_output_sampling_rate(48000);

  ATK::TriangleCheckerFilter<std::complex<float>> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_frequency(1000);
  checker.set_amplitude(std::complex<float>(1,1));
  
  converter.set_input_port(0, &generator, 0);
  converter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &converter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE(ConvertBasedFilter_triangle_complex_to_real_test)
{
  ATK::TriangleGeneratorFilter<std::complex<float>> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(1000);
  generator.set_amplitude(std::complex<float>(1, 1));

  ATK::ComplexToRealFilter<float> converter;
  converter.set_input_sampling_rate(48000);
  converter.set_output_sampling_rate(48000);

  ATK::TriangleCheckerFilter<float> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_frequency(1000);
  ATK::TriangleCheckerFilter<float> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_frequency(1000);

  converter.set_input_port(0, &generator, 0);
  checker1.set_input_port(0, &converter, 0);
  checker2.set_input_port(0, &converter, 1);
  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.process(PROCESSSIZE);
}
