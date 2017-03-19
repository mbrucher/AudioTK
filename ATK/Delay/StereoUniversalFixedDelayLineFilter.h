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
  /// A stereo/ping-pong delay effect
  template<typename DataType_>
  class ATK_DELAY_EXPORT StereoUniversalFixedDelayLineFilter : public TypedBaseFilter<DataType_>
  {
    class SUFDLF_Impl;
  protected:
    /// Simplify parent calls
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
    /*!
    * @brief construct the filter with a maximum delay line size
    * @param max-delay is the maximum delay allowed
    */
    StereoUniversalFixedDelayLineFilter(std::size_t max_delay);
    /// Destructor
    ~StereoUniversalFixedDelayLineFilter();

    /// Sets the initial delay from channel 1
    void set_delay_ch1(std::size_t delay);
    /// Gets the initial delay from channel 1
    std::size_t get_delay_ch1() const;
    /// Sets the initial delay from channel 2
    void set_delay_ch2(std::size_t delay);
    /// Gets the initial delay from channel 2
    std::size_t get_delay_ch2() const;

    /// Sets the blend of channel 1 (between -1 and 1)
    void set_blend_ch1(DataType_ blend);
    /// Gets the blend of channel 1
    DataType_ get_blend_ch1() const;
    /// Sets the blend of channel 2 (between -1 and 1)
    void set_blend_ch2(DataType_ blend);
    /// Gets the blend of channel 2
    DataType_ get_blend_ch2() const;

    /// Sets the feedback from channel 1 to channel 1 (between -1 and 1)
    void set_feedback_ch1_ch1(DataType_ feedback);
    /// Gets the feedback from channel 1 to channel 1
    DataType_ get_feedback_ch1_ch1() const;
    /// Sets the feedback from channel 1 to channel 2 (between -1 and 1)
    void set_feedback_ch1_ch2(DataType_ feedback);
    /// Gets the feedback from channel 1 to channel 2
    DataType_ get_feedback_ch1_ch2() const;
    /// Sets the feedback from channel 2 to channel 1 (between -1 and 1)
    void set_feedback_ch2_ch1(DataType_ feedback);
    /// Gets the feedback from channel 2 to channel 1
    DataType_ get_feedback_ch2_ch1() const;
    /// Sets the feedback from channel 2 to channel 2 (between -1 and 1)
    void set_feedback_ch2_ch2(DataType_ feedback);
    /// Gets the feedback from channel 2 to channel 2
    DataType_ get_feedback_ch2_ch2() const;

    /// Sets the feedforward from channel 1 to channel 1 (between -1 and 1)
    void set_feedforward_ch1_ch1(DataType_ feedforward);
    /// Gets the feedforward from channel 1 to channel 1
    DataType_ get_feedforward_ch1_ch1() const;
    /// Sets the feedforward from channel 1 to channel 2 (between -1 and 1)
    void set_feedforward_ch1_ch2(DataType_ feedforward);
    /// Gets the feedforward from channel 1 to channel 2
    DataType_ get_feedforward_ch1_ch2() const;
    /// Sets the feedforward from channel 2 to channel 1 (between -1 and 1)
    void set_feedforward_ch2_ch1(DataType_ feedforward);
    /// Gets the feedforward from channel 2 to channel 1
    DataType_ get_feedforward_ch2_ch1() const;
    /// Sets the feedforward from channel 2 to channel 2 (between -1 and 1)
    void set_feedforward_ch2_ch2(DataType_ feedforward);
    /// Gets the feedforward from channel 2 to channel 2
    DataType_ get_feedforward_ch2_ch2() const;

    virtual void full_setup() override final;
  protected:
    virtual void process_impl(int64_t size) const override final;

  private:
    // internal state
    std::unique_ptr<SUFDLF_Impl> impl;
    std::size_t delay_l;
    std::size_t delay_r;
    /// Max delay for the delay line
    std::size_t max_delay;
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
