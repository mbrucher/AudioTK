
#include <cstdlib>
#include <ATK/EQ/BesselFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

int main(int argc, char** argv)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_cut_frequency(100);
  filter.set_order(7);

  filter.set_input_port(0, &generator, 0);

  for(size_t i = 0; i < 1024*1024; ++i)
    filter.process(1024);

  return EXIT_SUCCESS;
}