/**
 * \file OffsetVolumeFilter.hxx
 */

#include "OffsetVolumeFilter.h"

namespace ATK
{
  template<typename DataType_>
  OffsetVolumeFilter<DataType_>::OffsetVolumeFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
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
  void OffsetVolumeFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = offset + volume * input[i];
      }
    }
  }
}
