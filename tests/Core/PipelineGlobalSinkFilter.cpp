/**
 * \file TypedBaseFilter.cpp
 */

#include <cstdint>

#include <ATK/Core/PipelineGlobalSinkFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( PipelineGlobalSinkFilter_constructor_test )
{
  BOOST_CHECK_NO_THROW(ATK::PipelineGlobalSinkFilter filter);
}

BOOST_AUTO_TEST_CASE( PipelineGlobalSinkFilter_2sinks_first_test )
{
  ATK::TriangleGeneratorFilter<std::int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::int64_t> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_amplitude(1000000);
  checker1.set_frequency(1000);
  checker1.set_input_port(0, &generator, 0);

  ATK::TriangleCheckerFilter<std::int64_t> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_amplitude(1000000);
  checker2.set_frequency(1000);
  checker2.set_input_port(0, &generator, 0);

  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.process(PROCESSSIZE);
  checker1.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PipelineGlobalSinkFilter_2sinks_second_test )
{
  ATK::TriangleGeneratorFilter<std::int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::int64_t> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_amplitude(1000000);
  checker1.set_frequency(1000);
  checker1.set_input_port(0, &generator, 0);

  ATK::TriangleCheckerFilter<std::int64_t> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_amplitude(1000000);
  checker2.set_frequency(1000);
  checker2.set_input_port(0, &generator, 0);

  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.process(PROCESSSIZE);
  checker2.process(PROCESSSIZE);
}
