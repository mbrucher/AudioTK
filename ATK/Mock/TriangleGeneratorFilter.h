/**
 * \file TriangleGeneratorFilter.h
 */

#ifndef ATK_MOCK_TRIANGLEGENERATORFILTER_H
#define ATK_MOCK_TRIANGLEGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#include "config.h"

namespace ATK
{
  template<class DataType_>
  class ATK_MOCK_EXPORT TriangleGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;

    TriangleGeneratorFilter();
    virtual ~TriangleGeneratorFilter();
    
    void set_amplitude(DataType_ amplitude);
    void set_frequency(int frequency);
    
  protected:
    virtual void process_impl(long size);

    double state;
    bool ascending;
    DataType_ amplitude;
    int frequency;
  };
}

#endif
