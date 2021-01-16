/**
 * \file UniversalFixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H
#define ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>
#include <ATK/Delay/DelayInterface.h>

#include <vector>

namespace ATK
{
  /// Fixed delay line for fixed delays
  template<typename DataType_>
  class ATK_DELAY_EXPORT UniversalFixedDelayLineFilter final : public TypedBaseFilter<DataType_>, public DelayInterface, public UniversalDelayInterface<typename TypeTraits<DataType_>::Scalar>
  {
    class UFDLF_Impl;
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;
    using Scalar = typename TypeTraits<DataType>::Scalar;

  public:
    /*!
    * @brief construct the filter with a maximum delay line size
    * @param max-delay is the maximum delay allowed
    */
    explicit UniversalFixedDelayLineFilter(gsl::index max_delay);
    /// Destructor
    ~UniversalFixedDelayLineFilter() override;

    /// Sets the initial delay
    void set_delay(gsl::index delay) override;
    /// Gets the initial delay
    gsl::index get_delay() const override;

    /// Sets the blend (between -1 and 1)
    void set_blend(Scalar blend) override;
    /// Gets the blend
    Scalar get_blend() const override;

    /// Sets feedback amount (between -1 and 1)
    void set_feedback(Scalar feedback) override;
    /// Gets feedback amount
    Scalar get_feedback() const override;

    /// Sets feedforward amount (between -1 and 1)
    void set_feedforward(Scalar feedforward) override;
    /// Gets feedforward amount
    Scalar get_feedforward() const override;

    void full_setup() final;
  protected:
    void process_impl(gsl::index size) const final;

  private:
    // internal state
    std::unique_ptr<UFDLF_Impl> impl;
    gsl::index delay = 100;
    Scalar blend{0};
    Scalar feedback{0};
    Scalar feedforward{1};
  };
}

#endif
