/**
 * \file UniversalFixedDelayLineFilter.h
 */

#ifndef ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H
#define ATK_DELAY_UNIVERSALFIXEDDELAYFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>

namespace ATK
{
  /// Fixed delay line for fixed delays
  template<typename DataType_>
  class ATK_DELAY_EXPORT UniversalFixedDelayLineFilter final : public TypedBaseFilter<DataType_>
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
    void set_delay(std::size_t delay);
    /// Gets the initial delay
    std::size_t get_delay() const;

    /// Sets the blend (between -1 and 1)
    void set_blend(Scalar blend);
    /// Gets the blend
    Scalar get_blend() const;

    /// Sets feedback amount (between -1 and 1)
    void set_feedback(Scalar feedback);
    /// Gets feedback amount
    Scalar get_feedback() const;

    /// Sets feedforward amount (between -1 and 1)
    void set_feedforward(Scalar feedforward);
    /// Gets feedforward amount
    Scalar get_feedforward() const;

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
