/**
 * \file PanFilter.cpp
 */

#include "PanFilter.h"

namespace ATK
{
  template<typename DataType_>
  PanFilter<DataType_>::PanFilter()
  :Parent(1, 2)
  {
    
  }
  
  template<typename DataType_>
  PanFilter<DataType_>::~PanFilter()
  {
    
  }
  
  template<typename DataType_>
  void PanFilter<DataType_>::process_impl(int size)
  {
    if(outputs_size[0] < size)
    {
      outputs[0].reset(new DataType[size]);
      outputs_size[0] = size;
    }
    if(outputs_size[1] < size)
    {
      outputs[1].reset(new DataType[size]);
      outputs_size[1] = size;
    }
    
    
  }
  
  template class PanFilter<std::int16_t>;
  template class PanFilter<std::int32_t>;
  template class PanFilter<std::int64_t>;
  template class PanFilter<float>;
  template class PanFilter<double>;
}
