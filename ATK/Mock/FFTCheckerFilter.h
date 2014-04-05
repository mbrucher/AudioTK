/**
 * \file FFTCheckerFilter.h
 */

#ifndef ATK_MOCK_FFTCHECKERFILTER_H
#define ATK_MOCK_FFTCHECKERFILTER_H

#include <ATK/config.h>

#if ATK_USE_FFTW == 1
#include <fftw3.h>
#endif
#if ATK_USE_ACCELERATE == 1
#include <Accelerate/Accelerate.h>
#endif

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<class DataType_>
  class FFTCheckerFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    
    FFTCheckerFilter();
    virtual ~FFTCheckerFilter();
    
    void set_checks(const std::vector<std::pair<int, DataType> >& frequency_checks);
    
  protected:
    virtual void process_impl(long size);
    virtual void setup();
    
    std::vector<std::pair<int, DataType> > frequency_checks;

#if ATK_USE_FFTW == 1
    fftw_plan fft_plan;
    fftw_complex* input_data;
    fftw_complex* output_freqs;
#endif

#if ATK_USE_ACCELERATE == 1
    int log2n;
    FFTSetupD fftSetup;
    DSPDoubleSplitComplex splitData;
    double* output_freqs;
#endif
  };
}

#endif
