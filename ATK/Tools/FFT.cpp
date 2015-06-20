/**
 * \file FFT.cpp
 */

#include <cmath>
#include <complex>
#include <cstdlib>

#include "FFT.h"

namespace ATK
{
  template<class DataType_>
  FFT<DataType_>::FFT()
#if ATK_USE_FFTW == 1
  :size(0), fft_plan(nullptr), fft_reverse_plan(nullptr), input_data(nullptr), output_freqs(nullptr)
#endif
#if ATK_USE_ACCELERATE == 1
  :fftSetup(nullptr)
#endif
  {
#if ATK_USE_ACCELERATE == 1
    splitData.realp = nullptr;
    splitData.imagp = nullptr;
#endif
  }
  
  template<class DataType_>
  FFT<DataType_>::~FFT()
  {
#if ATK_USE_FFTW == 1
    fftw_free(input_data);
    fftw_free(output_freqs);
    fftw_destroy_plan(fft_plan);
    fftw_destroy_plan(fft_reverse_plan);
#endif
#if ATK_USE_ACCELERATE == 1
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
    delete[] output_freqs;
#endif
  }
  
  template<class DataType_>
  void FFT<DataType_>::set_size(std::int64_t size)
  {
    if(this->size == size)
      return;
    this->size = size;
    log2n = static_cast<int>(std::log(size) / std::log(2.));
#if ATK_USE_FFTW == 1
    fftw_free(input_data);
    fftw_free(output_freqs);
    fftw_destroy_plan(fft_plan);
    fftw_destroy_plan(fft_reverse_plan);
    
    input_data = fftw_alloc_complex(size);
    output_freqs = fftw_alloc_complex(size);
    
    fft_plan = fftw_plan_dft_1d(size, input_data, output_freqs, FFTW_FORWARD, FFTW_ESTIMATE);
    fft_reverse_plan = fftw_plan_dft_1d(size, input_data, output_freqs, FFTW_BACKWARD, FFTW_ESTIMATE);
#endif
#if ATK_USE_ACCELERATE == 1
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
    splitData.realp = new double[size];
    splitData.imagp = new double[size];
    fftSetup = vDSP_create_fftsetupD(log2n, FFT_RADIX2);
#endif
  }

  template<class DataType_>
  void FFT<DataType_>::process(const DataType_* input, std::int64_t input_size)
  {
#if ATK_USE_FFTW == 1
    double factor = 1 << (log2n - 1);
    for(int j = 0; j < std::min(input_size, size); ++j)
    {
      input_data[j][0] = input[j] / factor;
      input_data[j][1] = 0;
    }
    fftw_execute(fft_plan);
#endif
#if ATK_USE_ACCELERATE == 1
    double factor = input_sampling_rate;
    for(int j = 0; j < std::min(input_size, size); ++j)
    {
      splitData.realp[j] = input[j] / factor;
      splitData.imagp[j] = 0;
    }
    vDSP_fft_zipD(fftSetup, &splitData, 1, log2n, FFT_FORWARD);
#endif
  }
  
  template<class DataType_>
  void FFT<DataType_>::process_forward(const DataType_* input, std::complex<DataType_>* output, std::int64_t input_size)
  {
    process(input, input_size);
#if ATK_USE_FFTW == 1
    for(int j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = std::complex<DataType_>(output_freqs[j][0], output_freqs[j][1]);
    }
#endif
#if ATK_USE_ACCELERATE == 1
    for(int j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = std::complex<DataType_>(splitData.realp[j], splitData.imagp[j]);
    }
#endif
  }

  template<class DataType_>
  void FFT<DataType_>::get_amp(std::vector<DataType_>& amp) const
  {
    amp.assign(size / 2 + 1, 0);
    for(std::int64_t i = 0; i < size / 2 + 1; ++i)
    {
#if ATK_USE_FFTW == 1
      amp[i] = output_freqs[i][0] * output_freqs[i][0];
      amp[i] += output_freqs[i][1] * output_freqs[i][1];
      amp[i] = std::sqrt(amp[i]);
#endif
#if ATK_USE_ACCELERATE == 1
      amp[i] = splitData.realp[j] * splitData.realp[j];
      amp[i] += splitData.imagp[j] * splitData.imagp[j];
      amp[i] = std::sqrt(amp[i]);
#endif
    }
  }
  
  template<class DataType_>
  void FFT<DataType_>::get_angle(std::vector<DataType_>& angle) const
  {
    angle.assign(size / 2 + 1, 0);
    for(std::int64_t i = 0; i < size / 2 + 1; ++i)
    {
#if ATK_USE_FFTW == 1
      angle[i] = std::arg(std::complex<DataType_>(output_freqs[i][0], output_freqs[i][1]));
#endif
#if ATK_USE_ACCELERATE == 1
      angle[i] = std::arg(std::complex<DataType_>(splitData.realp[j], splitData.imagp[j]));
#endif
    }
  }

  template class FFT<double>;
}
