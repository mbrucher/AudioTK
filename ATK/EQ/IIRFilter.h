/**
 * \file IIRFilter.h
 */

#ifndef ATK_EQ_IIRFILTER_H
#define ATK_EQ_IIRFILTER_H

#include <cassert>
#include <vector>

#include "config.h"

namespace ATK
{
  /// IIR filter template class (Direct Form I)
  template<class Coefficients >
  class ATK_EQ_EXPORT IIRFilter: public Coefficients
  {
  public:
    /// Simplify parent calls
    typedef Coefficients Parent;
    using typename Parent::DataType;
    using typename Parent::AlignedVector;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    
    using Parent::in_order;
    using Parent::out_order;
    using Parent::input_delay;
    using Parent::output_delay;
    using Parent::setup;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    IIRFilter(int nb_channels = 1)
      :Parent(nb_channels)
    {
    }

    /// Move constructor
    IIRFilter(IIRFilter&& other)
    :Parent(std::move(other))
    {
    }

    void setup() override final
    {
      Parent::setup();
      input_delay = in_order;
      output_delay = out_order;
    }
    
    virtual void process_impl(int64_t size) const override final
    {
      assert(input_sampling_rate == output_sampling_rate);
      assert(nb_input_ports == nb_output_ports);
      assert(coefficients_in.data());
      assert(coefficients_out.data());

      const DataType* ATK_RESTRICT coefficients_in_ptr = coefficients_in.data();
      const DataType* ATK_RESTRICT coefficients_out_ptr = coefficients_out.data();

      for(int channel = 0; channel < nb_input_ports; ++channel)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[channel] - in_order;
        DataType* ATK_RESTRICT output = outputs[channel];

        for(int64_t i = 0; i < size; ++i)
        {
          output[i] = 0;
        }

        for (int j = 0; j < in_order + 1; ++j)
        {
          for (int64_t i = 0; i < size; ++i)
          {
            output[i] += coefficients_in_ptr[j] * input[i + j];
          }
        }

        for (int64_t i = 0; i < size; ++i)
        {
          DataType tempout = output[i];
          for(int j = 0; j < out_order; ++j)
          {
            tempout += coefficients_out_ptr[j] * output[i - out_order + j];
          }
          output[i] = tempout;
        }
      }
    }
    
    /// Returns the vector of internal coefficients for the MA section 
    const AlignedVector& get_coefficients_in() const
    {
      return coefficients_in;
    }
    
    /// Returns the vector of internal coefficients for the AR section, without degree 0 implicitely set to -1
    const AlignedVector& get_coefficients_out() const
    {
      return coefficients_out;
    }
  };

}

#endif
