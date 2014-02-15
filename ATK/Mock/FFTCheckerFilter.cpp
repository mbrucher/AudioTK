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
  :TypedBaseFilter<DataType_>(1, 0)
#ifdef __APPLE__
  , fftSetup(NULL)
#endif
  ,output_freqs(NULL)
  {
#ifdef __APPLE__
    splitData.realp = NULL;
    splitData.imagp = NULL;
#endif
  }
  
  template<class DataType_>
  FFTCheckerFilter<DataType_>::~FFTCheckerFilter()
  {
#ifdef __APPLE__
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
#endif
    delete[] output_freqs;
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::set_checks(const std::vector<std::pair<int, DataType> >& frequency_checks)
  {
    this->frequency_checks = frequency_checks;
  }

  template<class DataType_>
  void FFTCheckerFilter<DataType_>::setup()
  {
#ifdef __APPLE__
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
    splitData.realp = new double[input_sampling_rate/2];
    splitData.imagp = new double[input_sampling_rate/2];
    log2n = std::log2(input_sampling_rate);
    fftSetup = vDSP_create_fftsetupD(log2n, FFT_RADIX2);
#endif
    delete[] output_freqs;
    output_freqs = new double[input_sampling_rate/2];
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::process_impl(long size)
  {
    double factor = input_sampling_rate;
    for(long i = 0; i < size/input_sampling_rate; ++i)
    {
      vDSP_ctozD(reinterpret_cast<DOUBLE_COMPLEX*>(&converted_inputs[0][i * input_sampling_rate]), 2, &splitData, 1, input_sampling_rate/2);
      vDSP_fft_zripD(fftSetup, &splitData, 1, log2n, FFT_FORWARD);
      vDSP_zvabsD(&splitData, 1, output_freqs, 1, input_sampling_rate/2);
      vDSP_vsdivD(output_freqs, 1, &factor, output_freqs, 1, input_sampling_rate/2);
      
      for(int j = 0; j < frequency_checks.size(); ++j)
      {
        DataType amp = output_freqs[frequency_checks[j].first];
        DataType amp_check = frequency_checks[j].second * frequency_checks[j].second;
        if(amp_check == 0)
        {
          BOOST_REQUIRE_SMALL(amp, 0.01);
        }
        else
        {
          BOOST_REQUIRE_CLOSE(amp, amp_check, 0.001);
        }
      }
    }
  }
  
  template class FFTCheckerFilter<double>;
}
