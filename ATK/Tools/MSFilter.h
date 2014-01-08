/**
 * \file MSFilter.h
 */

#ifndef ATK_TOOLS_MSFILTER_H
#define ATK_TOOLS_MSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class MiddleSideFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    
  public:
    MiddleSideFilter();
    ~MiddleSideFilter();
    
  protected:
    virtual void process_impl(int size);
  };
}

#endif
