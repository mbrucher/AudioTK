/**
 * \file InPointerFilter.cpp
 */

#include "InPointerFilter.h"

#include <cstdint>

namespace ATK
{
  template<typename DataType>
  InPointerFilter<DataType>::InPointerFilter(const DataType* array, int channels, std::int64_t size, bool interleaved)
  :TypedBaseFilter<DataType>(0, interleaved?size:channels), offset(0), array(array), mysize(interleaved?channels:size), channels(interleaved?size:channels), interleaved(interleaved)
  {
  }
  
  template<typename DataType>
  InPointerFilter<DataType>::~InPointerFilter()
  {
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::set_pointer(const DataType* array, std::int64_t size)
  {
    this->array = array;
    mysize = size;
    offset = 0;
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::process_impl(std::int64_t size)
  {
    std::int64_t i;
    for(i = 0; i < size && (i + offset < mysize); ++i)
    {
      for(int j = 0; j < channels; ++j)
      {
        outputs[j][i] = array[channels * offset + (interleaved ? (j + i * channels) : (j * mysize + i))];
      }
    }
    for(; i < size; ++i)
    {
      for(int j = 0; j < channels; ++j)
      {
        outputs[j][i] = 0;
      }
    }
    
    offset += size;
  }
  
  template class InPointerFilter<std::int16_t>;
  template class InPointerFilter<std::int32_t>;
  template class InPointerFilter<std::int64_t>;
  template class InPointerFilter<float>;
  template class InPointerFilter<double>;
}
