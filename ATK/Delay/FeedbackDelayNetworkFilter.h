/**
 * \file FeedbackDelayNetworkFilter.h
 */

#ifndef ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_H
#define ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_H

#include <array>
#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

#if ATK_EIGEN == 1

namespace ATK
{
  /// A FDN class with custom mixture matrix
  template<typename Mixture>
  class ATK_DELAY_EXPORT FeedbackDelayNetworkFilter final : public TypedBaseFilter<typename Mixture::DataType>
  {
    class HFDN_Impl;
  protected:
    typedef typename Mixture::DataType DataType;
    typedef TypedBaseFilter<DataType> Parent;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

    static constexpr auto nb_channels = Mixture::nb_channels;

  public:
    /*!
    * @brief construct the filter with a maximum delay line size
    * @param max_delay is the maximum delay allowed
    */
    FeedbackDelayNetworkFilter(std::size_t max_delay);
    /// Destructor
    ~FeedbackDelayNetworkFilter();

    /// Set the initial delay from a channel
    void set_delay(unsigned int channel, std::size_t delay);
    /// Gets the initial delay from a channel
    std::size_t get_delay(unsigned int channel) const;

    /// Sets the input gain of a channel (between -1 and 1)
    void set_ingain(unsigned int channel, DataType ingain);
    /// Gets the input gain of a channel
    DataType get_ingain(unsigned int channel) const;

    /// Sets the feedback of a channel
    void set_feedback(unsigned int channel, DataType feedback);
    /// Gets the feedback of a channel
    DataType get_feedback(unsigned int channel) const;

    /// Sets the output gain of a channel (between -1 and 1)
    void set_outgain(unsigned int channel, DataType ingain);
    /// Gets the output gain of a channel
    DataType get_outgain(unsigned int channel) const;

    virtual void full_setup() final;
  protected:
    virtual void process_impl(std::size_t size) const final;

  private:
    // internal state
    std::unique_ptr<HFDN_Impl> impl;
    std::array<std::size_t, nb_channels> delay;
    /// Max delay for the delay line
    std::size_t max_delay;
  };
}

#endif
#endif
