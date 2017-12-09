/**
 * \file UniversalFixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H
#define ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>
#include <ATK/Delay/DelayInterface.h>

namespace ATK
{
  /// Fixed delay line for fixed delays
  template<typename DataType_>
  class ATK_DELAY_EXPORT UniversalFixedDelayLineFilter final : public TypedBaseFilter<DataType_>, public DelayInterface, public UniversalDelayInterface<typename TypeTraits<DataType_>::Scalar>
  {
    class UFDLF_Impl;
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;
    typedef typename TypeTraits<DataType>::Scalar Scalar;

  public:
    /*!
    * @brief construct the filter with a maximum delay line size
    * @param max-delay is the maximum delay allowed
    */
    UniversalFixedDelayLineFilter(std::size_t max_delay);
    /// Destructor
    ~UniversalFixedDelayLineFilter() override;

    /// Sets the initial delay
    void set_delay(std::size_t delay) override;
    /// Gets the initial delay
    std::size_t get_delay() const override;

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
    void process_impl(std::size_t size) const final;

  private:
    // internal state
    std::unique_ptr<UFDLF_Impl> impl;
    std::size_t delay;
    Scalar blend;
    Scalar feedback;
    Scalar feedforward;
  };
}

#endif
