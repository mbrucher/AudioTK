/**
 * \file VolumeFilter.cpp
 */

#include "VolumeFilter.h"

#include <cmath>
#include <complex>
#include <cstdint>

#include <ATK/Core/TypeTraits.h>

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
  double VolumeFilter<DataType_>::get_volume() const
  {
    return volume;
  }

  template<typename DataType_>
  void VolumeFilter<DataType_>::process_impl(std::size_t size) const
  {
    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        output[i] = static_cast<DataType>(static_cast<typename TypeTraits<DataType>::Scalar>(volume) * static_cast<typename TypeTraits<DataType>::Scalar>(input[i]));
      }
    }
  }
  
  template class VolumeFilter<std::int16_t>;
  template class VolumeFilter<std::int32_t>;
  template class VolumeFilter<std::int64_t>;
  template class VolumeFilter<float>;
  template class VolumeFilter<double>;
  template class VolumeFilter<std::complex<float>>;
  template class VolumeFilter<std::complex<double>>;
}
