/**
 * \file FFT.cpp
 */

#include "FFT.h"

#include <ATK/config.h>
#if ATK_USE_FFTW == 1
#include <fftw3.h>
#endif
#if ATK_USE_IPP == 1
#include <ipp.h>
#endif

#include <gsl/gsl>

#include <algorithm>
#include <complex>
#include <cstdlib>

namespace ATK
{
  template<class DataType_>
  class FFT<DataType_>::FFTImpl
  {
#if ATK_USE_FFTW == 1
    fftw_plan fft_plan;
    fftw_plan fft_reverse_plan;
    fftw_complex* input_data;
    fftw_complex* output_freqs;
#endif
#if ATK_USE_IPP == 1
    Ipp64fc *pSrc;
    Ipp64fc *pDst;
    IppsFFTSpec_C_64fc* pFFTSpec;
    IppsDFTSpec_C_64fc* pDFTSpec;
    Ipp8u* pFFTSpecBuf;
    Ipp8u* pFFTInitBuf;
    Ipp8u* pFFTWorkBuf;
    bool power_of_two;
#endif
  public:
    FFTImpl()
#if ATK_USE_FFTW == 1
    :fft_plan(nullptr), fft_reverse_plan(nullptr), input_data(nullptr), output_freqs(nullptr)
#endif
#if ATK_USE_IPP == 1
    :pSrc(nullptr), pDst(nullptr), pFFTSpec(nullptr), pDFTSpec(nullptr), pFFTSpecBuf(nullptr), pFFTInitBuf(nullptr), pFFTWorkBuf(nullptr), power_of_two(false)
#endif
    {
    }
    
    ~FFTImpl()
    {
#if ATK_USE_FFTW == 1
      fftw_free(input_data);
      fftw_free(output_freqs);
      fftw_destroy_plan(fft_plan);
      fftw_destroy_plan(fft_reverse_plan);
#endif
#if ATK_USE_IPP == 1
      if (pSrc)
      {
        ippFree(pSrc);
      }
      if (pDst)
      {
        ippFree(pDst);
      }
      if (pFFTSpec)
      {
        ippFree(pFFTSpec);
      }
      if (pFFTInitBuf)
      {
        ippFree(pFFTInitBuf);
      }
      if (pFFTWorkBuf)
      {
        ippFree(pFFTWorkBuf);
      }
#endif
    }

    void set_size(gsl::index size)
    {
#if ATK_USE_FFTW == 1
      fftw_free(input_data);
      fftw_free(output_freqs);
      fftw_destroy_plan(fft_plan);
      fftw_destroy_plan(fft_reverse_plan);
      
      input_data = fftw_alloc_complex(size);
      output_freqs = fftw_alloc_complex(size);
      
      fft_plan = fftw_plan_dft_1d(size, input_data, output_freqs, FFTW_FORWARD, FFTW_ESTIMATE);
      fft_reverse_plan = fftw_plan_dft_1d(size, output_freqs, input_data, FFTW_BACKWARD, FFTW_ESTIMATE);
#endif
#if ATK_USE_IPP == 1
      power_of_two = ((size & (size - 1)) == 0);
      if (pSrc)
      {
        ippFree(pSrc);
      }
      if (pDst)
      {
        ippFree(pDst);
      }
      if (pFFTSpec)
      {
        ippFree(pFFTSpec);
      }
      pFFTSpec = nullptr;
      if (pDFTSpec)
      {
        ippFree(pDFTSpec);
      }
      pDFTSpec = nullptr;
      if (pFFTSpecBuf)
      {
        ippFree(pFFTSpecBuf);
      }
      if (pFFTInitBuf)
      {
        ippFree(pFFTInitBuf);
      }
      if (pFFTWorkBuf)
      {
        ippFree(pFFTWorkBuf);
      }
      int sizeFFTSpec, sizeFFTInitBuf, sizeFFTWorkBuf;
      if (power_of_two)
      {
        ippsFFTGetSize_C_64fc(static_cast<int>(std::lround(std::log(size) / std::log(2))), IPP_FFT_DIV_FWD_BY_N, ippAlgHintAccurate, &sizeFFTSpec, &sizeFFTInitBuf, &sizeFFTWorkBuf);
      }
      else
      {
        ippsDFTGetSize_C_64fc(static_cast<int>(size), IPP_FFT_DIV_FWD_BY_N, ippAlgHintAccurate, &sizeFFTSpec, &sizeFFTInitBuf, &sizeFFTWorkBuf);
      }
      
      pFFTSpecBuf = ippsMalloc_8u(sizeFFTSpec);
      pFFTInitBuf = ippsMalloc_8u(sizeFFTInitBuf);
      pFFTWorkBuf = ippsMalloc_8u(sizeFFTWorkBuf);
      pSrc = ippsMalloc_64fc(static_cast<int>(size));
      pDst = ippsMalloc_64fc(static_cast<int>(size));
      if (power_of_two)
      {
        ippsFFTInit_C_64fc(&pFFTSpec, static_cast<int>(std::lround(std::log(size) / std::log(2))), IPP_FFT_DIV_FWD_BY_N, ippAlgHintAccurate, pFFTSpecBuf, pFFTInitBuf);
      }
      else
      {
        pDFTSpec = (IppsDFTSpec_C_64fc*)ippsMalloc_8u(sizeFFTSpec);
        ippsDFTInit_C_64fc(static_cast<int>(size), IPP_FFT_DIV_FWD_BY_N, ippAlgHintAccurate, pDFTSpec, pFFTInitBuf);
      }
      if (pFFTInitBuf)
        ippFree(pFFTInitBuf);
      pFFTInitBuf = nullptr;
#endif
    }

    void process(const DataType_* input, gsl::index input_size, gsl::index size) const
    {
#if ATK_USE_FFTW == 1
      double factor = static_cast<double>(size);
      for(gsl::index j = 0; j < std::min(input_size, size); ++j)
      {
        input_data[j][0] = input[j] / factor;
        input_data[j][1] = 0;
      }
      for(gsl::index j = input_size; j < size; ++j)
      {
        input_data[j][0] = 0;
        input_data[j][1] = 0;
      }
      fftw_execute(fft_plan);
#endif
#if ATK_USE_IPP == 1
      for (gsl::index j = 0; j < std::min(input_size, size); ++j)
      {
        pSrc[j].re = input[j];
        pSrc[j].im = 0;
      }
      for (gsl::index j = input_size; j < size; ++j)
      {
        pSrc[j].re = 0;
        pSrc[j].im = 0;
      }
      if (power_of_two)
      {
        ippsFFTFwd_CToC_64fc(pSrc, pDst, pFFTSpec, pFFTWorkBuf);
      }
      else
      {
        ippsDFTFwd_CToC_64fc(pSrc, pDst, pDFTSpec, pFFTWorkBuf);
      }
#endif
    }
    
    void process_forward(std::complex<DataType_>* output, gsl::index size) const
    {
      for(gsl::index j = 0; j < size; ++j)
      {
#if ATK_USE_FFTW == 1
        output[j] = std::complex<DataType_>(output_freqs[j][0], output_freqs[j][1]);
#endif
#if ATK_USE_IPP == 1
        output[j] = std::complex<DataType_>(pDst[j].re, pDst[j].im);
#endif
      }
    }
    
    void process_backward(const std::complex<DataType_>* input, DataType_* output, gsl::index input_size, gsl::index size) const
    {
#if ATK_USE_FFTW == 1
      for(gsl::index j = 0; j < size; ++j)
      {
        output_freqs[j][0] = input[j].real();
        output_freqs[j][1] = input[j].imag();
      }
      fftw_execute(fft_reverse_plan);
      for(gsl::index j = 0; j < input_size; ++j)
      {
        output[j] = input_data[j][0];
      }
#endif
#if ATK_USE_IPP == 1
      for (gsl::index j = 0; j < size; ++j)
      {
        pDst[j].re = input[j].real();
        pDst[j].im = input[j].imag();
      }
      if (power_of_two)
      {
        ippsFFTInv_CToC_64fc(pDst, pDst, pFFTSpec, pFFTWorkBuf);
      }
      else
      {
        ippsDFTInv_CToC_64fc(pDst, pDst, pDFTSpec, pFFTWorkBuf);
      }
      for (gsl::index j = 0; j < input_size; ++j)
      {
        output[j] = pDst[j].re;
      }
#endif
    }

    void process(const std::complex<DataType_>* input, gsl::index input_size, gsl::index size) const
    {
#if ATK_USE_FFTW == 1
      double factor = static_cast<double>(size);
      for (gsl::index j = 0; j < std::min(input_size, size); ++j)
      {
        input_data[j][0] = std::real(input[j]) / factor;
        input_data[j][1] = std::imag(input[j]) / factor;
      }
      for (gsl::index j = input_size; j < size; ++j)
      {
        input_data[j][0] = 0;
        input_data[j][1] = 0;
      }
      fftw_execute(fft_plan);
#endif
#if ATK_USE_IPP == 1
      for (gsl::index j = 0; j < std::min(input_size, size); ++j)
      {
        pSrc[j].re = std::real(input[j]);
        pSrc[j].im = std::imag(input[j]);
      }
      for (gsl::index j = input_size; j < size; ++j)
      {
        pSrc[j].re = 0;
        pSrc[j].im = 0;
      }
      if (power_of_two)
      {
        ippsFFTFwd_CToC_64fc(pSrc, pDst, pFFTSpec, pFFTWorkBuf);
      }
      else
      {
        ippsDFTFwd_CToC_64fc(pSrc, pDst, pDFTSpec, pFFTWorkBuf);
      }
#endif
    }
    
    void process_backward(const std::complex<DataType_>* input, std::complex<DataType_>* output, gsl::index input_size, gsl::index size) const
    {
#if ATK_USE_FFTW == 1
      for (gsl::index j = 0; j < size; ++j)
      {
        output_freqs[j][0] = input[j].real();
        output_freqs[j][1] = input[j].imag();
      }
      fftw_execute(fft_reverse_plan);
      for (gsl::index j = 0; j < input_size; ++j)
      {
        output[j] = std::complex<DataType_>(input_data[j][0], input_data[j][1]);
      }
#endif
#if ATK_USE_IPP == 1
      for (gsl::index j = 0; j < size; ++j)
      {
        pDst[j].re = input[j].real();
        pDst[j].im = input[j].imag();
      }
      if (power_of_two)
      {
        ippsFFTInv_CToC_64fc(pDst, pDst, pFFTSpec, pFFTWorkBuf);
      }
      else
      {
        ippsDFTInv_CToC_64fc(pDst, pDst, pDFTSpec, pFFTWorkBuf);
      }
      for (gsl::index j = 0; j < input_size; ++j)
      {
        output[j] = std::complex<DataType_>(pDst[j].re, pDst[j].im);
      }
#endif
    }
    
    void get_amp(std::vector<DataType_>& amp) const
    {
      for(size_t i = 0; i < amp.size(); ++i)
      {
#if ATK_USE_FFTW == 1
        amp[i] = output_freqs[i][0] * output_freqs[i][0];
        amp[i] += output_freqs[i][1] * output_freqs[i][1];
        amp[i] = std::sqrt(amp[i]);
#endif
#if ATK_USE_IPP == 1
        amp[i] = pDst[i].re * pDst[i].re;
        amp[i] += pDst[i].im * pDst[i].im;
        amp[i] = std::sqrt(amp[i]);
#endif
      }
    }
    
    void get_angle(std::vector<DataType_>& angle) const
    {
      for(size_t i = 0; i < angle.size(); ++i)
      {
#if ATK_USE_FFTW == 1
        angle[i] = std::arg(std::complex<DataType_>(output_freqs[i][0], output_freqs[i][1]));
#endif
#if ATK_USE_IPP == 1
        angle[i] = std::arg(std::complex<DataType_>(pDst[i].re, pDst[i].im));
#endif
      }
    }
  };

  template<class DataType_>
  FFT<DataType_>::FFT()
  :size(0), impl(std::make_unique<FFTImpl>())
  {
  }
  

  template<class DataType_>
  FFT<DataType_>::~FFT()
  {
  }

  template<class DataType_>
  void FFT<DataType_>::set_size(gsl::index size_)
  {
    if(size == size_)
    {
      return;
    }
    size = size_;
    impl->set_size(size);
  }

  template<class DataType_>
  gsl::index FFT<DataType_>::get_size() const
  {
    return size;
  }

  template<class DataType_>
  void FFT<DataType_>::process(const DataType_* input, gsl::index input_size) const
  {
    impl->process(input, input_size, size);
  }
  
  template<class DataType_>
  void FFT<DataType_>::process_forward(const DataType_* input, std::complex<DataType_>* output, gsl::index input_size) const
  {
    process(input, input_size);
    impl->process_forward(output, size);
  }

  template<class DataType_>
  void FFT<DataType_>::process_backward(const std::complex<DataType_>* input, DataType_* output, gsl::index input_size) const
  {
    impl->process_backward(input, output, input_size, size);
  }

  template<class DataType_>
  void FFT<DataType_>::process(const std::complex<DataType_>* input, gsl::index input_size) const
  {
    impl->process(input, input_size, size);
  }

  template<class DataType_>
  void FFT<DataType_>::process_forward(const std::complex<DataType_>* input, std::complex<DataType_>* output, gsl::index input_size) const
  {
    process(input, input_size);
    impl->process_forward(output, size);
  }

  template<class DataType_>
  void FFT<DataType_>::process_backward(const std::complex<DataType_>* input, std::complex<DataType_>* output, gsl::index input_size) const
  {
    impl->process_backward(input, output, input_size, size);
  }

  template<class DataType_>
  void FFT<DataType_>::get_amp(std::vector<DataType_>& amp) const
  {
    amp.assign(size / 2 + 1, 0);
    impl->get_amp(amp);
  }
  
  template<class DataType_>
  void FFT<DataType_>::get_angle(std::vector<DataType_>& angle) const
  {
    angle.assign(size / 2 + 1, 0);
    impl->get_angle(angle);
  }

  template class FFT<double>;
}
