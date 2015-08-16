/**
 * \file SimpleSinusGeneratorFilter.h
 */

#ifndef ATK_MOCK_SIMPLESINUSGENERATORFILTER_H
#define ATK_MOCK_SIMPLESINUSGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#include "config.h"

namespace ATK
{
  template<class DataType_>
  class ATK_MOCK_EXPORT SimpleSinusGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;
    
    SimpleSinusGeneratorFilter();
    virtual ~SimpleSinusGeneratorFilter();
    
    void set_amplitude(DataType_ amplitude);
    void set_frequency(int frequency);
    
  protected:
    virtual void process_impl(int64_t size) const override final;
    
    mutable double state;
    DataType_ amplitude;
    int frequency;
  };
}

#endif
