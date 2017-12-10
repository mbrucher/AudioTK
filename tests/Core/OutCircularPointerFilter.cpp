/**
 * \ file OutCircularPointerFilter.cpp
 */

#include <cmath>

#include <boost/math/constants/constants.hpp>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutCircularPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (512)

BOOST_AUTO_TEST_CASE( OutCircularPointerFloat_sin1k_test )
{
  std::array<float, PROCESSSIZE*200> data;
  for(ptrdiff_t i = 0; i < PROCESSSIZE*200; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 1, data.size(), false);
  generator.set_output_sampling_rate(48000);

  ATK::OutCircularPointerFilter<float> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  
  auto nb_iterations = 4 + ATK::OutCircularPointerFilter<float>::slice_size * ATK::OutCircularPointerFilter<float>::nb_slices / PROCESSSIZE;
  auto max_zero = std::max(0, int(ATK::OutCircularPointerFilter<float>::out_slice_size));
  auto offset = 0;
  
  for(int i = 0; i < nb_iterations; ++i)
  {
    output.process(PROCESSSIZE);
    bool process;
    const auto& outdata = output.get_last_slice(process);
    
    if(process && i!=0)
    {
      max_zero = std::max(0, int(ATK::OutCircularPointerFilter<float>::out_slice_size - (i+1) * PROCESSSIZE));
      offset = std::max(0, (i+1) * PROCESSSIZE - int(ATK::OutCircularPointerFilter<float>::out_slice_size)) - max_zero ;
    }
    for(ptrdiff_t j = 0; j < max_zero; ++j)
    {
      BOOST_REQUIRE_EQUAL(outdata[j], 0);
    }
    for(ptrdiff_t j = max_zero; j < outdata.size(); ++j)
    {
      BOOST_REQUIRE_EQUAL(outdata[j], data[j + offset]);
    }
  }
}
