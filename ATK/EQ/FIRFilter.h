/**
 * \file FIRFilter.h
 */

#ifndef ATK_EQ_FIRFILTER_H
#define ATK_EQ_FIRFILTER_H

#include <cassert>
#include <vector>

#include "config.h"

namespace ATK
{
  /**
   * FIR filter template class
   */
  template<class Coefficients >
  class ATK_EQ_EXPORT FIRFilter: public Coefficients
  {
  public:
    typedef Coefficients Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::coefficients_in;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    
    using Parent::in_order;
    using Parent::input_delay;
    using Parent::setup;
    
  public:
    void setup()
    {
      Parent::setup();
      input_delay = in_order;
    }
    
    virtual void process_impl(std::int64_t size)
    {
      assert(input_sampling_rate == output_sampling_rate);
      
      DataType tempout = 0;
      
      for(long i = 0; i < size; ++i)
      {
        tempout = coefficients_in[in_order] * converted_inputs[0][i];
        
        for(int j = 0; j < in_order; ++j)
        {
          tempout += coefficients_in[j] * converted_inputs[0][i - in_order + j];
        }
        outputs[0][i] = tempout;
      }
    }
    
    const std::vector<DataType>& get_coefficients_in() const
    {
      return coefficients_in;
    }
  };
  
}

#endif
