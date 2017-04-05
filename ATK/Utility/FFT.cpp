/**
 * \file FFT.cpp
 */

#include <algorithm>
#include <complex>
#include <cstdlib>

#include <ATK/Utility/FFT.h>

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
#if ATK_USE_IPP == 1
  :pSrc(nullptr), pDst(nullptr), pDFTSpec(nullptr), pDFTInitBuf(nullptr), pDFTWorkBuf(nullptr)
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
#if ATK_USE_IPP == 1
    if (pSrc)
      ippFree(pSrc);
    if (pDst)
      ippFree(pDst);
    if (pDFTSpec)
      ippFree(pDFTSpec);
    if (pDFTInitBuf)
      ippFree(pDFTInitBuf);
    if (pDFTWorkBuf)
      ippFree(pDFTWorkBuf);
#endif
  }
  
  template<class DataType_>
  void FFT<DataType_>::set_size(std::size_t size)
  {
    if(this->size == size)
      return;
    this->size = size;
    log2n = static_cast<int>(std::lround(std::log(size) / std::log(2.)));
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
#if ATK_USE_ACCELERATE == 1
    delete[] splitData.realp;
    delete[] splitData.imagp;
    vDSP_destroy_fftsetupD(fftSetup);
    splitData.realp = new double[size];
    splitData.imagp = new double[size];
    fftSetup = vDSP_create_fftsetupD(log2n, FFT_RADIX2);
#endif
#if ATK_USE_IPP == 1
    if (pSrc)
      ippFree(pSrc);
    if (pDst)
      ippFree(pDst);
    if (pDFTSpec)
      ippFree(pDFTSpec);
    if (pDFTInitBuf)
      ippFree(pDFTInitBuf);
    if (pDFTWorkBuf)
      ippFree(pDFTWorkBuf);
    int sizeDFTSpec, sizeDFTInitBuf, sizeDFTWorkBuf;
    ippsDFTGetSize_C_64fc(size, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, &sizeDFTSpec, &sizeDFTInitBuf, &sizeDFTWorkBuf);

    pDFTSpec = (IppsDFTSpec_C_64fc*) ippsMalloc_8u(sizeDFTSpec);
    pDFTInitBuf = ippsMalloc_8u(sizeDFTInitBuf);
    pDFTWorkBuf = ippsMalloc_8u(sizeDFTWorkBuf);
    pSrc = ippsMalloc_64fc(size);
    pDst = ippsMalloc_64fc(size);
    ippsDFTInit_C_64fc(size, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, pDFTSpec, pDFTInitBuf);
    if (pDFTInitBuf)
      ippFree(pDFTInitBuf);
    pDFTInitBuf = nullptr;
#endif
  }

  template<class DataType_>
  void FFT<DataType_>::process(const DataType_* input, std::size_t input_size) const
  {
    double factor = 1 << log2n;
#if ATK_USE_FFTW == 1
    for(std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      input_data[j][0] = input[j] / factor;
      input_data[j][1] = 0;
    }
    for(std::size_t j = std::min(input_size, size); j < size; ++j)
    {
      input_data[j][0] = 0;
      input_data[j][1] = 0;
    }
    fftw_execute(fft_plan);
#endif
#if ATK_USE_ACCELERATE == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      splitData.realp[j] = input[j] / factor;
      splitData.imagp[j] = 0;
    }
    for (std::size_t j = std::min(input_size, size); j < size; ++j)
    {
      splitData.realp[j] = 0;
      splitData.imagp[j] = 0;
    }
    vDSP_fft_zipD(fftSetup, &splitData, 1, log2n, FFT_FORWARD);
#endif
#if ATK_USE_IPP == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      pSrc[j].re = input[j] / factor;
      pSrc[j].im = 0;
    }
    for (std::size_t j = std::min(input_size, size); j < size; ++j)
    {
      pSrc[j].re = 0;
      pSrc[j].im = 0;
    }
    ippsDFTFwd_CToC_64fc(pSrc, pDst, pDFTSpec, pDFTWorkBuf);
#endif

  }
  
  template<class DataType_>
  void FFT<DataType_>::process_forward(const DataType_* input, std::complex<DataType_>* output, std::size_t input_size) const
  {
    process(input, input_size);
    for(std::size_t j = 0; j < size; ++j)
    {
#if ATK_USE_FFTW == 1
      output[j] = std::complex<DataType_>(output_freqs[j][0], output_freqs[j][1]);
#endif
#if ATK_USE_ACCELERATE == 1
      output[j] = std::complex<DataType_>(splitData.realp[j], splitData.imagp[j]);
#endif
#if ATK_USE_IPP == 1
      output[j] = std::complex<DataType_>(pDst[j].re, pDst[j].im);
#endif
    }
  }

  template<class DataType_>
  void FFT<DataType_>::process_backward(const std::complex<DataType_>* input, DataType_* output, std::size_t input_size) const
  {
#if ATK_USE_FFTW == 1
    for(std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output_freqs[j][0] = input[j].real();
      output_freqs[j][1] = input[j].imag();
    }
    fftw_execute(fft_reverse_plan);
    for(std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = input_data[j][0];
    }
#endif
#if ATK_USE_ACCELERATE == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      splitData.realp[j] = input[j].real();
      splitData.imagp[j] = input[j].imag();
    }
    vDSP_fft_zipD(fftSetup, &splitData, 1, log2n, FFT_BACKWARD);
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = splitData.realp[j];
    }
#endif
#if ATK_USE_IPP == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      pDst[j].re = input[j].real();
      pDst[j].im = input[j].imag();
    }
    ippsDFTInv_CToC_64fc(pDst, pDst, pDFTSpec, pDFTWorkBuf);
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = pDst[j].re;
    }
#endif
  }

  template<class DataType_>
  void FFT<DataType_>::process(const std::complex<DataType_>* input, std::size_t input_size) const
  {
    double factor = 1 << log2n;
#if ATK_USE_FFTW == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      input_data[j][0] = std::real(input[j]) / factor;
      input_data[j][1] = std::imag(input[j]) / factor;
    }
    for (std::size_t j = std::min(input_size, size); j < size; ++j)
    {
      input_data[j][0] = 0;
      input_data[j][1] = 0;
    }
    fftw_execute(fft_plan);
#endif
#if ATK_USE_ACCELERATE == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      splitData.realp[j] = std::real(input[j]) / factor;
      splitData.imagp[j] = std::imag(input[j]) / factor;
    }
    for (std::size_t j = std::min(input_size, size); j < size; ++j)
    {
      splitData.realp[j] = 0;
      splitData.imagp[j] = 0;
    }
    vDSP_fft_zipD(fftSetup, &splitData, 1, log2n, FFT_FORWARD);
#endif
#if ATK_USE_IPP == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      pSrc[j].re = std::real(input[j]) / factor;
      pSrc[j].im = std::imag(input[j]) / factor;
    }
    for (std::size_t j = std::min(input_size, size); j < size; ++j)
    {
      pSrc[j].re = 0;
      pSrc[j].im = 0;
    }
    ippsDFTFwd_CToC_64fc(pSrc, pDst, pDFTSpec, pDFTWorkBuf);
#endif

  }

  template<class DataType_>
  void FFT<DataType_>::process_forward(const std::complex<DataType_>* input, std::complex<DataType_>* output, std::size_t input_size) const
  {
    process(input, input_size);
    for (std::size_t j = 0; j < size; ++j)
    {
#if ATK_USE_FFTW == 1
      output[j] = std::complex<DataType_>(output_freqs[j][0], output_freqs[j][1]);
#endif
#if ATK_USE_ACCELERATE == 1
      output[j] = std::complex<DataType_>(splitData.realp[j], splitData.imagp[j]);
#endif
#if ATK_USE_IPP == 1
      output[j] = std::complex<DataType_>(pDst[j].re, pDst[j].im);
#endif
    }
  }

  template<class DataType_>
  void FFT<DataType_>::process_backward(const std::complex<DataType_>* input, std::complex<DataType_>* output, std::size_t input_size) const
  {
#if ATK_USE_FFTW == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output_freqs[j][0] = input[j].real();
      output_freqs[j][1] = input[j].imag();
    }
    fftw_execute(fft_reverse_plan);
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = std::complex<DataType_>(input_data[j][0], input_data[j][1]);
  }
#endif
#if ATK_USE_ACCELERATE == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      splitData.realp[j] = input[j].real();
      splitData.imagp[j] = input[j].imag();
    }
    vDSP_fft_zipD(fftSetup, &splitData, 1, log2n, FFT_BACKWARD);
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = std::complex<DataType_>(splitData.realp[j], splitData.imagp[j]);
    }
#endif
#if ATK_USE_IPP == 1
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      pDst[j].re = input[j].real();
      pDst[j].im = input[j].imag();
    }
    ippsDFTInv_CToC_64fc(pDst, pDst, pDFTSpec, pDFTWorkBuf);
    for (std::size_t j = 0; j < std::min(input_size, size); ++j)
    {
      output[j] = std::complex<DataType_>(pDst[j].re, pDst[j].im);
    }
#endif
  }

  template<class DataType_>
  void FFT<DataType_>::get_amp(std::vector<DataType_>& amp) const
  {
    amp.assign(size / 2 + 1, 0);
    for(std::size_t i = 0; i < size / 2 + 1; ++i)
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
#if ATK_USE_IPP == 1
      amp[i] = pDst[i].re * pDst[i].re;
      amp[i] += pDst[i].im * pDst[i].im;
      amp[i] = std::sqrt(amp[i]);
#endif
    }
  }
  
  template<class DataType_>
  void FFT<DataType_>::get_angle(std::vector<DataType_>& angle) const
  {
    angle.assign(size / 2 + 1, 0);
    for(std::size_t i = 0; i < size / 2 + 1; ++i)
    {
#if ATK_USE_FFTW == 1
      angle[i] = std::arg(std::complex<DataType_>(output_freqs[i][0], output_freqs[i][1]));
#endif
#if ATK_USE_ACCELERATE == 1
      angle[i] = std::arg(std::complex<DataType_>(splitData.realp[j], splitData.imagp[j]));
#endif
#if ATK_USE_IPP == 1
      angle[i] = std::arg(std::complex<DataType_>(pDst[i].re, pDst[i].im));
#endif
    }
  }

  template class FFT<double>;
}
