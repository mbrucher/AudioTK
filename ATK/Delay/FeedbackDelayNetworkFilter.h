/**
 * \file FeedbackDelayNetworkFilter.h
 */

#ifndef ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_H
#define ATK_DELAY_FEEDBACKDELAYNETWORKFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>

#include <array>
#include <vector>

namespace ATK
{
  /// A FDN class with custom mixture matrix
  template<typename Mixture>
  class ATK_DELAY_EXPORT FeedbackDelayNetworkFilter final : public TypedBaseFilter<typename Mixture::DataType>
  {
    class HFDN_Impl;
  protected:
    using DataType = typename Mixture::DataType;
    using Parent = TypedBaseFilter<DataType>;
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
    explicit FeedbackDelayNetworkFilter(gsl::index max_delay);
    /// Destructor
    ~FeedbackDelayNetworkFilter() override;

    /// Set the initial delay from a channel
    void set_delay(unsigned int channel, gsl::index delay);
    /// Gets the initial delay from a channel
    gsl::index get_delay(unsigned int channel) const;

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

    void full_setup() final;
  protected:
    void process_impl(gsl::index size) const final;

  private:
    // internal state
    std::unique_ptr<HFDN_Impl> impl;
    std::array<gsl::index, nb_channels> delay;
    /// Max delay for the delay line
    gsl::index max_delay{0};
  };
}

#endif
