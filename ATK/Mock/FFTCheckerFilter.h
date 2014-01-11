/**
 * \file FFTCheckerFilter.h
 */

#ifndef ATK_MOCK_FFTCHECKERFILTER_H
#define ATK_MOCK_FFTCHECKERFILTER_H

#ifdef __APPLE__
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
    
    void set_amplitude(DataType amplitude);
    void set_frequency(int frequency);
    
  protected:
    virtual void process_impl(int size);
    
    DataType amplitude;
    int frequency;
    
#ifdef __APPLE__
    int log2n;
    FFTSetupD fftSetup;
    DSPDoubleSplitComplex splitData;
#endif
  };
}

#endif
