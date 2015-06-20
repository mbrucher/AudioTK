/**
 * \file InPointerFilter.cpp
 */

#include "InPointerFilter.h"

#include <cstdint>
#include <cstring>

namespace ATK
{
  template<typename DataType>
  InPointerFilter<DataType>::InPointerFilter(const DataType* array, int channels, int64_t size, bool interleaved)
  :TypedBaseFilter<DataType>(0, interleaved?size:channels), offset(0), array(array), mysize(interleaved?channels:size), channels(static_cast<int>(interleaved?size:channels)), interleaved(interleaved)
  {
  }
  
  template<typename DataType>
  InPointerFilter<DataType>::~InPointerFilter()
  {
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::set_pointer(const DataType* array, int64_t size)
  {
    this->array = array;
    mysize = size;
    offset = 0;
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::process_impl(int64_t size) const
  {
    if(!interleaved)
    {
      int64_t i = std::min(size, mysize - offset);
      for(int j = 0; j < channels; ++j)
      {
        memcpy(reinterpret_cast<void*>(outputs[j]), reinterpret_cast<const void*>(&array[offset + (j * mysize)]), i * sizeof(DataType));
      }
      for(; i < size; ++i)
      {
        for(int j = 0; j < channels; ++j)
        {
          outputs[j][i] = 0;
        }
      }
    }
    else
    {
      int64_t i = 0;
      for(i = 0; i < size && (i + offset < mysize); ++i)
      {
        for(int j = 0; j < channels; ++j)
        {
          outputs[j][i] = array[channels * offset + (j + i * channels)];
        }
      }
      for(; i < size; ++i)
      {
        for(int j = 0; j < channels; ++j)
        {
          outputs[j][i] = 0;
        }
      }
    }
    
    offset += size;
  }
  
  template class InPointerFilter<std::int16_t>;
  template class InPointerFilter<std::int32_t>;
  template class InPointerFilter<int64_t>;
  template class InPointerFilter<float>;
  template class InPointerFilter<double>;
}
