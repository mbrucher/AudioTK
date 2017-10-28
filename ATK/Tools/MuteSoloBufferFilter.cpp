/**
 * \file MuteSoloBufferFilter.cpp
 */

#include <ATK/Tools/MuteSoloBufferFilter.h>

#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  MuteSoloBufferFilter<DataType_>::MuteSoloBufferFilter(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels), mute_statuses(nb_channels), solo_statuses(nb_channels), any_solo(false)
  {
  }
  
  template<typename DataType_>
  MuteSoloBufferFilter<DataType_>::~MuteSoloBufferFilter()
  {
  }
  
  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::process_impl(std::size_t size) const
  {
    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      if(mute_statuses[channel] || (any_solo && !solo_statuses[channel]))
      {
        for(std::size_t i = 0; i < size; ++i)
        {
          output[i] = 0;
        }
      }
      else
      {
        for(std::size_t i = 0; i < size; ++i)
        {
          output[i] = input[i];
        }
      }
    }
  }

  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_mute(std::size_t channel, bool mute)
  {
    mute_statuses[channel] = mute;
  }
  
  template<typename DataType_>
  bool MuteSoloBufferFilter<DataType_>::get_mute(std::size_t channel) const
  {
    return mute_statuses[channel];
  }
  
  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_solo(std::size_t channel, bool solo)
  {
    solo_statuses[channel] = solo;
    any_solo = solo_statuses.any();
  }
  
  template<typename DataType_>
  bool MuteSoloBufferFilter<DataType_>::get_solo(std::size_t channel) const
  {
    return solo_statuses[channel];
  }

  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_nb_input_ports(std::size_t nb_ports)
  {
    throw std::runtime_error("Can't change number of ports in this filter");
  }
  
  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_nb_output_ports(std::size_t nb_ports)
  {
    throw std::runtime_error("Can't change number of ports in this filter");
  }

  template class MuteSoloBufferFilter<std::int16_t>;
  template class MuteSoloBufferFilter<std::int32_t>;
  template class MuteSoloBufferFilter<std::int64_t>;
  template class MuteSoloBufferFilter<float>;
  template class MuteSoloBufferFilter<double>;
  template class MuteSoloBufferFilter<std::complex<float>>;
  template class MuteSoloBufferFilter<std::complex<double>>;
}
