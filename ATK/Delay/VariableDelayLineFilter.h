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

  protected:
    virtual void process_impl(std::int64_t size);
    
    /// Delay line contains the last size elements + max_delay of the last delay line
    std::vector<DataType> delay_line;
    
    /// Integer portion of the delay for the last processed chunk
    std::vector<int64_t> integer_delay;
    /// Fractional portion of the delay for the last processed chunk, used for the interpolation
    std::vector<DataType> fractional_delay;
    
    /// Max delay for the delay line
    std::int64_t max_delay;
  };
}

#endif
