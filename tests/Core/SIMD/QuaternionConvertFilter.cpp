/**
 * \file QuaternionConvertFilter.cpp
 */

#include <complex>
#include <cstdint>

#include <simdpp/simd.h>

#include <ATK/Core/SIMD/QuaternionConvertFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Core/PipelineGlobalSinkFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(SIMDPP_ARCH_NAMESPACE, QuaternionBasedFilter_triangle_real_to_real_test))
{
  ATK::TriangleGeneratorFilter<float> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_frequency(1000);
  generator1.set_amplitude(1);
  ATK::TriangleGeneratorFilter<float> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_frequency(10000);
  generator2.set_amplitude(.5);
  ATK::TriangleGeneratorFilter<float> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_frequency(100);
  generator3.set_amplitude(5);
  ATK::TriangleGeneratorFilter<float> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_frequency(1000);
  generator4.set_amplitude(10);

  ATK::RealToQuaternionFilter<float, simdpp::float32<4> > converter1;
  converter1.set_input_sampling_rate(48000);
  converter1.set_output_sampling_rate(48000);

  ATK::QuaternionToRealFilter<simdpp::float32<4>, float > converter2;
  converter2.set_input_sampling_rate(48000);
  converter2.set_output_sampling_rate(48000);

  ATK::TriangleCheckerFilter<float> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_frequency(1000);
  checker1.set_amplitude(1);
  ATK::TriangleCheckerFilter<float> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_frequency(10000);
  checker2.set_amplitude(.5);
  ATK::TriangleCheckerFilter<float> checker3;
  checker3.set_input_sampling_rate(48000);
  checker3.set_frequency(100);
  checker3.set_amplitude(5);
  ATK::TriangleCheckerFilter<float> checker4;
  checker4.set_input_sampling_rate(48000);
  checker4.set_frequency(1000);
  checker4.set_amplitude(10);

  converter1.set_input_port(0, &generator1, 0);
  converter1.set_input_port(1, &generator2, 0);
  converter1.set_input_port(2, &generator3, 0);
  converter1.set_input_port(3, &generator4, 0);
  
  converter2.set_input_port(0, &converter1, 0);
  
  checker1.set_input_port(0, &converter2, 0);
  checker2.set_input_port(0, &converter2, 1);
  checker3.set_input_port(0, &converter2, 2);
  checker4.set_input_port(0, &converter2, 3);
  
  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.add_filter(&checker3);
  globalsink.add_filter(&checker4);
  globalsink.process(PROCESSSIZE);
}

#ifdef SIMDPP_EMIT_DISPATCHER
BOOST_AUTO_TEST_CASE(QuaternionBasedFilter_triangle_real_to_real_test)
{
  ATK::TriangleGeneratorFilter<float> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_frequency(1000);
  generator1.set_amplitude(1);
  ATK::TriangleGeneratorFilter<float> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_frequency(10000);
  generator2.set_amplitude(.5);
  ATK::TriangleGeneratorFilter<float> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_frequency(100);
  generator3.set_amplitude(5);
  ATK::TriangleGeneratorFilter<float> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_frequency(1000);
  generator4.set_amplitude(10);
  
  std::unique_ptr<ATK::BaseFilter> converter1 = ATK::createRealToQuaternionFilter<float>(1);
  converter1->set_input_sampling_rate(48000);
  converter1->set_output_sampling_rate(48000);
  
  std::unique_ptr<ATK::BaseFilter> converter2 = ATK::createQuaternionToRealFilter<float>(1);
  converter2->set_input_sampling_rate(48000);
  converter2->set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<float> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_frequency(1000);
  checker1.set_amplitude(1);
  ATK::TriangleCheckerFilter<float> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_frequency(10000);
  checker2.set_amplitude(.5);
  ATK::TriangleCheckerFilter<float> checker3;
  checker3.set_input_sampling_rate(48000);
  checker3.set_frequency(100);
  checker3.set_amplitude(5);
  ATK::TriangleCheckerFilter<float> checker4;
  checker4.set_input_sampling_rate(48000);
  checker4.set_frequency(1000);
  checker4.set_amplitude(10);
  
  converter1->set_input_port(0, &generator1, 0);
  converter1->set_input_port(1, &generator2, 0);
  converter1->set_input_port(2, &generator3, 0);
  converter1->set_input_port(3, &generator4, 0);
  
  converter2->set_input_port(0, converter1.get(), 0);
  
  checker1.set_input_port(0, converter2.get(), 0);
  checker2.set_input_port(0, converter2.get(), 1);
  checker3.set_input_port(0, converter2.get(), 2);
  checker4.set_input_port(0, converter2.get(), 3);
  
  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.add_filter(&checker3);
  globalsink.add_filter(&checker4);
  globalsink.process(PROCESSSIZE);
}
#endif
