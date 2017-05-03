/**
 * \file SumFilter.h
 */

#ifndef ATK_TOOLS_SUMFILTER_H
#define ATK_TOOLS_SUMFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Sums two signals together
  template<typename DataType_>
  class ATK_TOOLS_EXPORT SumFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /// Constructor
    SumFilter(unsigned int channels = 1);
    /// Destructor
    ~SumFilter();
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
  };
}

#endif
