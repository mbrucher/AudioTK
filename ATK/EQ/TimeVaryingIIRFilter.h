/**
 * \file TimeVaryingIIRFilter.h
 */

#ifndef ATK_EQ_TIMEVARYINGIIRFILTER_H
#define ATK_EQ_TIMEVARYINGIIRFILTER_H

#include <cmath>
#include <vector>

#include "config.h"

namespace ATK
{
  /**
   * IIR filter template class
   */
  template<class Coefficients >
  class ATK_EQ_EXPORT TimeVaryingIIRFilter: public Coefficients
  {
  public:
    typedef Coefficients Parent;
    using typename Parent::DataType;
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

    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;

  public:
    TimeVaryingIIRFilter()
      :Parent()
    {
    }

    void setup()
    {
      Parent::setup();
      input_delay = in_order;
      output_delay = out_order;
    }
    
    virtual void process_impl(std::int64_t size)
    {
      assert(input_sampling_rate == output_sampling_rate);
      
      DataType scale = (number_of_steps - 1) / (max_frequency - min_frequency);
      DataType tempout = 0;
      
      const DataType* ATK_RESTRICT input = converted_inputs[0];
      const DataType* ATK_RESTRICT cut_frequencies = converted_inputs[1];
      DataType* ATK_RESTRICT output = outputs[0];
      for(std::int64_t i = 0; i < size; ++i)
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

        tempout = coefficients_in[frequency_index * (in_order+1) + in_order] * input[i];

        for(int j = 0; j < in_order; ++j)
        {
          tempout += coefficients_in[frequency_index * (in_order+1) + j] * input[i - in_order + j];
        }
        for(int j = 0; j < out_order; ++j)
        {
          tempout += coefficients_out[frequency_index * (out_order) + j] * output[i - out_order + j];
        }
        output[i] = tempout;
      }
    }
  };

}

#endif
