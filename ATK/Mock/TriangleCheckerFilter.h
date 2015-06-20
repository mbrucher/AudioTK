/**
 * \file TriangleCheckerFilter.h
 */

#ifndef ATK_MOCK_TRIANGLECHECKERFILTER_H
#define ATK_MOCK_TRIANGLECHECKERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#include "config.h"

namespace ATK
{
  template<class DataType_>
  class ATK_MOCK_EXPORT TriangleCheckerFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;

    TriangleCheckerFilter();
    virtual ~TriangleCheckerFilter();
    
    void set_amplitude(DataType amplitude);
    void set_frequency(int frequency);

  protected:
    virtual void process_impl(int64_t size) const override final;
    
    mutable double state;
    mutable bool ascending;
    DataType amplitude;
    int frequency;
  };
}

#endif
