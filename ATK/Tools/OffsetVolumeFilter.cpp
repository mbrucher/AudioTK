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
  :Parent(nb_channels, nb_channels), volume(1), offset(0)
  {
    
  }
  
  template<typename DataType_>
  OffsetVolumeFilter<DataType_>::~OffsetVolumeFilter()
  {
    
  }
  
  template<typename DataType_>
  void OffsetVolumeFilter<DataType_>::set_volume(DataType_ volume)
  {
    this->volume = volume;
  }

  template<typename DataType_>
  DataType_ OffsetVolumeFilter<DataType_>::get_volume() const
  {
    return volume;
  }
    
  template<typename DataType_>
  void OffsetVolumeFilter<DataType_>::set_offset(DataType_ offset)
  {
    this->offset = offset;
  }

  template<typename DataType_>
  DataType_ OffsetVolumeFilter<DataType_>::get_offset() const
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
  
  template class OffsetVolumeFilter<float>;
  template class OffsetVolumeFilter<double>;
}
