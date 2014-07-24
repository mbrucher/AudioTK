/**
 * \file MaxFilter.h
 */

#ifndef ATK_TOOLS_MAXFILTER_H
#define ATK_TOOLS_MAXFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType_>
  class ATK_TOOLS_EXPORT MaxFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    
  public:
    MaxFilter();
    ~MaxFilter();
    
  protected:
    virtual void process_impl(std::int64_t size);
  };
}

#endif
