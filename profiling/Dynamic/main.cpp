
#include <cstdlib>

#include <ATK/Dynamic/AttackReleaseFilter.h>
#include <ATK/Dynamic/GainColoredCompressorFilter.h>
#include <ATK/Dynamic/PowerFilter.h>

#include <ATK/Tools/ApplyGainFilter.h>
#include <ATK/Tools/DryWetFilter.h>
#include <ATK/Tools/VolumeFilter.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

int main(int argc, char** argv)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::PowerFilter<double> powerFilter;
  powerFilter.set_input_sampling_rate(1024 * 64);
  powerFilter.set_output_sampling_rate(1024 * 64);
  ATK::AttackReleaseFilter<double> attackReleaseFilter;
  attackReleaseFilter.set_input_sampling_rate(1024 * 64);
  attackReleaseFilter.set_output_sampling_rate(1024 * 64);
  ATK::GainFilter<ATK::GainColoredCompressorFilter<double>> gainCompressorFilter(1, 256*1024);
  gainCompressorFilter.set_input_sampling_rate(1024 * 64);
  gainCompressorFilter.set_output_sampling_rate(1024 * 64);
  ATK::ApplyGainFilter<double> applyGainFilter;
  applyGainFilter.set_input_sampling_rate(1024 * 64);
  applyGainFilter.set_output_sampling_rate(1024 * 64);
  ATK::VolumeFilter<double> volumeFilter;
  volumeFilter.set_input_sampling_rate(1024 * 64);
  volumeFilter.set_output_sampling_rate(1024 * 64);
  ATK::DryWetFilter<double> drywetFilter;
  drywetFilter.set_input_sampling_rate(1024 * 64);
  drywetFilter.set_output_sampling_rate(1024 * 64);

  powerFilter.set_input_port(0, &generator, 0);
  attackReleaseFilter.set_input_port(0, &powerFilter, 0);
  gainCompressorFilter.set_input_port(0, &attackReleaseFilter, 0);
  applyGainFilter.set_input_port(0, &gainCompressorFilter, 0);
  applyGainFilter.set_input_port(1, &generator, 0);
  volumeFilter.set_input_port(0, &applyGainFilter, 0);
  drywetFilter.set_input_port(0, &volumeFilter, 0);
  drywetFilter.set_input_port(1, &generator, 0);

  powerFilter.set_memory(0.001);
  attackReleaseFilter.set_attack(0.005);
  attackReleaseFilter.set_release(0.010);
  gainCompressorFilter.set_color(0);
  gainCompressorFilter.set_softness(0.001);
  gainCompressorFilter.set_quality(0.01);
  gainCompressorFilter.set_ratio(10);
  gainCompressorFilter.set_threshold(0.1);
  drywetFilter.set_dry(0.5);

  for(size_t i = 0; i < 1024*1024; ++i)
    drywetFilter.process(1024);

  return EXIT_SUCCESS;
}