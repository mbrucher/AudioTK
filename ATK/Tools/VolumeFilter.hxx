/**
 * \file VolumeFilter.hxx
 */

#include "VolumeFilter.h"
#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<typename DataType_>
  VolumeFilter<DataType_>::VolumeFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  void VolumeFilter<DataType_>::set_volume_db(double volume_db)
  {
    set_volume(TypeTraits<DataType_>::One() * static_cast<typename TypeTraits<DataType_>::Scalar>(std::pow(10., volume_db/20)));
  }
  
  template<typename DataType_>
  void VolumeFilter<DataType_>::set_volume(DataType_ volume)
  {
    this->volume = volume;
  }
  
  template<typename DataType_>
  DataType_ VolumeFilter<DataType_>::get_volume() const
  {
    return volume;
  }

  template<typename DataType_>
  void VolumeFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = volume * input[i];
      }
    }
  }
}
