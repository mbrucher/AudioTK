/**
 * \file VolumeFilter.cpp
 */

#include "VolumeFilter.h"

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  VolumeFilter<DataType_>::VolumeFilter()
  :Parent(1, 1), volume(1)
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
  void VolumeFilter<DataType_>::process_impl(long size)
  {
    for(long i = 0; i < size; ++i)
    {
      outputs[0][i] = static_cast<DataType>(volume * converted_inputs[0][i]);
    }
  }
  
  template class VolumeFilter<std::int16_t>;
  template class VolumeFilter<std::int32_t>;
  template class VolumeFilter<std::int64_t>;
  template class VolumeFilter<float>;
  template class VolumeFilter<double>;
}
