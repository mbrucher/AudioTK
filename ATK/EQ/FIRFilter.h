/**
 * \file FIRFilter.h
 */

#ifndef ATK_EQ_FIRFILTER_H
#define ATK_EQ_FIRFILTER_H

#include <ATK/config.h>
#include <ATK/EQ/config.h>

#include <gsl/gsl>

#include <cassert>
#include <cstdint>
#include <vector>

namespace ATK
{
  /**
   * FIR filter template class
   */
  template<class Coefficients >
  class ATK_EQ_EXPORT FIRFilter final : public Coefficients
  {
  protected:
    using Parent = Coefficients;
    using typename Parent::DataType;
    using typename Parent::AlignedScalarVector;

    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::coefficients_in;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

    using Parent::in_order;
    using Parent::input_delay;
    using Parent::setup;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit FIRFilter(gsl::index nb_channels = 1)
      :Parent(nb_channels)
    {
    }

    /// Move constructor
    FIRFilter(FIRFilter&& other)
    :Parent(std::move(other))
    {
    }

    void setup() override
    {
      Parent::setup();
      input_delay = in_order;
    }
    
    void process_impl(gsl::index size) const final
    {
      assert(input_sampling_rate == output_sampling_rate);
      assert(nb_input_ports == nb_output_ports);
      assert(coefficients_in.data());

      const auto* ATK_RESTRICT coefficients_in_ptr = coefficients_in.data();

      for (gsl::index channel = 0; channel < nb_input_ports; ++channel)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[channel] - static_cast<int64_t>(in_order);
        DataType* ATK_RESTRICT output = outputs[channel];

        for (gsl::index i = 0; i < size; ++i)
        {
          output[i] = 0;
        }

        for (gsl::index j = 0; j < in_order + 1; ++j)
        {
          for (gsl::index i = 0; i < size; ++i)
          {
            output[i] += coefficients_in_ptr[j] * input[i + j];
          }
        }
      }

    }
    
    /// Returns the vector of internal coefficients for the MA section 
    const AlignedScalarVector& get_coefficients_in() const
    {
      return coefficients_in;
    }
  };
  
}

#endif
