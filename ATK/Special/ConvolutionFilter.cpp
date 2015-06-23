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
    partial_frequency_input.assign(nb_splits - 1, std::vector<std::complex<DataType> >(split_size * 2, 0));
    // Pad with zeros so the convolution is easier created.
    impulse.resize((partial_frequency_input.size() + 1) * split_size, 0);

    temp_out_buffer.assign(split_size * 2, 0);
    processor.set_size(split_size * 2);
    
    // The size is twice as big than the impulse, less
    partial_frequency_impulse.assign(split_size * 2 * (nb_splits - 1), 0);
    for(int i = 1; i < nb_splits; ++i)
    {
      processor.process_forward(impulse.data() + i * split_size, partial_frequency_impulse.data() + (i - 1) * split_size * 2, split_size);
    }

    input_delay = split_size - 1;
    
    Parent::setup();
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::compute_convolutions() const
  {
    for(int i = 0; i < split_size; ++i)
    {
      temp_out_buffer[i] = temp_out_buffer[i + split_size];
      temp_out_buffer[i + split_size] = 0;
    }
    
    result.assign(2 * split_size, 0);
    DataType* ATK_RESTRICT result_ptr_orig = reinterpret_cast<DataType*>(result.data());
    const DataType* ATK_RESTRICT partial_frequency_impulse_ptr_orig = reinterpret_cast<const DataType*>(partial_frequency_impulse.data());

    // offset in the impulse frequencies
    int64_t offset = 0;
    for(const auto& buffer: partial_frequency_input)
    {
      DataType* ATK_RESTRICT result_ptr = result_ptr_orig;
      const DataType* ATK_RESTRICT buffer_ptr = reinterpret_cast<const DataType*>(buffer.data());
      const DataType* ATK_RESTRICT partial_frequency_impulse_ptr = partial_frequency_impulse_ptr_orig + offset;
      // Add the frequency result of this partial FFT
      for(int64_t i = 0; i < split_size; ++i)
      {
        DataType br1 = *(buffer_ptr++);
        DataType bi1 = *(buffer_ptr++);
        DataType pr1 = *(partial_frequency_impulse_ptr++);
        DataType pi1 = *(partial_frequency_impulse_ptr++);
        DataType br2 = *(buffer_ptr++);
        DataType bi2 = *(buffer_ptr++);
        DataType pr2 = *(partial_frequency_impulse_ptr++);
        DataType pi2 = *(partial_frequency_impulse_ptr++);
        *(result_ptr++) += br1*pr1-bi1*pi1;
        *(result_ptr++) += br1*pi1+pr1*bi1;
        *(result_ptr++) += br2*pr2-bi2*pi2;
        *(result_ptr++) += br2*pi2+pr2*bi2;
      }
      offset += 4 * split_size;
    }

    std::vector<DataType> ifft_result(2*split_size, 0);
    processor.process_backward(result.data(), ifft_result.data(), 2*split_size);
    for(int i = 0; i < 2*split_size; ++i)
    {
      temp_out_buffer[i] += ifft_result[i] * split_size * 2;
    }
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::process_new_chunk(int64_t position) const
  {
    if(partial_frequency_input.empty())
      return;
    partial_frequency_input.pop_back();
    std::vector<std::complex<double> > chunk(2 * split_size);
    processor.process_forward(converted_inputs[0] + position - split_size, chunk.data(), split_size);
    
    partial_frequency_input.push_front(std::move(chunk));
    compute_convolutions();
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::process_impulse_beginning(int64_t processed_size, int64_t size_to_process) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0] + processed_size;
    const DataType* ATK_RESTRICT impulse_ptr = impulse.data();
    DataType* ATK_RESTRICT output = outputs[0] + processed_size;

    for(int64_t i = 0; i < size_to_process; ++i)
    {
      output[i] = temp_out_buffer[split_position + i];
    }

    for(int j = 0; j < input_delay + 1; ++j)
    {
      for(int64_t i = 0; i < size_to_process; ++i)
      {
        output[i] += impulse_ptr[j] * input[i - j];
      }
    }
  }

  template<typename DataType_>
  void ConvolutionFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);
    assert(nb_input_ports == nb_output_ports);
    
    int processed_size = 0;
    do
    {
      // We can only process split_size elements at a time, but if we already have some elements in the buffer,
      // we need to take them into account.
      int64_t size_to_process = std::min(split_size - split_position, size - processed_size);

      process_impulse_beginning(processed_size, size_to_process);

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
