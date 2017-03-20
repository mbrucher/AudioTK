/**
 * \file FFTCheckerFilter.h
 */

#ifndef ATK_MOCK_FFTCHECKERFILTER_H
#define ATK_MOCK_FFTCHECKERFILTER_H

#include "config.h"

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Utility/FFT.h>

namespace ATK
{
  /// Checks the input signal has a specific spectrum template
  template<class DataType_>
  class ATK_MOCK_EXPORT FFTCheckerFilter : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    
    /// Constructor
    FFTCheckerFilter();
    /// Destructor
    virtual ~FFTCheckerFilter();
    
    /// Sets the template we require
    void set_checks(const std::vector<std::pair<int, DataType> >& frequency_checks);
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
    virtual void setup() override final;

  private:
    std::vector<std::pair<int, DataType> > frequency_checks;
    std::unique_ptr<FFT<DataType> > FFTimpl;
  };
}

#endif
