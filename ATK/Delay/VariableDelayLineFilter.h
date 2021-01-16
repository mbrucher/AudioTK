/**
 * \file VariableDelayLineFilter.h
 */

#ifndef ATK_DELAY_VARIABLEDELAYFILTER_H
#define ATK_DELAY_VARIABLEDELAYFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>

#include <vector>

namespace ATK
{
  /// Variable delay line. Second port drives the delay. This delay must always be lower than max_delay
  template<typename DataType_>
  class ATK_DELAY_EXPORT VariableDelayLineFilter final : public TypedBaseFilter<DataType_>
  {
    class VDLF_Impl;
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
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
    explicit VariableDelayLineFilter(gsl::index max_delay);
    /// Destructor
    ~VariableDelayLineFilter() override;

    void full_setup() final;
  protected:
    void process_impl(gsl::index size) const final;

  private:
    std::unique_ptr<VDLF_Impl> impl;
    
    /// Max delay for the delay line
    gsl::index max_delay{0};
  };
}

#endif
