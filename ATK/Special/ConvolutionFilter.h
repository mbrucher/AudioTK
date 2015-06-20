/**
 * \file ConvolutionFilter.h
 */

#ifndef ATK_SPECIAL_CONVOLUTIONFILTER_H
#define ATK_SPECIAL_CONVOLUTIONFILTER_H

#include <list>
#include <vector>

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
    mutable int64_t split_position;
    int64_t split_size;
    
    std::vector<DataType> impulse;
    /// This buffer contains the head of the last convolution (easier to have 2 parts)
    mutable std::vector<DataType> temp_out_buffer;
    /// Called partial convolutions, but actually contains the former temp_in_buffers
    mutable std::list<std::vector<DataType> > partial_convolutions;

    /// Simple convolution kernel, mandatory to have the same sizes for intput1 and input2
    void compute_convolution(DataType* ATK_RESTRICT output, const DataType* ATK_RESTRICT input1, const DataType* ATK_RESTRICT  input2, int size) const;
    /// Compute the partial convolutions
    void compute_convolutions() const;
    /// Create a new chunk and compute the convolution
    void process_new_chunk(int64_t position) const;
    
  public:
    ConvolutionFilter();

    /**
     * Set the impulse for the convolution
     */
    void set_impulse(std::vector<DataType> impulse);
    
    void set_split_size(int split_size);
    
    void process_impl(int64_t size) const override final;
    
    void setup() override final;
    
  };
}

#endif
