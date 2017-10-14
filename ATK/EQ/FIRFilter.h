/**
 * \file FIRFilter.h
 */

#ifndef ATK_EQ_FIRFILTER_H
#define ATK_EQ_FIRFILTER_H

#include <cassert>
#include <cstdint>
#include <vector>

#include <ATK/config.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  /**
   * FIR filter template class
   */
  template<class Coefficients >
  class ATK_EQ_EXPORT FIRFilter final : public Coefficients
  {
  public:
    typedef Coefficients Parent;
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
    FIRFilter(std::size_t nb_channels = 1)
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
    
    virtual void process_impl(std::size_t size) const override
    {
      assert(input_sampling_rate == output_sampling_rate);
      assert(nb_input_ports == nb_output_ports);
      assert(coefficients_in.data());

      const auto* ATK_RESTRICT coefficients_in_ptr = coefficients_in.data();

      for (unsigned int channel = 0; channel < nb_input_ports; ++channel)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[channel] - static_cast<int64_t>(in_order);
        DataType* ATK_RESTRICT output = outputs[channel];

        for (std::size_t i = 0; i < size; ++i)
        {
          output[i] = 0;
        }

        for (unsigned int j = 0; j < in_order + 1; ++j)
        {
          for (std::size_t i = 0; i < size; ++i)
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
