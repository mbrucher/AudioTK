/**
 * \file WhiteNoiseGeneratorFilter.cpp
 */

#include "WhiteNoiseGeneratorFilter.h"

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType_>
  WhiteNoiseGeneratorFilter<DataType_>::WhiteNoiseGeneratorFilter()
  :Parent(0, 1)
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
  void WhiteNoiseGeneratorFilter<DataType_>::process_impl(gsl::index size) const
  {
    DataType* ATK_RESTRICT output = outputs[0];
    for(gsl::index i = 0; i < size; ++i)
    {
      output[i] = dist(gen);
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class WhiteNoiseGeneratorFilter<float>;
#endif
  template class WhiteNoiseGeneratorFilter<double>;
}
