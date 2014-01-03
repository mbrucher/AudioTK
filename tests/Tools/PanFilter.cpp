/**
 * \ file PanFilter.cpp
 */

#include <ATK/Tools/PanFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_MODULE ATKTools_test
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE( PanFilter_center_default_test )
{
  ATK::TriangleGeneratorFilter generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::PanFilter<std::int64_t> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(1000000);
  checker_l.set_frequency(1000);
  ATK::TriangleCheckerFilter checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(1000000);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(1024*1024);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(1024*1024);
}

