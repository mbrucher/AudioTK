/**
 * \file FFTCheckerFilter.h
 */

#ifndef ATK_MOCK_FFTCHECKERFILTER_H
#define ATK_MOCK_FFTCHECKERFILTER_H

#include "config.h"

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/FFT.h>

namespace ATK
{
  template<class DataType_>
  class ATK_MOCK_EXPORT FFTCheckerFilter : public TypedBaseFilter<DataType_>
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
    virtual void process_impl(std::int64_t size) const override final;
    virtual void setup() override final;
    
    std::vector<std::pair<int, DataType> > frequency_checks;
    std::unique_ptr<FFT<DataType> > FFTimpl;
  };
}

#endif
