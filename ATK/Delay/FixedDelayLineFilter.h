/**
 * \file FixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_FIXEDDELAYFILTER_H
#define ATK_DELAY_FIXEDDELAYFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>
#include <ATK/Delay/DelayInterface.h>

#include <vector>

namespace ATK
{
  /// Fixed delay line, max_delay should always be higher than the actual delay
  template<typename DataType_>
  class ATK_DELAY_EXPORT FixedDelayLineFilter final : public TypedBaseFilter<DataType_>, public DelayInterface
  {
    class FDLF_Impl;
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
     * @param max_delay is the maximum delay allowed
     */
    explicit FixedDelayLineFilter(gsl::index max_delay);
    /// Destructor
    ~FixedDelayLineFilter() override;
    
    /// Changes the delay used for the filter
    void set_delay(gsl::index delay) override;
    /// Returns the elay used for the system
    gsl::index get_delay() const override;

    void full_setup() final;
  protected:
    void process_impl(gsl::index size) const final;

  private:
    std::unique_ptr<FDLF_Impl> impl;

    gsl::index delay{0};
  };
}

#endif
