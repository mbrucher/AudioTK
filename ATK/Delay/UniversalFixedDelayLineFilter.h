/**
 * \file UniversalFixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H
#define ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Gain "compressor". Has twice as many inputs channels as it has output channels
   * Even channels are signal, odd channels are gains, results is the product of both
   */
  template<typename DataType_>
  class ATK_DELAY_EXPORT UniversalFixedDelayLineFilter : public TypedBaseFilter<DataType_>
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
    UniversalFixedDelayLineFilter(int max_delay);
    ~UniversalFixedDelayLineFilter();

    void set_delay(std::int64_t delay);
    std::int64_t get_delay() const;

    void set_blend(DataType_ blend);
    DataType_ get_blend() const;

    void set_feedback(DataType_ feedback);
    DataType_ get_feedback() const;

    void set_feedforward(DataType_ feedforward);
    DataType_ get_feedforward() const;

  protected:
    virtual void process_impl(std::int64_t size);

    std::vector<DataType> delay_line;
    std::vector<DataType> processed_input;
    std::int64_t delay;
    DataType_ blend;
    DataType_ feedback;
    DataType_ feedforward;
  };
}

#endif
