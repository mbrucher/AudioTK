/**
 * \file WhiteNoiseGeneratorFilter.cpp
 */

#include "WhiteNoiseGeneratorFilter.h"

#include <cmath>
#include <cstdint>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType_>
  WhiteNoiseGeneratorFilter<DataType_>::WhiteNoiseGeneratorFilter()
  :Parent(0, 1), volume(1), offset(0), dist(static_cast<DataType>(1e-3), static_cast<DataType>(2e-3))
  {
    
  }
  
  template<typename DataType_>
  WhiteNoiseGeneratorFilter<DataType_>::~WhiteNoiseGeneratorFilter()
  {
    
  }
  
  template<typename DataType_>
  void WhiteNoiseGeneratorFilter<DataType_>::set_volume(DataType_ volume)
  {
    this->volume = volume;
    dist.param(typename boost::random::uniform_real_distribution<DataType_>::param_type(static_cast<DataType>(offset - volume), static_cast<DataType>(offset + volume)));
  }
  
  template<typename DataType_>
  DataType_ WhiteNoiseGeneratorFilter<DataType_>::get_volume() const
  {
    return volume;
  }
  
  template<typename DataType_>
  void WhiteNoiseGeneratorFilter<DataType_>::set_offset(DataType_ offset)
  {
    this->offset = offset;
    dist.param(typename boost::random::uniform_real_distribution<DataType_>::param_type(static_cast<DataType>(offset - volume), static_cast<DataType>(offset + volume)));
  }
  
  template<typename DataType_>
  DataType_ WhiteNoiseGeneratorFilter<DataType_>::get_offset() const
  {
    return offset;
  }

  template<typename DataType_>
  void WhiteNoiseGeneratorFilter<DataType_>::process_impl(std::size_t size) const
  {
    DataType* ATK_RESTRICT output = outputs[0];
    for(std::size_t i = 0; i < size; ++i)
    {
      output[i] = dist(gen);
    }
  }
  
  template class WhiteNoiseGeneratorFilter<float>;
  template class WhiteNoiseGeneratorFilter<double>;
}
