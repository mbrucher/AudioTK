/**
 * \file LMSFilter.cpp
 */

#include "LMSFilter.h"

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include <Eigen/Core>

namespace ATK
{
  template<typename DataType_>
  class LMSFilter<DataType_>::LMSFilterImpl
  {
  public:
    LMSFilterImpl(std::size_t size)
    {

    }

  };

  template<typename DataType_>
  LMSFilter<DataType_>::LMSFilter(std::size_t size)
  :Parent(2, 1), global_size(size), impl(new LMSFilterImpl(size))
  {
    input_delay = size + 1;
  }
  
  template<typename DataType_>
  LMSFilter<DataType_>::~LMSFilter()
  {
  }
  
  template<typename DataType_>
  void LMSFilter<DataType_>::set_size(std::size_t size)
  {
    if(size == 0)
    {
      throw std::out_of_range("Size must be strictly positive");
    }

    input_delay = size+1;
    this->global_size = size;
  }

  template<typename DataType_>
  std::size_t LMSFilter<DataType_>::get_size() const
  {
    return global_size;
  }
  
  template<typename DataType_>
  void LMSFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    
    for(std::size_t i = 0; i < size; ++i)
    {
      // compute next sample
      output[i] = input[i];
      
    }
  }

  template class LMSFilter<float>;
  template class LMSFilter<double>;
}
