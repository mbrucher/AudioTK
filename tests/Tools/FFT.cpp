/**
 * \ file FFT.cpp
 */

#include <cmath>

#include <ATK/Tools/FFT.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( FFT_test )
{
  std::vector<double> input(128);
  std::vector<double> ref(128);
  for(int i = 0; i < 100; ++i)
  {
    input[i] = ref[i] = i+1;
  }
  std::vector<std::complex<double> > frequency(128);
  
  ATK::FFT<double> processor;
  processor.set_size(128);
  
  processor.process_forward(input.data(), frequency.data(), 100);
  processor.process_backward(frequency.data(), input.data(), 128);
  
  for(int i = 0; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(input[i], ref[i], 0.0001);
  }
}

BOOST_AUTO_TEST_CASE( doubleFFT_test )
{
  std::vector<double> input(128);
  std::vector<double> double_input(128);
  std::vector<double> ref(128);
  for(int i = 0; i < 100; ++i)
  {
    input[i] = ref[i] = i+1;
    double_input[i] = 2 * (i+1);
  }
  std::vector<std::complex<double> > frequency(128);
  std::vector<std::complex<double> > double_frequency(128);
  
  ATK::FFT<double> processor;
  processor.set_size(128);
  
  processor.process_forward(input.data(), frequency.data(), 100);
  processor.process_forward(double_input.data(), double_frequency.data(), 100);
  processor.process_backward(frequency.data(), input.data(), 128);
  processor.process_backward(double_frequency.data(), double_input.data(), 128);
  
  for(int i = 0; i < 100; ++i)
  {
    BOOST_REQUIRE_CLOSE(input[i], ref[i], 0.0001);
    BOOST_REQUIRE_CLOSE(double_input[i], 2*ref[i], 0.0001);
  }
}
