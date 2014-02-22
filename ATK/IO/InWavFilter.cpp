/**
 * \file InWavFilter.cpp
 */

#include "InWavFilter.h"

namespace ATK
{
  template<typename DataType>
  InWavFilter<DataType>::InWavFilter(const std::string& filename)
  :TypedBaseFilter<DataType>(0, 0)
  {
    
  }

  template<typename DataType>
  void InWavFilter<DataType>::process_impl(long size)
  {
    
  }
  
  template class InWavFilter<std::int16_t>;
  template class InWavFilter<std::int32_t>;
  template class InWavFilter<std::int64_t>;
  template class InWavFilter<float>;
  template class InWavFilter<double>;
}
