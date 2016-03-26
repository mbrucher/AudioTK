/**
 * \file SumFilter.h
 */

#ifndef ATK_TOOLS_SUMFILTER_H
#define ATK_TOOLS_SUMFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Sums two signqls together
  template<typename DataType_>
  class ATK_TOOLS_EXPORT SumFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    
  public:
    /// Constructor
    SumFilter();
    /// Destructor
    ~SumFilter();
    
  protected:
    virtual void process_impl(int64_t size) const override final;
  };
}

#endif
