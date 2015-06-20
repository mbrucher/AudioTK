/**
 * \file FixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_FIXEDDELAYFILTER_H
#define ATK_DELAY_FIXEDDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType>
  class FDLF_Impl;

  /**
   * Fixed delay line, max_delay should always be higher than the actual delay
   */
  template<typename DataType_>
  class ATK_DELAY_EXPORT FixedDelayLineFilter : public TypedBaseFilter<DataType_>
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
    FixedDelayLineFilter(int max_delay);
    ~FixedDelayLineFilter();
    
    void set_delay(int64_t delay);
    int64_t get_delay() const;

    virtual void full_setup() override final;
  protected:
    virtual void process_impl(int64_t size) const override final;

    // internal state
    std::unique_ptr<FDLF_Impl<DataType_> > impl;

    int64_t delay;
  };
}

#endif
