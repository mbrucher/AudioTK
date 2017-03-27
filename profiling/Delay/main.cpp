
#include <cstdlib>

#include <ATK/Delay/FixedDelayLineFilter.h>
#include <ATK/Delay/UniversalVariableDelayLineFilter.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <ATK/Tools/CachedSinusGeneratorFilter.h>
#include <ATK/Tools/DryWetFilter.h>

int main(int argc, char** argv)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  ATK::CachedSinusGeneratorFilter<double> generatordelay(10);
  generatordelay.set_output_sampling_rate(1024 * 64);
  generatordelay.set_volume(5);
  generatordelay.set_offset(20);

  ATK::FixedDelayLineFilter<double> fixedDelayLineFilter(1024*64);
  fixedDelayLineFilter.set_input_sampling_rate(1024 * 64);
  fixedDelayLineFilter.set_output_sampling_rate(1024 * 64);
  ATK::UniversalVariableDelayLineFilter<double> filter(48000);
  filter.set_blend(0.5);
  filter.set_feedback(0.1);
  filter.set_feedforward(1);
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_input_port(0, &fixedDelayLineFilter, 0);
  filter.set_input_port(1, &generatordelay, 0);
  ATK::DryWetFilter<double> drywetFilter;
  drywetFilter.set_input_sampling_rate(1024 * 64);
  drywetFilter.set_output_sampling_rate(1024 * 64);

  fixedDelayLineFilter.set_input_port(0, &generator, 0);

  drywetFilter.set_input_port(0, &filter, 0);
  drywetFilter.set_input_port(1, &generator, 0);

  drywetFilter.set_dry(0.5);

  for(size_t i = 0; i < 1024*1024; ++i)
    drywetFilter.process(1024);

  return EXIT_SUCCESS;
}