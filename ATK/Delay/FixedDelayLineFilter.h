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
    
    void set_delay(std::int64_t delay);
    std::int64_t get_delay() const;

  protected:
    virtual void process_impl(std::int64_t size);
    
    std::vector<DataType> delay_line;
    std::int64_t delay;
  };
}

#endif
