/**
 * \file BoradcastReduceFilter.cpp
 */

#include <complex>
#include <cstdint>

#include <simdpp/simd.h>

#include <ATK/Tools/SIMD/BroadcastFilter.h>
#include <ATK/Tools/SIMD/ReduceFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Core/PipelineGlobalSinkFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(SIMDPP_ARCH_NAMESPACE, BroadcastReduceFilter_triangle_real_to_real_test))
{
  ATK::TriangleGeneratorFilter<float> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_frequency(1000);
  generator1.set_amplitude(1);

  ATK::BroadcastFilter<float, simdpp::float32<4> > converter1;
  converter1.set_input_sampling_rate(48000);
  converter1.set_output_sampling_rate(48000);

  ATK::ReduceFilter<simdpp::float32<4>, float > converter2;
  converter2.set_input_sampling_rate(48000);
  converter2.set_output_sampling_rate(48000);

  ATK::TriangleCheckerFilter<float> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_frequency(1000);
  checker1.set_amplitude(4);

  converter1.set_input_port(0, &generator1, 0);
  converter2.set_input_port(0, &converter1, 0);
  checker1.set_input_port(0, &converter2, 0);
  checker1.process(PROCESSSIZE);
}

#ifdef SIMDPP_EMIT_DISPATCHER
BOOST_AUTO_TEST_CASE(BroadcastReduceFilter_triangle_real_to_real_test)
{
  ATK::TriangleGeneratorFilter<float> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_frequency(1000);
  generator1.set_amplitude(1);
  
  std::unique_ptr<ATK::BaseFilter> converter1 = ATK::createBroadcastFilter<float, 4>();
  converter1->set_input_sampling_rate(48000);
  converter1->set_output_sampling_rate(48000);
  
  std::unique_ptr<ATK::BaseFilter> converter2 = ATK::createReduceFilter<float, 4>();
  converter2->set_input_sampling_rate(48000);
  converter2->set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<float> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_frequency(1000);
  checker1.set_amplitude(4);
  
  converter1->set_input_port(0, &generator1, 0);
  converter2->set_input_port(0, converter1.get(), 0);
  checker1.set_input_port(0, converter2.get(), 0);
  checker1.process(PROCESSSIZE);
}
#endif
