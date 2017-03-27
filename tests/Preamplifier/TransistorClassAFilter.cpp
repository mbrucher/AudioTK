/**
 * \ file TransistorClassAFilter.cpp
 */

#include <fstream>

#include <ATK/config.h>

#include <ATK/EQ/ButterworthFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Preamplifier/TransistorClassAFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/DecimationFilter.h>
#include <ATK/Tools/OversamplingFilter.h>
#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/VolumeFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#define PROCESSSIZE (1200)

BOOST_AUTO_TEST_CASE( TransistorClassAFilter_sin1k )
{
  std::unique_ptr<double[]> data(new double[PROCESSSIZE]);
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input2.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.get()), PROCESSSIZE * sizeof(double));
  }
  
  ATK::InPointerFilter<double> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::unique_ptr<double[]> datacheck(new double[PROCESSSIZE]);
  {
    std::ifstream check(ATK_SOURCE_TREE "/tests/data/output4_tca.dat", std::ios::binary);
    check.read(reinterpret_cast<char*>(datacheck.get()), PROCESSSIZE * sizeof(double));
  }
  
  ATK::InPointerFilter<double> check(datacheck.get(), 1, PROCESSSIZE, false);
  check.set_output_sampling_rate(48000);
  
  ATK::VolumeFilter<double> volume;
  volume.set_input_sampling_rate(48000);
  volume.set_volume(-1);
  volume.set_input_port(0, &check, 0);

  ATK::OversamplingFilter<double, ATK::Oversampling6points5order_4<double> > oversampling_filter;
  oversampling_filter.set_input_sampling_rate(48000);
  oversampling_filter.set_output_sampling_rate(48000 * 4);
  oversampling_filter.set_input_port(0, &generator, 0);

  auto filter = ATK::TransistorClassAFilter<double>::build_standard_filter();
  filter.set_input_sampling_rate(48000 * 4);
  filter.set_input_port(0, &oversampling_filter, 0);
  
  ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<double> > lowfilter;
  lowfilter.set_input_sampling_rate(48000 * 4);
  lowfilter.set_output_sampling_rate(48000 * 4);
  lowfilter.set_cut_frequency(48000);
  lowfilter.set_order(5);
  lowfilter.set_input_port(0, &filter, 0);

  ATK::DecimationFilter<double> decimation_filter(1);
  decimation_filter.set_input_sampling_rate(48000 * 4);
  decimation_filter.set_output_sampling_rate(48000);
  decimation_filter.set_input_port(0, &lowfilter, 0);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &decimation_filter, 0);
  sum.set_input_port(1, &volume, 0);
  
  ATK::VolumeFilter<double> volume2;
  volume2.set_input_sampling_rate(48000);
  volume2.set_volume(.001);
  volume2.set_input_port(0, &sum, 0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &volume2, 0);
  
  checker.process(PROCESSSIZE);
}
