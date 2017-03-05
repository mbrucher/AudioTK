/**
 * \ file TriodeFilter.cpp
 */

#include <ATK/Preamplifier/TriodeFilter.h>
#include <ATK/Preamplifier/EnhancedKorenTriodeFunction.h>
#include <ATK/Preamplifier/KorenTriodeFunction.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( TriodeFilter_Koren_0_const )
{
  std::unique_ptr<double[]> data(new double[PROCESSSIZE]);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }
  
  ATK::InPointerFilter<double> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  auto filter = ATK::TriodeFilter<double, ATK::KorenTriodeFunction<double>>::build_standard_filter();
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  
  std::unique_ptr<double[]> outdata(new double[PROCESSSIZE]);
  
  ATK::OutPointerFilter<double> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(int64_t i = 0; i < 50; ++i)
  {
    BOOST_REQUIRE_SMALL(outdata[i], 1e-10);
  }
}
