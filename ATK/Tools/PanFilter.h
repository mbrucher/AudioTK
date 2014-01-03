/**
 * \file PanFilter.h
 */

#ifndef ATK_TOOLS_PANFILTER_H
#define ATK_TOOLS_PANFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class PanFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;

  public:
    PanFilter();
    ~PanFilter();
    
  protected:
    virtual void process_impl(int size);

  };
}

#endif
