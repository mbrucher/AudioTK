/**
 * \file LowPassReverbFilter.h
 */

#ifndef ATK_REVERBERATION_LOWPASSREVERBFILTER_H
#define ATK_REVERBERATION_LOWPASSREVERBFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Reverberation/config.h>

#include <vector>

namespace ATK
{
  /// Simple low pass reverb filter
  template<typename DataType_>
  class ATK_REVERBERATION_EXPORT LowPassReverbFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_delay;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    /*!
    * @brief construct the filter with a maximum delay line size
    * @param max_delay is the maximum delay allowed
    */
    explicit LowPassReverbFilter(gsl::index max_delay);
    /// Destructor
    ~LowPassReverbFilter() override = default;

    /// Changes the delay used for the filter
    void set_delay(gsl::index delay);
    /// Returns the elay used for the system
    gsl::index get_delay() const;

    /// Sets feedback amount (sum of cutoff and feedback must be between 0 and 1)
    void set_feedback(DataType_ feedback);
    /// Gets feedback amount
    DataType_ get_feedback() const;
    /// Sets cutoff amount (sum of cutoff and feedback must be between 0 and 1)
    void set_cutoff(DataType_ cutoff);
    /// Gets cutoff amount
    DataType_ get_cutoff() const;
  protected:
    void process_impl(gsl::index size) const final;
  private:
    gsl::index delay{0};
    DataType_ feedback{0};
    DataType_ cutoff{0};
  };
}

#endif
