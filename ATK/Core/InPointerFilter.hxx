/**
 * \file InPointerFilter.hxx
 */

#include <ATK/Core/InPointerFilter.h>

#include <cstring>

namespace ATK
{
  template<typename DataType>
  InPointerFilter<DataType>::InPointerFilter(const DataType* array, int channels, std::size_t size, bool interleaved)
  :TypedBaseFilter<DataType>(0, static_cast<int>(interleaved?size:channels)), offset(0), array(array), mysize(interleaved?channels:size), channels(static_cast<int>(interleaved?size:channels)), interleaved(interleaved)
  {
  }
  
  template<typename DataType>
  InPointerFilter<DataType>::~InPointerFilter()
  {
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::set_pointer(const DataType* array, std::size_t size)
  {
    this->array = array;
    mysize = size;
    offset = 0;
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::process_impl(std::size_t size) const
  {
    if(!interleaved)
    {
      auto i = std::min(size, mysize - offset);
      for(unsigned int j = 0; j < channels; ++j)
      {
        memcpy(reinterpret_cast<void*>(outputs[j]), reinterpret_cast<const void*>(&array[offset + (j * mysize)]), static_cast<size_t>(i) * sizeof(DataType));
      }
      for(; i < size; ++i)
      {
        for(unsigned int j = 0; j < channels; ++j)
        {
        outputs[j][i] = TypeTraits<DataType>::Zero();
        }
      }
    }
    else
    {
      std::size_t i = 0;
      for(i = 0; i < size && (i + offset < mysize); ++i)
      {
        for(unsigned int j = 0; j < channels; ++j)
        {
          outputs[j][i] = array[channels * offset + (j + i * channels)];
        }
      }
      for(; i < size; ++i)
      {
        for(unsigned int j = 0; j < channels; ++j)
        {
          outputs[j][i] = TypeTraits<DataType>::Zero();
        }
      }
    }
    
    offset += size;
  }
}
