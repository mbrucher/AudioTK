/**
 * \file OffsetVolumeFilter.cpp
 */

#include "OffsetVolumeFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  OffsetVolumeFilter<DataType_>::OffsetVolumeFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), offset(0), volume(1)
  {
    
  }
  
  template<typename DataType_>
  OffsetVolumeFilter<DataType_>::~OffsetVolumeFilter()
  {
    
  }
  
  template<typename DataType_>
  void OffsetVolumeFilter<DataType_>::set_volume(double volume)
  {
    this->volume = volume;
  }

  template<typename DataType_>
  double OffsetVolumeFilter<DataType_>::get_volume() const
  {
    return volume;
  }
    
  template<typename DataType_>
  void OffsetVolumeFilter<DataType_>::set_offset(double offset)
  {
    this->offset = offset;
  }

  template<typename DataType_>
  double OffsetVolumeFilter<DataType_>::get_offset() const
  {
    return offset;
  }

  template<typename DataType_>
  void OffsetVolumeFilter<DataType_>::process_impl(int64_t size) const
  {
    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        *(output++) = static_cast<DataType>(offset + volume * *(input++));
      }
    }
  }
  
  template class OffsetVolumeFilter<std::int16_t>;
  template class OffsetVolumeFilter<std::int32_t>;
  template class OffsetVolumeFilter<int64_t>;
  template class OffsetVolumeFilter<float>;
  template class OffsetVolumeFilter<double>;
}
