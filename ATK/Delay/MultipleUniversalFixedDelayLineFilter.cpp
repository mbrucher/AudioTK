/**
 * \file MultipleUniversalFixedDelayLineFilter.cpp
 */

#include "MultipleUniversalFixedDelayLineFilter.h"

#include <cmath>
#include <cstring>
#include <complex>
#include <iostream>
#include <numeric>
#include <stdexcept>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<class DataType, unsigned int nb_channels>
  class MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::SUFDLF_Impl
  {
  public:
    std::array<std::vector<DataType>, nb_channels> delay_line;
    std::size_t index;

    SUFDLF_Impl(std::size_t max_delay)
    {
      for(unsigned int channel = 0; channel < nb_channels; ++channel)
      {
        delay_line[channel].assign(max_delay, 0);
      }
    }
  };

  template<class DataType, unsigned int nb_channels>
  MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::MultipleUniversalFixedDelayLineFilter(std::size_t max_delay)
    :Parent(nb_channels, 2*nb_channels), impl(new SUFDLF_Impl(max_delay)), max_delay(max_delay)
  {
    delay.fill(max_delay-1);
    blend.fill(0);
    feedback.fill(0);
    feedforward.fill(0);
  }
  
  template<class DataType, unsigned int nb_channels>
  MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::~MultipleUniversalFixedDelayLineFilter()
  {
  }
  
  template<class DataType, unsigned int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::set_delay(unsigned int channel, std::size_t delay)
  {
    if(delay == 0)
    {
      throw std::out_of_range("Delay must be strictly positive");
    }
    if(delay >= max_delay)
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    this->delay[channel] = delay;
  }

  template<class DataType, unsigned int nb_channels>
  std::size_t MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::get_delay(unsigned int channel) const
  {
    return delay[channel];
  }

  template<class DataType_, unsigned int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::set_blend(unsigned int channel, DataType_ blend)
  {
    this->blend[channel] = blend;
  }

  template<class DataType_, unsigned int nb_channels>
  DataType_ MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::get_blend(unsigned int channel) const
  {
    return blend[channel];
  }

  template<class DataType_, unsigned int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::set_feedback(unsigned int from_channel, unsigned int to_channel, DataType_ feedback)
  {
    if(std::abs(feedback) > 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    this->feedback[from_channel * nb_channels + to_channel] = feedback;
  }

  template<class DataType_, unsigned int nb_channels>
  DataType_ MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::get_feedback(unsigned int from_channel, unsigned int to_channel) const
  {
    return feedback[from_channel * nb_channels + to_channel];
  }

  template<class DataType_, unsigned int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::set_feedforward(unsigned int from_channel, unsigned int to_channel, DataType_ feedforward)
  {
    this->feedforward[from_channel * nb_channels + to_channel]  = feedforward;
  }

  template<class DataType_, unsigned int nb_channels>
  DataType_ MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::get_feedforward(unsigned int from_channel, unsigned int to_channel) const
  {
    return feedforward[from_channel * nb_channels + to_channel] ;
  }

  template<class DataType, unsigned int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::full_setup()
  {
    // reset the delay line
    for(unsigned int channel = 0; channel < nb_channels; ++channel)
    {
      impl->delay_line[channel].assign(max_delay, 0);
    }
  }

  template<class DataType, unsigned int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::process_impl(std::size_t size) const
  {
    // Start of the actual impl, will try to remove the lines above
    
    std::size_t max_processing_size = std::accumulate(delay.begin(), delay.end(), size, [](std::size_t a, std::size_t b)
                {
                  return std::min(a - 1, b - 1) + 1;// stupid way of turning 0 in max(), so that they are not counted in the minimum
                });

    ATK_VECTORIZE for(std::size_t i = 0; i < size; i += max_processing_size)
    {
      auto processing_size = std::min(max_processing_size, size - i);
      process_impl(processing_size, i);
    }
  }

  
  template<class DataType, unsigned int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::process_impl(std::size_t size, std::size_t offset) const
  {
    auto delay_line_size = impl->delay_line[0].size();

    std::cout << "size\t" << size << std::endl;
    std::cout << "offset\t" << offset << std::endl;

    std::array<std::size_t, nb_channels> size_before_index;
    std::array<std::size_t, nb_channels> size_after_index;
    for(unsigned int channel = 0; channel < nb_channels; ++channel)
    {
      size_before_index[channel] = std::min(impl->index, impl->index < delay[channel] ? (size > delay[channel] - impl->index ? size - (delay[channel] - impl->index) : 0) : std::min(size, delay[channel]));
      size_after_index[channel] = impl->index < delay[channel] ? std::min(size, delay[channel] - impl->index) : 0;
      std::cout << size_before_index[channel] << "\t" << size_after_index[channel] << std::endl;
    }

    // Update intermediate input
    for(unsigned int channel = 0; channel < nb_channels; ++channel)
    {
      ATK_VECTORIZE for (std::size_t i = 0; i < size_after_index[channel]; ++i)
      {
        outputs[nb_channels + channel][offset+i] = converted_inputs[channel][offset+i];
        
        for(unsigned int to_channel = 0; to_channel < nb_channels; ++to_channel)
        {
          outputs[nb_channels + to_channel][offset+i] += feedback[to_channel * nb_channels + channel] * impl->delay_line[to_channel][delay_line_size + i - (delay[channel] - impl->index)];
        }
      }
      ATK_VECTORIZE for (std::size_t i = 0; i < size_before_index[channel]; ++i)
      {
        outputs[nb_channels + channel][offset+i + size_after_index[channel]] = converted_inputs[channel][offset+i + size_after_index[channel]];
        
        for(unsigned int to_channel = 0; to_channel < nb_channels; ++to_channel)
        {
           outputs[nb_channels + to_channel][offset+i + size_after_index[channel]] += feedback[to_channel * nb_channels + channel] * impl->delay_line[to_channel][i + size_after_index[channel] + impl->index - delay[channel]];
        }
      }
      ATK_VECTORIZE for(std::size_t i = delay[channel]; i < size; ++i)
      {
        outputs[nb_channels + channel][offset+i+delay[channel]] = converted_inputs[channel][offset+i];
        
        for(unsigned int to_channel = 0; to_channel < nb_channels; ++to_channel)
        {
          outputs[nb_channels + to_channel][offset+i + delay[channel]] += feedback[to_channel * nb_channels + channel] * outputs[nb_channels + to_channel][i - delay[channel]];
        }
      }
    }
    
    //update output
    for(unsigned int channel = 0; channel < nb_channels; ++channel)
    {
      ATK_VECTORIZE for (std::size_t i = 0; i < size_after_index[channel]; ++i)
      {
        outputs[channel][offset+i] = blend[channel] * outputs[nb_channels + channel][offset+i];
        
        for(unsigned int to_channel = 0; to_channel < nb_channels; ++to_channel)
        {
          outputs[nb_channels + to_channel][offset+i] += feedforward[to_channel * nb_channels + channel] * impl->delay_line[to_channel][delay_line_size + i - (delay[channel] - impl->index)];
        }
      }
      ATK_VECTORIZE for (std::size_t i = 0; i < size_before_index[channel]; ++i)
      {
        outputs[channel][offset+i + size_after_index[channel]] = blend[channel] * outputs[nb_channels + channel][offset+i + size_after_index[channel]];
        
        for(unsigned int to_channel = 0; to_channel < nb_channels; ++to_channel)
        {
          outputs[to_channel][offset+i + size_after_index[channel]] += feedforward[to_channel * nb_channels + channel] * impl->delay_line[to_channel][i + size_after_index[channel] + impl->index - delay[channel]];
        }
      }
      ATK_VECTORIZE for(std::size_t i = delay[channel]; i < size; ++i)
      {
        outputs[channel][offset+i+delay[channel]] = blend[channel] * outputs[nb_channels + channel][offset+i];
        
        for(unsigned int to_channel = 0; to_channel < nb_channels; ++to_channel)
        {
          outputs[to_channel][offset+i + delay[channel]] += feedforward[to_channel * nb_channels + channel] * outputs[nb_channels + to_channel][i - delay[channel]];
        }
      }
    }
    
    if (size > delay_line_size)
    {
      impl->index = 0;
      for(unsigned int channel = 0; channel < nb_channels; ++channel)
      {
        memcpy(reinterpret_cast<void*>(impl->delay_line[channel].data()), reinterpret_cast<const void*>(outputs[nb_channels + channel] + size - delay_line_size), delay_line_size * sizeof(DataType));
      }
    }
    else
    {
      auto new_index = std::min(impl->index + size, delay_line_size);
      auto first_size = new_index - impl->index;
      for(unsigned int channel = 0; channel < nb_channels; ++channel)
      {
        memcpy(reinterpret_cast<void*>(impl->delay_line[channel].data() + impl->index), reinterpret_cast<const void*>(outputs[nb_channels + channel]), first_size * sizeof(DataType));
      }
      auto second_size = size - first_size;
      
      if (impl->index + size > delay_line_size)
      {
        impl->index = second_size;
        for(unsigned int channel = 0; channel < nb_channels; ++channel)
        {
          memcpy(reinterpret_cast<void*>(impl->delay_line[channel].data()), reinterpret_cast<const void*>(outputs[nb_channels + channel] + first_size), second_size * sizeof(DataType));
        }
      }
      else
      {
        impl->index = new_index;
      }
    }
  }

  template class MultipleUniversalFixedDelayLineFilter<float, 2>;
  template class MultipleUniversalFixedDelayLineFilter<double, 2>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<float>, 2>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<double>, 2>;

  template class MultipleUniversalFixedDelayLineFilter<float, 4>;
  template class MultipleUniversalFixedDelayLineFilter<double, 4>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<float>, 4>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<double>, 4>;

  template class MultipleUniversalFixedDelayLineFilter<float, 8>;
  template class MultipleUniversalFixedDelayLineFilter<double, 8>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<float>, 8>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<double>, 8>;
}
