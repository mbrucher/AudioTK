/**
 * \file UniversalVariableDelayLineFilter.h
 */

#ifndef ATK_DELAY_UNIVERSALVARIABLEDELAYFILTER_H
#define ATK_DELAY_UNIVERSALVARIABLEDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Variable delay line. Second port drives the delay. This delay must always be lower than max_delay-1, superior to 1
  template<typename DataType_>
  class ATK_DELAY_EXPORT UniversalVariableDelayLineFilter final : public TypedBaseFilter<DataType_>
  {
    class UVDLF_Impl;
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
    UniversalVariableDelayLineFilter(std::size_t max_delay);
    /// Destructor
    ~UniversalVariableDelayLineFilter();

    /// Sets the central delay
    void set_central_delay(std::size_t central_delay);
    /// Gets the central delay
    std::size_t get_central_delay() const;

    /// Sets the blend (between -1 and 1)
    void set_blend(DataType_ blend);
    /// Gets the blend
    DataType_ get_blend() const;

    /// Sets feedback amount (between -1 and 1)
    void set_feedback(DataType_ feedback);
    /// Gets feedback amount
    DataType_ get_feedback() const;

    /// Sets feedforward amount (between -1 and 1)
    void set_feedforward(DataType_ feedforward);
    /// Gets feedforward amount
    DataType_ get_feedforward() const;

    virtual void full_setup() override final;
  protected:
    virtual void process_impl(std::size_t size) const override final;
    
  private:
    std::unique_ptr<UVDLF_Impl> impl;

    /// Max delay for the delay line
    std::size_t max_delay;
    std::size_t central_delay;
    DataType_ blend;
    DataType_ feedback;
    DataType_ feedforward;
  };
}

#endif
