/**
 * \file FFT.h
 */

#ifndef ATK_TOOLS_FFT_H
#define ATK_TOOLS_FFT_H

#include <complex>
#include <cstdint>
#include <vector>

#include <ATK/config.h>
#include "config.h"

#if ATK_USE_FFTW == 1
#include <fftw3.h>
#endif
#if ATK_USE_ACCELERATE == 1
#include <Accelerate/Accelerate.h>
#endif

namespace ATK
{
  template<class DataType_>
  class ATK_TOOLS_EXPORT FFT
  {
  public:
    FFT();
    ~FFT();
    
    void set_size(int64_t size);
    void process(const DataType_* input, int64_t input_size) const;
    void process_forward(const DataType_* input, std::complex<DataType_>* output, int64_t input_size) const;
    void process_backward(const std::complex<DataType_>* input, DataType_* output, int64_t input_size) const;
    void get_amp(std::vector<DataType_>& amp) const;
    void get_angle(std::vector<DataType_>& angle) const;

  protected:
	int64_t size;
	int log2n;

#if ATK_USE_FFTW == 1
    fftw_plan fft_plan;
    fftw_plan fft_reverse_plan;
    fftw_complex* input_data;
    fftw_complex* output_freqs;
#endif
    
#if ATK_USE_ACCELERATE == 1
    FFTSetupD fftSetup;
    DSPDoubleSplitComplex splitData;
#endif
  };
}

#endif