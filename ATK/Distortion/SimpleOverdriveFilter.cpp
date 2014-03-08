/**
 * \file SimpleOverdriveFilter.cpp
 */

#include "SimpleOverdriveFilter.h"

namespace ATK
{
  template <typename DataType>
  SimpleOverdriveFilter<DataType>::SimpleOverdriveFilter()
  :TypedBaseFilter<DataType>(1, 1)
  {
    
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::setup()
  {
    
  }

  template <typename DataType>
  void SimpleOverdriveFilter<DataType>::process_impl(long size)
  {
    
  }

  template class SimpleOverdriveFilter<float>;
  template class SimpleOverdriveFilter<double>;
}
