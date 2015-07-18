/**
 * \file RLSFilter.cpp
 */

#include "RLSFilter.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  RLSFilter<DataType_>::RLSFilter(int64_t size)
  :Parent(1, 1)
  {
  }
  
  template<typename DataType_>
  RLSFilter<DataType_>::~RLSFilter()
  {
    
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_size(int64_t size)
  {
    if(size < 0)
    {
      throw std::out_of_range("Size must be positive");
    }

    this->size = size;
  }

  template<typename DataType_>
  int64_t RLSFilter<DataType_>::get_size() const
  {
    return size;
  }

  template<typename DataType_>
  void RLSFilter<DataType_>::process_impl(int64_t size)
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
  }
  
  template class RLSFilter<float>;
  template class RLSFilter<double>;
}
