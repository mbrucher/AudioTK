/**
 * \file SimpleSinusGeneratorFilter.h
 */

#ifndef ATK_MOCK_SIMPLESINUSGENERATORFILTER_H
#define ATK_MOCK_SIMPLESINUSGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#include "config.h"

namespace ATK
{
  /// Filter creating a sinus signal (usng std::sin, so not precise enough and fast enough)
  template<class DataType_>
  class ATK_MOCK_EXPORT SimpleSinusGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;
    
    /// Constructor
    SimpleSinusGeneratorFilter();
    /// Destructor
    virtual ~SimpleSinusGeneratorFilter();
    
    /// Sets the amplitude of the sinusoid
    void set_amplitude(DataType_ amplitude);
    /// Sets the frequency of the sinusoid
    void set_frequency(int frequency);
    
  protected:
    virtual void process_impl(std::size_t size) const override final;

  private:
    mutable double state;
    DataType_ amplitude;
    int frequency;
  };
}

#endif
