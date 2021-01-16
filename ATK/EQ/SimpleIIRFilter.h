/**
 * \file SimpleIIRFilter.h
 */

#ifndef ATK_EQ_SIMPLEIIRFILTER_H
#define ATK_EQ_SIMPLEIIRFILTER_H

#include <ATK/config.h>
#include <ATK/EQ/config.h>

#include <algorithm>
#include <cassert>
#include <vector>

namespace ATK
{
  /// IIR filter template class (Direct Form I)
  template<class Coefficients>
  class SimpleIIRFilter final : public Coefficients
  {
  public:
    /// Simplify parent calls
    using Parent = Coefficients;
    using typename Parent::DataType;
    using typename Parent::AlignedScalarVector;
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
    explicit SimpleIIRFilter(gsl::index nb_channels = 1)
      :Parent(nb_channels)
    {
    }

    /// Move constructor
    SimpleIIRFilter(SimpleIIRFilter&& other)
    :Parent(std::move(other))
    {
    }

    void setup() final
    {
      Parent::setup();
      input_delay = in_order;
      output_delay = out_order;
    }
    
    void process_impl(gsl::index size) const final
    {
      assert(input_sampling_rate == output_sampling_rate);
      assert(nb_input_ports == nb_output_ports);
      assert(coefficients_in.data());
      assert(out_order == 0 || coefficients_out.data() != nullptr);

      const auto* ATK_RESTRICT coefficients_in_ptr = coefficients_in.data();
      const auto* ATK_RESTRICT coefficients_out_ptr = coefficients_out.data();

      for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[channel] - static_cast<int64_t>(in_order);
        DataType* ATK_RESTRICT output = outputs[channel];

        for(gsl::index i = 0; i < size; ++i)
        {
          output[i] = TypeTraits<DataType>::Zero();
        }

        for (gsl::index j = 0; j < in_order + 1; ++j)
        {
          for (gsl::index i = 0; i < size; ++i)
          {
            output[i] = output[i] + coefficients_in_ptr[j] * input[i + j];
          }
        }

        for (gsl::index i = 0; i < size; ++i)
        {
          for (gsl::index j = 0; j < out_order; ++j)
          {
            output[i] = output[i] + coefficients_out_ptr[j] * output[static_cast<int64_t>(i) - out_order + j];
          }
        }
      }
    }
    
    /// Returns the vector of internal coefficients for the MA section 
    const AlignedScalarVector& get_coefficients_in() const
    {
      return coefficients_in;
    }
    
    /// Returns the vector of internal coefficients for the AR section, without degree 0 implicitely set to -1
    const AlignedScalarVector& get_coefficients_out() const
    {
      return coefficients_out;
    }
  };
}

#endif
