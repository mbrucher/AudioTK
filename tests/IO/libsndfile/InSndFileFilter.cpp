/**
 * \ file InSndFilter.cpp
 */

#include <ATK/IO/libsndfile/InSndFileFilter.h>
#include <ATK/IO/InWavFilter.h>

#include <ATK/config.h>

#include <ATK/Tools/VolumeFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const size_t PROCESSSIZE = 1024;

BOOST_AUTO_TEST_CASE( InSndFileFilter_InFloat_1k_test )
{
  ATK::InSndFileFilter<float> generator(ATK_SOURCE_TREE "/tests/data/sinus1k.wav");
  BOOST_CHECK_EQUAL(generator.get_frames(), PROCESSSIZE);
  
  ATK::InWavFilter<float> filter(ATK_SOURCE_TREE "/tests/data/sinus1k.wav");
  filter.set_output_sampling_rate(48000);

  ATK::VolumeFilter<float> gainfilter;
  gainfilter.set_input_sampling_rate(48000);
  gainfilter.set_volume(-1);

  ATK::SumFilter<float> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  gainfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(0, &gainfilter, 0);
  sumfilter.set_input_port(1, &filter, 0);
  
  checker.set_input_port(0, &sumfilter, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( InSndFileFilter_InFloat_1k2k_test )
{
  ATK::InSndFileFilter<float> generator(ATK_SOURCE_TREE "/tests/data/sinus1k2k.wav");
  
  ATK::VolumeFilter<float> gainfilter1;
  gainfilter1.set_input_sampling_rate(48000);
  gainfilter1.set_volume(-1);
  gainfilter1.set_input_port(0, &generator, 0);

  ATK::VolumeFilter<float> gainfilter2;
  gainfilter2.set_input_sampling_rate(48000);
  gainfilter2.set_volume(-1);
  gainfilter2.set_input_port(0, &generator, 1);

  ATK::InWavFilter<float> filter(ATK_SOURCE_TREE "/tests/data/sinus1k2k.wav");
  filter.set_output_sampling_rate(48000);
  
  ATK::SumFilter<float> sumfilter1;
  sumfilter1.set_input_sampling_rate(48000);
  sumfilter1.set_input_port(0, &gainfilter1, 0);
  sumfilter1.set_input_port(1, &filter, 0);
  
  ATK::SumFilter<float> sumfilter2;
  sumfilter2.set_input_sampling_rate(48000);
  sumfilter2.set_input_port(0, &gainfilter2, 0);
  sumfilter2.set_input_port(1, &filter, 1);
  
  ATK::SumFilter<float> sumfilter3;
  sumfilter3.set_input_sampling_rate(48000);
  sumfilter3.set_input_port(0, &sumfilter1, 0);
  sumfilter3.set_input_port(1, &sumfilter2, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &sumfilter3, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( InSndFileFilter_InDouble_1k_test )
{
  ATK::InSndFileFilter<double> generator(ATK_SOURCE_TREE "/tests/data/sinus1k.wav");
  
  ATK::InWavFilter<double> filter(ATK_SOURCE_TREE "/tests/data/sinus1k.wav");
  filter.set_output_sampling_rate(48000);
  
  ATK::VolumeFilter<double> gainfilter;
  gainfilter.set_input_sampling_rate(48000);
  gainfilter.set_volume(-1);
  
  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  gainfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(0, &gainfilter, 0);
  sumfilter.set_input_port(1, &filter, 0);
  
  checker.set_input_port(0, &sumfilter, 0);
  
  checker.process(PROCESSSIZE);
}

BOOST_AUTO_TEST_CASE( InSndFileFilter_InDouble_1k2k_test )
{
  ATK::InSndFileFilter<double> generator(ATK_SOURCE_TREE "/tests/data/sinus1k2k.wav");
  
  ATK::VolumeFilter<double> gainfilter1;
  gainfilter1.set_input_sampling_rate(48000);
  gainfilter1.set_volume(-1);
  gainfilter1.set_input_port(0, &generator, 0);
  
  ATK::VolumeFilter<double> gainfilter2;
  gainfilter2.set_input_sampling_rate(48000);
  gainfilter2.set_volume(-1);
  gainfilter2.set_input_port(0, &generator, 1);
  
  ATK::InWavFilter<double> filter(ATK_SOURCE_TREE "/tests/data/sinus1k2k.wav");
  filter.set_output_sampling_rate(48000);
  
  ATK::SumFilter<double> sumfilter1;
  sumfilter1.set_input_sampling_rate(48000);
  sumfilter1.set_input_port(0, &gainfilter1, 0);
  sumfilter1.set_input_port(1, &filter, 0);
  
  ATK::SumFilter<double> sumfilter2;
  sumfilter2.set_input_sampling_rate(48000);
  sumfilter2.set_input_port(0, &gainfilter2, 0);
  sumfilter2.set_input_port(1, &filter, 1);
  
  ATK::SumFilter<double> sumfilter3;
  sumfilter3.set_input_sampling_rate(48000);
  sumfilter3.set_input_port(0, &sumfilter1, 0);
  sumfilter3.set_input_port(1, &sumfilter2, 0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &sumfilter3, 0);
  
  checker.process(PROCESSSIZE);
}
