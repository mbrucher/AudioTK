/**
 * \file OutPointerFilter.hxx
 */

#include "OutPointerFilter.h"

#include <cstring>

namespace ATK
{
  template<typename DataType>
  OutPointerFilter<DataType>::OutPointerFilter(DataType* array, int channels, gsl::index size, bool interleaved)
  :TypedBaseFilter<DataType>(static_cast<int>(interleaved?size:channels), 0), array(array), mysize(interleaved?channels:size), channels(static_cast<int>(interleaved?size:channels)), interleaved(interleaved)
  {
  }
  
  template<typename DataType>
  void OutPointerFilter<DataType>::set_pointer(DataType* array, gsl::index size)
  {
    this->array = array;
    mysize = size;
    offset = 0;
  }

  template<typename DataType>
  void OutPointerFilter<DataType>::process_impl(gsl::index size) const
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
        memcpy(reinterpret_cast<void*>(&array[offset + (j * mysize)]), reinterpret_cast<const void*>(converted_inputs[j]), static_cast<size_t>(i) * sizeof(DataType));
      }
    }
    else
    {
      for(gsl::index i = 0; i < size && (i + offset < mysize); ++i)
      {
        for(gsl::index j = 0; j < channels; ++j)
        {
          array[channels * offset + (j + i * channels)] = converted_inputs[j][i];
        }
      }
    }
    
    offset += size;
  }
}
