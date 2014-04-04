/**
 * \file IIRFilter.h
 */

#ifndef ATK_EQ_IIRFILTER_H
#define ATK_EQ_IIRFILTER_H

namespace ATK
{
  
  /**
   * IIR filter template class
   */
  template<class Coefficients >
  class IIRFilter: public Coefficients
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
    
    using Parent::in_order;
    using Parent::out_order;
    using Parent::input_delay;
    using Parent::output_delay;
    using Parent::setup;
    
  public:
    void setup()
    {
      Parent::setup();
      input_delay = in_order;
      output_delay = out_order;
    }
    
    virtual void process_impl(long size)
    {
      assert(input_sampling_rate == output_sampling_rate);
      
      for(long i = 0; i < size; ++i)
      {
        outputs[0][i] = coefficients_in[in_order] * converted_inputs[0][i];

        for(int j = 0; j < in_order; ++j)
        {
          outputs[0][i] += coefficients_in[j] * converted_inputs[0][i - in_order + j];
        }
        for(int j = 0; j < out_order; ++j)
        {
          outputs[0][i] += coefficients_out[j] * outputs[0][i - out_order + j];
        }
      }
    }
    
    const std::vector<DataType>& get_coefficients_in() const
    {
      return coefficients_in;
    }
    
    const std::vector<DataType>& get_coefficients_out() const
    {
      return coefficients_out;
    }
  };

}

#endif
