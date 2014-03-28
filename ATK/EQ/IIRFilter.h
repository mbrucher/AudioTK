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
  private:
    DataType buffer_in[in_order];
    DataType buffer_out[out_order];
    
  public:
    IIRFilter()
    {
      for(int i = 0; i < in_order; ++i)
      {
        buffer_in[i] = 0;
      }
      for(int i = 0; i < out_order; ++i)
      {
        buffer_out[i] = 0;
      }
    }
    
    virtual void process_impl(long size)
    {
      assert(input_sampling_rate == output_sampling_rate);
      
      for(long i = 0; i < size; ++i)
      {
        outputs[0][i] = coefficients_in[in_order] * converted_inputs[0][i];

        for(int j = 0; j < in_order; ++j)
        {
          outputs[0][i] += coefficients_in[j] * buffer_in[j];
        }
        for(int j = 0; j < out_order; ++j)
        {
          outputs[0][i] += coefficients_out[j] * buffer_out[j];
        }
        //std::cout << outputs[0][i] << std::endl;
        for(int j = 1; j < in_order; ++j)
        {
          buffer_in[j-1] = buffer_in[j];
        }
        buffer_in[in_order-1] = converted_inputs[0][i];
        for(int j = 1; j < out_order; ++j)
        {
          buffer_out[j-1] = buffer_out[j];
        }
        buffer_out[out_order-1] = outputs[0][i];
      }
    }

  };

}

#endif
