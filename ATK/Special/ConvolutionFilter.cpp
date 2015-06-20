/**
 * \file ConvolutionFilter.cpp
 */

#include "ConvolutionFilter.h"

#include <cassert>

namespace ATK
{
  template <typename DataType>
  ConvolutionFilter<DataType>::ConvolutionFilter()
    :Parent(1, 1), split_position(0), split_size(0)
  {
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::set_impulse(std::vector<DataType> impulse)
  {
    this->impulse = std::move(impulse);
    setup();
    // Pad with zeros so the convolution is easier created.
    this->impulse.resize((partial_convolutions.size() + 1) * split_size, 0);
  }
  
  template<typename DataType_>
  void ConvolutionFilter<DataType_>::set_split_size(int split_size)
  {
    this->split_size = split_size;
    setup();
  }
  
  template<typename DataType_>
  void ConvolutionFilter<DataType_>::setup()
  {
    if(impulse.size() == 0 || split_size == 0)
    {
      return;
    }

    auto nb_splits = (impulse.size() + split_size - 1) / split_size;
    partial_convolutions.assign(nb_splits - 1, std::vector<DataType>(split_size * 2, 0));
    temp_out_buffer.assign(split_size * 2, 0);

    input_delay = split_size - 1;
    
    Parent::setup();
  }
  
  template<typename DataType_>
  void ConvolutionFilter<DataType_>::compute_convolution(DataType* ATK_RESTRICT output, const DataType* ATK_RESTRICT input1, const DataType* ATK_RESTRICT  input2, int size) const
  {
    // Adding this convolution to the previous one, easier.
    for(int i = 0; i < size; ++i)
    {
      for(int j = 0; j < size; ++j)
      {
        output[i + j] += input1[i] * input2[j];
      }
    }
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::compute_convolutions() const
  {
    for(int i = 0; i < split_size; ++i)
    {
      temp_out_buffer[i] = temp_out_buffer[i + split_size];
      temp_out_buffer[i + split_size] = 0;
    }
    int64_t offset = split_size; // Where I'll start my convolutions
    for(const auto& buffer: partial_convolutions)
    {
      compute_convolution(temp_out_buffer.data(), buffer.data(), impulse.data() + offset, split_size);
      offset += split_size;
    }
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::process_new_chunk(int64_t position) const
  {
    partial_convolutions.pop_back();
    std::vector<double> chunk(split_size);
    for(int64_t i = position - split_size, j = 0; i < position; ++i, ++j)
    {
      chunk[j] = converted_inputs[0][i];
    }
    partial_convolutions.push_front(std::move(chunk));
    compute_convolutions();
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);
    assert(nb_input_ports == nb_output_ports);
    
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    
    int processed_size = 0;
    do
    {
      // We can only process split_size elements at a time, but if we already have some elements in the buffer,
      // we need to take them into account.
      int64_t size_to_process = std::min(split_size - split_position, size - processed_size);

      for(int64_t i = 0; i < size_to_process; ++i)
      {
        DataType tempout = temp_out_buffer[split_position + i];
        for(int j = 0; j < input_delay + 1; ++j)
        {
          tempout += impulse[j] * input[processed_size + i - j];
        }
        output[processed_size + i] = tempout;
      }

      split_position += size_to_process;
      processed_size += size_to_process;
      if(split_position == split_size)
      {
        process_new_chunk(processed_size);
        split_position = 0;
      }
    }while(processed_size != size);
  }

  template class ConvolutionFilter<double>;
}
