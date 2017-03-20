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
  /// Simple low pass reverb filter
  template<typename DataType_>
  class ATK_REVERBERATION_EXPORT LowPassReverbFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
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
    /*!
    * @brief construct the filter with a maximum delay line size
    * @param max-delay is the maximum delay allowed
    */
    LowPassReverbFilter(std::size_t max_delay);
    /// Destructor
    ~LowPassReverbFilter();

    /// Changes the delay used for the filter
    void set_delay(std::size_t delay);
    /// Returns the elay used for the system
    std::size_t get_delay() const;

    /// Sets feedback amount (sum of cutoff and feedback must be between 0 and 1)
    void set_feedback(DataType_ feedback);
    /// Gets feedback amount
    DataType_ get_feedback() const;
    /// Sets cutoff amount (sum of cutoff and feedback must be between 0 and 1)
    void set_cutoff(DataType_ cutoff);
    /// Gets cutoff amount
    DataType_ get_cutoff() const;
  protected:
    virtual void process_impl(std::size_t size) const override final;
  private:
    std::size_t delay;
    DataType_ feedback;
    DataType_ cutoff;
  };
}

#endif
