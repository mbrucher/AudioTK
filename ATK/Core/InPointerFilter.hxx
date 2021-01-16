/**
 * \file InPointerFilter.hxx
 */

#include "InPointerFilter.h"

#include <cstring>

namespace ATK
{
  template<typename DataType>
  InPointerFilter<DataType>::InPointerFilter(const DataType* array, int channels, gsl::index size, bool interleaved)
  :TypedBaseFilter<DataType>(0, static_cast<int>(interleaved?size:channels)), array(array), mysize(interleaved?channels:size), channels(static_cast<int>(interleaved?size:channels)), interleaved(interleaved)
  {
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::set_pointer(const DataType* array, gsl::index size)
  {
    this->array = array;
    mysize = size;
    offset = 0;
  }
  
  template<typename DataType>
  void InPointerFilter<DataType>::process_impl(gsl::index size) const
  {
    if(!interleaved)
    {
      auto i = std::min(size, mysize - offset);
      if (mysize < offset)
      {
        i = 0;
      }
      for(gsl::index j = 0; j < channels; ++j)
      {
        memcpy(reinterpret_cast<void*>(outputs[j]), reinterpret_cast<const void*>(&array[offset + (j * mysize)]), static_cast<size_t>(i) * sizeof(DataType));
      }
      for(; i < size; ++i)
      {
        for(gsl::index j = 0; j < channels; ++j)
        {
          outputs[j][i] = TypeTraits<DataType>::Zero();
        }
      }
    }
    else
    {
      gsl::index i = 0;
      for(i = 0; i < size && (i + offset < mysize); ++i)
      {
        for(gsl::index j = 0; j < channels; ++j)
        {
          outputs[j][i] = array[channels * offset + (j + i * channels)];
        }
      }
      for(; i < size; ++i)
      {
        for(gsl::index j = 0; j < channels; ++j)
        {
          outputs[j][i] = TypeTraits<DataType>::Zero();
        }
      }
    }
    
    offset += size;
  }
}
