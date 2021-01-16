/**
 * \file MuteSoloBufferFilter.cpp
 */

#include "MuteSoloBufferFilter.h"
#include <ATK/Core/Utilities.h>

#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  MuteSoloBufferFilter<DataType_>::MuteSoloBufferFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels), mute_statuses(nb_channels), solo_statuses(nb_channels)
  {
  }
  
  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      if(mute_statuses[channel] || (any_solo && !solo_statuses[channel]))
      {
        for(gsl::index i = 0; i < size; ++i)
        {
          output[i] = 0;
        }
      }
      else
      {
        for(gsl::index i = 0; i < size; ++i)
        {
          output[i] = input[i];
        }
      }
    }
  }

  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_mute(gsl::index channel, bool mute)
  {
    mute_statuses[channel] = mute;
  }
  
  template<typename DataType_>
  bool MuteSoloBufferFilter<DataType_>::get_mute(gsl::index channel) const
  {
    return mute_statuses[channel];
  }
  
  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_solo(gsl::index channel, bool solo)
  {
    solo_statuses[channel] = solo;
    any_solo = solo_statuses.any();
  }
  
  template<typename DataType_>
  bool MuteSoloBufferFilter<DataType_>::get_solo(gsl::index channel) const
  {
    return solo_statuses[channel];
  }

  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_nb_input_ports(gsl::index nb_ports)
  {
    throw ATK::RuntimeError("Can't change number of ports in this filter");
  }
  
  template<typename DataType_>
  void MuteSoloBufferFilter<DataType_>::set_nb_output_ports(gsl::index nb_ports)
  {
    throw ATK::RuntimeError("Can't change number of ports in this filter");
  }

#if ATK_ENABLE_INSTANTIATION
  template class MuteSoloBufferFilter<std::int16_t>;
  template class MuteSoloBufferFilter<std::int32_t>;
  template class MuteSoloBufferFilter<std::int64_t>;
  template class MuteSoloBufferFilter<float>;
  template class MuteSoloBufferFilter<std::complex<float>>;
  template class MuteSoloBufferFilter<std::complex<double>>;
#endif
  template class MuteSoloBufferFilter<double>;
}
