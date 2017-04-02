/**
 * \file MultipleUniversalFixedDelayLineFilter
 */

#ifndef ATK_DELAY_MULTIPLEUNIVERSALFIXEDDELAYFILTER_H
#define ATK_DELAY_MULTIPLEUNIVERSALFIXEDDELAYFILTER_H

#include <array>
#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// A stereo/ping-pong delay effect
  template<class DataType_, unsigned int nb_channels>
  class ATK_DELAY_EXPORT MultipleUniversalFixedDelayLineFilter final : public TypedBaseFilter<DataType_>
  {
    class SUFDLF_Impl;
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
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
    MultipleUniversalFixedDelayLineFilter(std::size_t max_delay);
    /// Destructor
    ~MultipleUniversalFixedDelayLineFilter();

    /// Set the initial delay from a channel
    void set_delay(unsigned int channel, std::size_t delay);
    /// Gets the initial delay from a channel
    std::size_t get_delay(unsigned int channel) const;
    
    /// Sets the blend of channel 1 (between -1 and 1)
    void set_blend(unsigned int channel, double blend);
    /// Gets the blend of a channel
    double get_blend(unsigned int channel) const;
    
    /// Sets the feedback from channel to channel
    void set_feedback(unsigned int from_channel, unsigned int to_channel, double feedback);
    /// Gets the feedback from channel to channel
    double get_feedback(unsigned int from_channel, unsigned int to_channel) const;
    
    /// Sets the feedforward from channel to channel
    void set_feedforward(unsigned int from_channel, unsigned int to_channel, double feedforward);
    /// Gets the feedforward from channel to channel
    double get_feedforward(unsigned int from_channel, unsigned int to_channel) const;

    virtual void full_setup() override final;
  protected:
    virtual void process_impl(std::size_t size) const override final;

  private:
    // internal state
    std::unique_ptr<SUFDLF_Impl> impl;
    std::array<std::size_t, nb_channels> delay;
    /// Max delay for the delay line
    std::size_t max_delay;
    std::array<double, nb_channels> blend;
    std::array<double, nb_channels*nb_channels> feedback;
    std::array<double, nb_channels*nb_channels> feedforward;
  };
}

#endif
