/**
 * \ file HouseholderFeedbackDelayNetworkFilter.cpp
 */

#include <ATK/Delay/FeedbackDelayNetworkFilter.h>
#include <ATK/Delay/HouseholderMixture.h>

#include <array>
#include <fstream>

#include <ATK/Core/InPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

const int OTHERPROCESSSIZE = 9600;

BOOST_AUTO_TEST_CASE(HouseholderFeedbackDelayNetworkFilter_sinus_complex_test)
{
  std::array<double, OTHERPROCESSSIZE> data;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_hadamard.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, OTHERPROCESSSIZE, false);
  generator.set_output_sampling_rate(96000);

  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 4>> filter(100000);
  filter.set_input_sampling_rate(96000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 4800);
  filter.set_delay(1, 3600);
  filter.set_delay(2, 2400);
  filter.set_delay(3, 1200);
  filter.set_ingain(0, 1);
  filter.set_ingain(1, .2);
  filter.set_ingain(2, 1);
  filter.set_ingain(3, 1);
  filter.set_outgain(0, 1);
  filter.set_outgain(1, 1);
  filter.set_outgain(2, 1);
  filter.set_outgain(3, .5);
  filter.set_feedback(0, .2);
  filter.set_feedback(1, .8);
  filter.set_feedback(2, .4);
  filter.set_feedback(3, .2);

  filter.process(OTHERPROCESSSIZE);

  std::array<double, OTHERPROCESSSIZE> outdata;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_householder.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(outdata.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < OTHERPROCESSSIZE; ++i)
  {
    BOOST_CHECK_CLOSE(outdata[i], filter.get_output_array(0)[i], 0.0001);
  }
}
