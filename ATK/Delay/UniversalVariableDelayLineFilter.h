/**
 * \file UniversalVariableDelayLineFilter.h
 */

#ifndef ATK_DELAY_UNIVERSALVARIABLEDELAYFILTER_H
#define ATK_DELAY_UNIVERSALVARIABLEDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType>
  class UVDLF_Impl;
  /**
   * Variable delay line. Second port drives the delay. This delay must always be lower than max_delay-1, superior to 1
   */
  template<typename DataType_>
  class ATK_DELAY_EXPORT UniversalVariableDelayLineFilter : public TypedBaseFilter<DataType_>
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
    UniversalVariableDelayLineFilter(int max_delay);
    ~UniversalVariableDelayLineFilter();

    void set_central_delay(int central_delay);
    int get_central_delay() const;

    void set_blend(DataType_ blend);
    DataType_ get_blend() const;
    
    void set_feedback(DataType_ feedback);
    DataType_ get_feedback() const;
    
    void set_feedforward(DataType_ feedforward);
    DataType_ get_feedforward() const;

    virtual void full_setup() override final;
  protected:
    virtual void process_impl(int64_t size) const override final;
    
    std::unique_ptr<UVDLF_Impl<DataType_> > impl;

    /// Max delay for the delay line
    int64_t max_delay;
    int central_delay;
    DataType_ blend;
    DataType_ feedback;
    DataType_ feedforward;
  };
}

#endif
