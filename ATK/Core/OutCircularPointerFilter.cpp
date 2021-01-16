/**
 * \file OutCircularPointerFilter.cpp
 */

#include "OutCircularPointerFilter.h"

#include <algorithm>
#include <complex>
#include <cstring>

namespace ATK
{
  template<typename DataType>
  OutCircularPointerFilter<DataType>::OutCircularPointerFilter()
  :TypedBaseFilter<DataType>(1, 0)
  {
  }
  
  template<typename DataType>
  void OutCircularPointerFilter<DataType>::full_setup()
  {
    last_checked_out_buffer = -1;
    offset = 0;
    array.fill(0);
  }

  template<typename DataType>
  void OutCircularPointerFilter<DataType>::process_impl(gsl::index size) const
  {
    auto update_size = std::min(size, static_cast<gsl::index>(array.size()) - offset);
    memcpy(reinterpret_cast<void*>(&array[offset]), reinterpret_cast<const void*>(converted_inputs[0]), static_cast<size_t>(update_size) * sizeof(DataType));
    offset += update_size;
    if(offset == array.size())
    {
      auto additional_update_size = size - update_size;
      memcpy(reinterpret_cast<void*>(array.data()), reinterpret_cast<const void*>(converted_inputs[0] + update_size), static_cast<size_t>(additional_update_size) * sizeof(DataType));
      offset = additional_update_size;
    }
    
    current_slice = offset / slice_size; // Current slice we are filing
  }
  
  template<typename DataType>
  auto OutCircularPointerFilter<DataType>::get_last_slice(bool& process) -> const SliceBuffer&
  {
    process = false;
    if(last_checked_out_buffer != current_slice)
    {
      process = true;
      auto first_index = static_cast<int>((current_slice - nb_slices + 2) * slice_size);
      if(first_index < 0)
      {
        first_index += nb_slices * slice_size;
      }
      auto last_index = std::min(first_index + out_slice_size, nb_slices * slice_size) - first_index;
      for(gsl::index i = 0; i < last_index; ++i)
      {
        last_slice[i] = array[first_index + i];
      }
      auto remaining_index = out_slice_size - last_index;
      for(gsl::index i = 0; i < remaining_index; ++i)
      {
        last_slice[i + last_index] = array[i];
      }
      
      last_checked_out_buffer = current_slice;
    }
    return last_slice;
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class OutCircularPointerFilter<std::int16_t>;
  template class OutCircularPointerFilter<std::int32_t>;
  template class OutCircularPointerFilter<std::int64_t>;
#endif
  template class OutCircularPointerFilter<float>;
#if ATK_ENABLE_INSTANTIATION
  template class OutCircularPointerFilter<double>;
  template class OutCircularPointerFilter<std::complex<float>>;
  template class OutCircularPointerFilter<std::complex<double>>;
#endif
}
