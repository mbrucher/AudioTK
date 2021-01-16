/**
 * \file TimeVaryingIIRFilter.h
 */

#ifndef ATK_EQ_TIMEVARYINGIIRFILTER_H
#define ATK_EQ_TIMEVARYINGIIRFILTER_H

#include <ATK/config.h>
#include <ATK/EQ/config.h>

#include <cassert>
#include <cmath>
#include <vector>

namespace ATK
{
  /// IIR filter template class for time varying frequencies. Transposed Direct Form II
  template<class Coefficients >
  class ATK_EQ_EXPORT TimeVaryingIIRFilter final : public Coefficients
  {
  public:
    /// Simplify parent calls
    using Parent = Coefficients;
    using typename Parent::DataType;
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

    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::memory;
    using Parent::number_of_steps;
  protected:
    mutable std::vector<DataType> current_coeffs_in;
    mutable std::vector<DataType> current_coeffs_out;
    mutable std::vector<DataType> state;
  public:
    TimeVaryingIIRFilter()
      :Parent()
    {
    }

    void setup() final
    {
      Parent::setup();
      input_delay = in_order;
      output_delay = out_order;
      state.resize(std::max(input_delay, output_delay), 0);
    }
    
    void process_impl(gsl::index size) const final
    {
      assert(input_sampling_rate == output_sampling_rate);
      
      current_coeffs_in.resize(in_order+1, 0);
      current_coeffs_out.resize(out_order, 0);

      DataType scale = static_cast<DataType>((number_of_steps - 1) / (max_frequency - min_frequency));

      const DataType* ATK_RESTRICT input = converted_inputs[0];
      const DataType* ATK_RESTRICT cut_frequencies = converted_inputs[1];
      DataType* ATK_RESTRICT output = outputs[0];
      for(gsl::index i = 0; i < size; ++i)
      {
        int frequency_index = static_cast<int>((cut_frequencies[i] - min_frequency) * scale);
        if(frequency_index < 0)
        {
          frequency_index = 0;
        }
        if(frequency_index >= number_of_steps)
        {
          frequency_index = number_of_steps - 1;
        }
        for(gsl::index j = 0; j < in_order+1; ++j)
        {
          current_coeffs_in[j] = static_cast<DataType>(current_coeffs_in[j] * memory + coefficients_in[frequency_index * (in_order+1) + j] * (1 - memory));
        }
        for(gsl::index j = 0; j < out_order; ++j)
        {
          current_coeffs_out[j] = static_cast<DataType>(current_coeffs_out[j] * memory + coefficients_out[frequency_index * (out_order) + j] * (1 - memory));
        }

        output[i] = current_coeffs_in[in_order] * input[i] + state[0];
        for(gsl::index j = 0; j < state.size() - 1; ++j)
        {
          state[j] = state[j + 1];
        }
        state[state.size() - 1] = 0;

        for(gsl::index j = 0; j < in_order; ++j)
        {
          state[j] += input[i] * current_coeffs_in[in_order - static_cast<int64_t>(j) - 1];
        }
        for(gsl::index j = 0; j < out_order; ++j)
        {
          state[j] += output[i] * current_coeffs_out[out_order - static_cast<int64_t>(j) - 1];
        }
      }
    }
  };

}

#endif
