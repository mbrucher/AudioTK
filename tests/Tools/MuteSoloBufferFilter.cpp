/**
 * \ file MuteSoloBufferFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/MuteSoloBufferFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

constexpr gsl::index PROCESSSIZE = 1024;

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_mute_test )
{
  ATK::MuteSoloBufferFilter<double> bufferfilter;
  BOOST_CHECK_EQUAL(bufferfilter.get_mute(0), false);
  bufferfilter.set_mute(0, true);
  BOOST_CHECK_EQUAL(bufferfilter.get_mute(0), true);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_solo_test )
{
  ATK::MuteSoloBufferFilter<double> bufferfilter;
  BOOST_CHECK_EQUAL(bufferfilter.get_solo(0), false);
  bufferfilter.set_solo(0, true);
  BOOST_CHECK_EQUAL(bufferfilter.get_solo(0), true);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_input_ports_test )
{
  ATK::MuteSoloBufferFilter<double> bufferfilter;
  BOOST_CHECK_THROW(bufferfilter.set_nb_input_ports(10), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_output_ports_test )
{
  ATK::MuteSoloBufferFilter<double> bufferfilter;
  BOOST_CHECK_THROW(bufferfilter.set_nb_output_ports(10), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_test )
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::MuteSoloBufferFilter<double> bufferfilter;
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &bufferfilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_multipleon_test )
{
  ATK::TriangleGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_amplitude(4);
  generator3.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_amplitude(8);
  generator4.set_frequency(1000);
  
  ATK::MuteSoloBufferFilter<double> bufferfilter(4);
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  
  ATK::SumFilter<double> sumFilter(1, 4);
  sumFilter.set_input_sampling_rate(48000);
  sumFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(15);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator1, 0);
  bufferfilter.set_input_port(1, &generator2, 0);
  bufferfilter.set_input_port(2, &generator3, 0);
  bufferfilter.set_input_port(3, &generator4, 0);
  sumFilter.set_input_port(0, &bufferfilter, 0);
  sumFilter.set_input_port(1, &bufferfilter, 1);
  sumFilter.set_input_port(2, &bufferfilter, 2);
  sumFilter.set_input_port(3, &bufferfilter, 3);
  checker.set_input_port(0, &sumFilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_multiple_one_mute_test )
{
  ATK::TriangleGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_amplitude(4);
  generator3.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_amplitude(8);
  generator4.set_frequency(1000);
  
  ATK::MuteSoloBufferFilter<double> bufferfilter(4);
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  bufferfilter.set_mute(2, true);
  
  ATK::SumFilter<double> sumFilter(1, 4);
  sumFilter.set_input_sampling_rate(48000);
  sumFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(11);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator1, 0);
  bufferfilter.set_input_port(1, &generator2, 0);
  bufferfilter.set_input_port(2, &generator3, 0);
  bufferfilter.set_input_port(3, &generator4, 0);
  sumFilter.set_input_port(0, &bufferfilter, 0);
  sumFilter.set_input_port(1, &bufferfilter, 1);
  sumFilter.set_input_port(2, &bufferfilter, 2);
  sumFilter.set_input_port(3, &bufferfilter, 3);
  checker.set_input_port(0, &sumFilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_multiple_one_mute2_test )
{
  ATK::TriangleGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_amplitude(4);
  generator3.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_amplitude(8);
  generator4.set_frequency(1000);
  
  ATK::MuteSoloBufferFilter<double> bufferfilter(4);
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  bufferfilter.set_mute(2, true);
  bufferfilter.set_mute(2, false);
  
  ATK::SumFilter<double> sumFilter(1, 4);
  sumFilter.set_input_sampling_rate(48000);
  sumFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(15);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator1, 0);
  bufferfilter.set_input_port(1, &generator2, 0);
  bufferfilter.set_input_port(2, &generator3, 0);
  bufferfilter.set_input_port(3, &generator4, 0);
  sumFilter.set_input_port(0, &bufferfilter, 0);
  sumFilter.set_input_port(1, &bufferfilter, 1);
  sumFilter.set_input_port(2, &bufferfilter, 2);
  sumFilter.set_input_port(3, &bufferfilter, 3);
  checker.set_input_port(0, &sumFilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_multiple_one_solo_test )
{
  ATK::TriangleGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_amplitude(4);
  generator3.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_amplitude(8);
  generator4.set_frequency(1000);
  
  ATK::MuteSoloBufferFilter<double> bufferfilter(4);
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  bufferfilter.set_solo(2, true);
  
  ATK::SumFilter<double> sumFilter(1, 4);
  sumFilter.set_input_sampling_rate(48000);
  sumFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(4);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator1, 0);
  bufferfilter.set_input_port(1, &generator2, 0);
  bufferfilter.set_input_port(2, &generator3, 0);
  bufferfilter.set_input_port(3, &generator4, 0);
  sumFilter.set_input_port(0, &bufferfilter, 0);
  sumFilter.set_input_port(1, &bufferfilter, 1);
  sumFilter.set_input_port(2, &bufferfilter, 2);
  sumFilter.set_input_port(3, &bufferfilter, 3);
  checker.set_input_port(0, &sumFilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_multiple_one_solo2_test )
{
  ATK::TriangleGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_amplitude(4);
  generator3.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_amplitude(8);
  generator4.set_frequency(1000);
  
  ATK::MuteSoloBufferFilter<double> bufferfilter(4);
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  bufferfilter.set_solo(2, true);
  bufferfilter.set_solo(2, false);
  
  ATK::SumFilter<double> sumFilter(1, 4);
  sumFilter.set_input_sampling_rate(48000);
  sumFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(15);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator1, 0);
  bufferfilter.set_input_port(1, &generator2, 0);
  bufferfilter.set_input_port(2, &generator3, 0);
  bufferfilter.set_input_port(3, &generator4, 0);
  sumFilter.set_input_port(0, &bufferfilter, 0);
  sumFilter.set_input_port(1, &bufferfilter, 1);
  sumFilter.set_input_port(2, &bufferfilter, 2);
  sumFilter.set_input_port(3, &bufferfilter, 3);
  checker.set_input_port(0, &sumFilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_multiple_dual_solo_test )
{
  ATK::TriangleGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_amplitude(4);
  generator3.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_amplitude(8);
  generator4.set_frequency(1000);
  
  ATK::MuteSoloBufferFilter<double> bufferfilter(4);
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  bufferfilter.set_solo(0, true);
  bufferfilter.set_solo(2, true);
  
  ATK::SumFilter<double> sumFilter(1, 4);
  sumFilter.set_input_sampling_rate(48000);
  sumFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(5);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator1, 0);
  bufferfilter.set_input_port(1, &generator2, 0);
  bufferfilter.set_input_port(2, &generator3, 0);
  bufferfilter.set_input_port(3, &generator4, 0);
  sumFilter.set_input_port(0, &bufferfilter, 0);
  sumFilter.set_input_port(1, &bufferfilter, 1);
  sumFilter.set_input_port(2, &bufferfilter, 2);
  sumFilter.set_input_port(3, &bufferfilter, 3);
  checker.set_input_port(0, &sumFilter, 0);
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( MuteSoloBufferFilter_multiple_one_mutesolo_test )
{
  ATK::TriangleGeneratorFilter<double> generator1;
  generator1.set_output_sampling_rate(48000);
  generator1.set_amplitude(1);
  generator1.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator3;
  generator3.set_output_sampling_rate(48000);
  generator3.set_amplitude(4);
  generator3.set_frequency(1000);
  
  ATK::TriangleGeneratorFilter<double> generator4;
  generator4.set_output_sampling_rate(48000);
  generator4.set_amplitude(8);
  generator4.set_frequency(1000);
  
  ATK::MuteSoloBufferFilter<double> bufferfilter(4);
  bufferfilter.set_input_sampling_rate(48000);
  bufferfilter.set_output_sampling_rate(48000);
  bufferfilter.set_solo(2, true);
  bufferfilter.set_mute(2, true);
  
  ATK::SumFilter<double> sumFilter(1, 4);
  sumFilter.set_input_sampling_rate(48000);
  sumFilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  bufferfilter.set_input_port(0, &generator1, 0);
  bufferfilter.set_input_port(1, &generator2, 0);
  bufferfilter.set_input_port(2, &generator3, 0);
  bufferfilter.set_input_port(3, &generator4, 0);
  sumFilter.set_input_port(0, &bufferfilter, 0);
  sumFilter.set_input_port(1, &bufferfilter, 1);
  sumFilter.set_input_port(2, &bufferfilter, 2);
  sumFilter.set_input_port(3, &bufferfilter, 3);
  checker.set_input_port(0, &sumFilter, 0);
  checker.process(PROCESSSIZE);
}
