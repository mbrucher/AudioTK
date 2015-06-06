/**
 * \file StereoUniversalFixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_STEREOUNIVERSALFIXEDDELAYFILTER_H
#define ATK_DELAY_STEREOUNIVERSALFIXEDDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType>
  class SUFDLF_Impl;
  /**
   * Gain "compressor". Has twice as many inputs channels as it has output channels
   * Even channels are signal, odd channels are gains, results is the product of both
   */
  template<typename DataType_>
  class ATK_DELAY_EXPORT StereoUniversalFixedDelayLineFilter : public TypedBaseFilter<DataType_>
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
    StereoUniversalFixedDelayLineFilter(int max_delay);
    ~StereoUniversalFixedDelayLineFilter();

    /// Set the initial delay from channel 1
    void set_delay_ch1(std::int64_t delay);
    std::int64_t get_delay_ch1() const;
    /// Set the initial delay from channel 2
    void set_delay_ch2(std::int64_t delay);
    std::int64_t get_delay_ch2() const;

    void set_blend_ch1(DataType_ blend);
    DataType_ get_blend_ch1() const;
    void set_blend_ch2(DataType_ blend);
    DataType_ get_blend_ch2() const;

    /// Set the feedback from channel 1 to channel 1
    void set_feedback_ch1_ch1(DataType_ feedback);
    DataType_ get_feedback_ch1_ch1() const;
    /// Set the feedback from channel 1 to channel 2
    void set_feedback_ch1_ch2(DataType_ feedback);
    DataType_ get_feedback_ch1_ch2() const;
    /// Set the feedback from channel 2 to channel 1
    void set_feedback_ch2_ch1(DataType_ feedback);
    DataType_ get_feedback_ch2_ch1() const;
    /// Set the feedback from channel 2 to channel 2
    void set_feedback_ch2_ch2(DataType_ feedback);
    DataType_ get_feedback_ch2_ch2() const;

    void set_feedforward_ch1_ch1(DataType_ feedforward);
    DataType_ get_feedforward_ch1_ch1() const;
    void set_feedforward_ch1_ch2(DataType_ feedforward);
    DataType_ get_feedforward_ch1_ch2() const;
    void set_feedforward_ch2_ch1(DataType_ feedforward);
    DataType_ get_feedforward_ch2_ch1() const;
    void set_feedforward_ch2_ch2(DataType_ feedforward);
    DataType_ get_feedforward_ch2_ch2() const;

    virtual void full_setup() override final;
  protected:
    virtual void process_impl(std::int64_t size) const override final;

    // internal state
    std::unique_ptr<SUFDLF_Impl<DataType_> > impl;

    std::int64_t delay_l;
    std::int64_t delay_r;
    /// Max delay for the delay line
    std::int64_t max_delay;
    DataType_ blend_l;
    DataType_ blend_r;
    DataType_ feedback_l_l;
    DataType_ feedback_l_r;
    DataType_ feedback_r_l;
    DataType_ feedback_r_r;
    DataType_ feedforward_l_l;
    DataType_ feedforward_l_r;
    DataType_ feedforward_r_l;
    DataType_ feedforward_r_r;
  };
}

#endif
