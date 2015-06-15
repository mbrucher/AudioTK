/**
 * \file VariableDelayLineFilter.h
 */

#ifndef ATK_DELAY_VARIABLEDELAYFILTER_H
#define ATK_DELAY_VARIABLEDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType>
  class VDLF_Impl;

  /**
   * Variable delay line. Second port drives the delay. This delay must always be lower than max_delay
   */
  template<typename DataType_>
  class ATK_DELAY_EXPORT VariableDelayLineFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    VariableDelayLineFilter(int max_delay);
    ~VariableDelayLineFilter();

    virtual void full_setup() override final;
  protected:
    virtual void process_impl(std::int64_t size) const override final;
    
    std::unique_ptr<VDLF_Impl<DataType_> > impl;
    
    /// Max delay for the delay line
    std::int64_t max_delay;
  };
}

#endif
