/**
 * \file OutPointerFilter.cpp
 */

#include "OutPointerFilter.h"

#include <cstdint>

namespace ATK
{
  template<typename DataType>
  OutPointerFilter<DataType>::OutPointerFilter(DataType* array, int channels, std::int64_t size, bool interleaved)
  :TypedBaseFilter<DataType>(channels, 0), offset(0), array(array), mysize(size), channels(channels), interleaved(interleaved)
  {
  }
  
  template<typename DataType>
  OutPointerFilter<DataType>::~OutPointerFilter()
  {
  }
  
  template<typename DataType>
  void OutPointerFilter<DataType>::process_impl(std::int64_t size)
  {
    std::int64_t i;
    for(i = 0; i < size && (i + offset < mysize); ++i)
    {
      for(int j = 0; j < channels; ++j)
      {
        array[channels * offset + (interleaved ? (j + i * channels) : (j * mysize + i))] = converted_inputs[j][i];
      }
    }
    
    offset += size;
  }
  
  template class OutPointerFilter<std::int16_t>;
  template class OutPointerFilter<std::int32_t>;
  template class OutPointerFilter<std::int64_t>;
  template class OutPointerFilter<float>;
  template class OutPointerFilter<double>;
}
