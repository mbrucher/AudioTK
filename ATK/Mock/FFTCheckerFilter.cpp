/**
 * \file FFTCheckerFilter.cpp
 */

#include "FFTCheckerFilter.h"

#include <cmath>

#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

namespace ATK
{
  template<class DataType_>
  FFTCheckerFilter<DataType_>::FFTCheckerFilter()
  :TypedBaseFilter<DataType_>(1, 0), amplitude(1), frequency(1)
#ifdef __APPLE__
  , fftSetup(NULL)
#endif
  {
  }
  
  template<class DataType_>
  FFTCheckerFilter<DataType_>::~FFTCheckerFilter()
  {
#ifdef __APPLE__
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
#endif
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::set_amplitude(DataType amplitude)
  {
    this->amplitude = amplitude;
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
#ifdef __APPLE__
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
    splitData.realp = new double[input_sampling_rate/2];
    splitData.imagp = new double[input_sampling_rate/2];
    log2n = std::log(input_sampling_rate);
    vDSP_create_fftsetupD(log2n, FFT_RADIX2);
#endif
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::process_impl(int size)
  {
    for(int i = 0; i < size/input_sampling_rate; ++i)
    {
      vDSP_ctozD(reinterpret_cast<DOUBLE_COMPLEX*>(&converted_inputs[0][i * input_sampling_rate]), 2, &splitData, 1, input_sampling_rate/2);
      vDSP_fft_zripD(fftSetup, &splitData, 1, log2n, FFT_FORWARD);
      
      /* Now find a way of comparing results to theoretical levels */
    }
  }
  
  template class FFTCheckerFilter<double>;
}
