/**
 * \ file SimpleOverdriveFilter.cpp
 */

#include <ATK/config.h>
#include <ATK/git.h>

#include <ATK/Distortion/SimpleOverdriveFilter.h>

#include <ATK/IO/libsndfile/InSndFileFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/VolumeFilter.h>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1000)

BOOST_AUTO_TEST_CASE( SimpleOverdriveFilter_sin1k_test )
{
  ATK::InSndFileFilter<float> generator(ATK_SOURCE_TREE "/tests/data/sin.wav");
  generator.set_output_sampling_rate(48000);

  ATK::InSndFileFilter<float> check(ATK_SOURCE_TREE "/tests/data/sin_overdrive.wav");
  generator.set_output_sampling_rate(48000);

  ATK::VolumeFilter<float> volume;
  volume.set_input_sampling_rate(48000);
  volume.set_volume(-1);
  volume.set_input_port(0, &generator, 0);
  
  ATK::SimpleOverdriveFilter<float> filter;
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &volume, 0);

  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &check, 0);

  ATK::VolumeFilter<float> volume2;
  volume2.set_input_sampling_rate(48000);
  volume2.set_volume(.001);
  volume2.set_input_port(0, &sum, 0);

  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &volume2, 0);
  
  checker.process(PROCESSSIZE);
}
