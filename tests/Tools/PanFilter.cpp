/**
 * \ file PanFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/PanFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_MODULE ATKTools_test
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1024*1024)

BOOST_AUTO_TEST_CASE( PanFilter_center_sincos_0_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(1);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_sincos_0_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(1);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_sincos_0_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(std::sqrt(2.));
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_sincos_0_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(0);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_sincos_0_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(0);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_sincos_0_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(std::sqrt(2.));
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_sincos_3_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::SINCOS_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(1 / std::sqrt(2));
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_sincos_3_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::SINCOS_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(1 / std::sqrt(2));
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_sincos_3_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SINCOS_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_sincos_3_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SINCOS_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(0);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_sincos_3_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SINCOS_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(0);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_sincos_3_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SINCOS_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_square_0_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_0_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(1);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_square_0_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_0_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(1);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_square_0_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_0_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(std::sqrt(2.));
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_square_0_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_0_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(0);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_square_0_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_0_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(0);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_square_0_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_0_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(std::sqrt(2.));
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_square_3_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(1 / std::sqrt(2));
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_square_3_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(1 / std::sqrt(2));
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_square_3_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_square_3_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(0);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_square_3_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(0);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_square_3_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::SQUARE_3_CENTER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_linear_taper_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::LINEAR_TAPER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(.5);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_linear_taper_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::LINEAR_TAPER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(.5);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_linear_taper_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::LINEAR_TAPER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(1);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_linear_taper_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::LINEAR_TAPER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(0);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_linear_taper_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::LINEAR_TAPER);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(0);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_linear_taper_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::LINEAR_TAPER);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(1);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_balance_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::BALANCE);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(1);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_center_balance_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan_law(ATK::PanFilter<double>::BALANCE);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(1);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_balance_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::BALANCE);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_left_balance_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(-1);
  panfilter.set_pan_law(ATK::PanFilter<double>::BALANCE);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_amplitude(0);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_balance_left_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::BALANCE);
  
  ATK::TriangleCheckerFilter<double> checker_l;
  checker_l.set_input_sampling_rate(48000);
  checker_l.set_amplitude(0);
  checker_l.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_l.set_input_port(0, &panfilter, 0);
  checker_l.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( PanFilter_right_balance_right_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::PanFilter<double> panfilter;
  panfilter.set_input_sampling_rate(48000);
  panfilter.set_output_sampling_rate(48000);
  panfilter.set_pan(1);
  panfilter.set_pan_law(ATK::PanFilter<double>::BALANCE);
  
  ATK::TriangleCheckerFilter<double> checker_r;
  checker_r.set_input_sampling_rate(48000);
  checker_r.set_frequency(1000);
  
  panfilter.set_input_port(0, &generator, 0);
  checker_r.set_input_port(0, &panfilter, 1);
  checker_r.process(PROCESSSIZE);
}
