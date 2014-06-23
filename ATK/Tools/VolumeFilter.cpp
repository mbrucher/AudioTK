/**
 * \file VolumeFilter.cpp
 */

#include "VolumeFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  VolumeFilter<DataType_>::VolumeFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), volume(1)
  {
    
  }
  
  template<typename DataType_>
  VolumeFilter<DataType_>::~VolumeFilter()
  {
    
  }
  
  template<typename DataType_>
  void VolumeFilter<DataType_>::set_volume_db(double volume_db)
  {
    set_volume(std::pow(10., volume_db/20));
  }
  
  template<typename DataType_>
  void VolumeFilter<DataType_>::set_volume(double volume)
  {
    this->volume = volume;
  }
  
  template<typename DataType_>
  void VolumeFilter<DataType_>::process_impl(std::int64_t size)
  {
    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      for(std::int64_t i = 0; i < size; ++i)
      {
        outputs[channel][i] = static_cast<DataType>(volume * converted_inputs[channel][i]);
      }
    }
  }
  
  template class VolumeFilter<std::int16_t>;
  template class VolumeFilter<std::int32_t>;
  template class VolumeFilter<std::int64_t>;
  template class VolumeFilter<float>;
  template class VolumeFilter<double>;
}
