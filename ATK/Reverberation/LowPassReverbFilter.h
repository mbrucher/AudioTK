/**
 * \file LowPassReverbFilter.h
 */

#ifndef ATK_REVERBERATION_LOWPASSREVERBFILTER_H
#define ATK_REVERBERATION_LOWPASSREVERBFILTER_H

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
  class ATK_REVERBERATION_EXPORT LowPassReverbFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::input_delay;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    LowPassReverbFilter(int max_delay);
    ~LowPassReverbFilter();

    void set_delay(int64_t delay);
    int64_t get_delay() const;

    void set_feedback(DataType_ feedback);
    DataType_ get_feedback() const;
    void set_cutoff(DataType_ cutoff);
    DataType_ get_cutoff() const;
  protected:
    virtual void process_impl(int64_t size) const override final;

    int64_t delay;
    DataType_ feedback;
    DataType_ cutoff;
  };
}

#endif
