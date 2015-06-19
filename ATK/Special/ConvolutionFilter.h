/**
 * \file ConvolutionFilter.h
 */

#ifndef ATK_SPECIAL_CONVOLUTIONFILTER_H
#define ATK_SPECIAL_CONVOLUTIONFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class ConvolutionFilter: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::input_delay;
  protected:
    int in_order;

    std::vector<DataType> impulse;

  public:
    ConvolutionFilter(int nb_channels = 1);

    /**
     * Set the impulse for the convolution
     */
    void set_impulse(std::vector<DataType> impulse);
    
    void process_impl(std::int64_t size) const override final;
    
  };
}

#endif
