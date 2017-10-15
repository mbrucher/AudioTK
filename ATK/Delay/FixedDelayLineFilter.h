/**
 * \file FixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_FIXEDDELAYFILTER_H
#define ATK_DELAY_FIXEDDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Fixed delay line, max_delay should always be higher than the actual delay
  template<typename DataType_>
  class ATK_DELAY_EXPORT FixedDelayLineFilter final : public TypedBaseFilter<DataType_>
  {
    class FDLF_Impl;
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
     * @param max_delay is the maximum delay allowed
     */
    FixedDelayLineFilter(std::size_t max_delay);
    /// Destructor
    ~FixedDelayLineFilter();
    
    /// Changes the delay used for the filter
    void set_delay(std::size_t delay);
    /// Returns the elay used for the system
    std::size_t get_delay() const;

    virtual void full_setup() final;
  protected:
    virtual void process_impl(std::size_t size) const final;

  private:
    std::unique_ptr<FDLF_Impl> impl;

    std::size_t delay;
  };
}

#endif
