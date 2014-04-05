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
#if ATK_USE_FFTW == 1
  , fft_plan(NULL), input_data(NULL), output_freqs(NULL)
#endif
#if ATK_USE_ACCELERATE == 1
  , fftSetup(NULL), output_freqs(NULL)
#endif
  {
#if ATK_USE_ACCELERATE == 1
    splitData.realp = NULL;
    splitData.imagp = NULL;
#endif
  }
  
  template<class DataType_>
  FFTCheckerFilter<DataType_>::~FFTCheckerFilter()
  {
#if ATK_USE_FFTW == 1
    delete[] input_data;
    delete[] output_freqs;
    fftw_destroy_plan(fft_plan);
#endif
#if ATK_USE_ACCELERATE == 1
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
    delete[] output_freqs;
#endif
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::set_checks(const std::vector<std::pair<int, DataType> >& frequency_checks)
  {
    this->frequency_checks = frequency_checks;
  }

  template<class DataType_>
  void FFTCheckerFilter<DataType_>::setup()
  {
#if ATK_USE_FFTW == 1
    delete[] input_data;
    delete[] output_freqs;
    fftw_destroy_plan(fft_plan);

    input_data = new fftw_complex[input_sampling_rate];
    output_freqs = new fftw_complex[input_sampling_rate];
    
    fft_plan = fftw_plan_dft_1d(input_sampling_rate, input_data, output_freqs, FFTW_FORWARD, FFTW_ESTIMATE);

#endif
#if ATK_USE_ACCELERATE == 1
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
    splitData.realp = new double[input_sampling_rate/2];
    splitData.imagp = new double[input_sampling_rate/2];
    log2n = std::log2(input_sampling_rate);
    fftSetup = vDSP_create_fftsetupD(log2n, FFT_RADIX2);
    delete[] output_freqs;
    output_freqs = new double[input_sampling_rate/2];
#endif
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::process_impl(long size)
  {
    for(long i = 0; i < size/input_sampling_rate; ++i)
    {
#if ATK_USE_FFTW == 1
      for(int j = 0; j < input_sampling_rate; ++j)
      {
        input_data[j][0] = converted_inputs[0][i * input_sampling_rate + j];
        input_data[j][1] =0;
      }
      fftw_execute(fft_plan);
#endif
#if ATK_USE_ACCELERATE == 1
      double factor = input_sampling_rate;
      vDSP_ctozD(reinterpret_cast<DOUBLE_COMPLEX*>(&converted_inputs[0][i * input_sampling_rate]), 2, &splitData, 1, input_sampling_rate/2);
      vDSP_fft_zripD(fftSetup, &splitData, 1, log2n, FFT_FORWARD);
      vDSP_zvabsD(&splitData, 1, output_freqs, 1, input_sampling_rate/2);
      vDSP_vsdivD(output_freqs, 1, &factor, output_freqs, 1, input_sampling_rate/2);
#endif
      
      for(int j = 0; j < frequency_checks.size(); ++j)
      {
#if ATK_USE_FFTW == 1
        DataType amp = output_freqs[frequency_checks[j].first][0] * output_freqs[frequency_checks[j].first][0];
        amp += output_freqs[frequency_checks[j].first][1] * output_freqs[frequency_checks[j].first][1];
#endif
#if ATK_USE_ACCELERATE == 1
        DataType amp = output_freqs[frequency_checks[j].first];
#endif
        DataType amp_check = frequency_checks[j].second * frequency_checks[j].second;
        if(amp_check == 0)
        {
          BOOST_REQUIRE_SMALL(amp, 0.01);
        }
        else
        {
          BOOST_REQUIRE_CLOSE(amp, amp_check, 0.01);
        }
      }
    }
  }
  
  template class FFTCheckerFilter<double>;
}
