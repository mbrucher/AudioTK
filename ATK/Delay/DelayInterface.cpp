/**
 * \file DelayInterface.cpp
 */

#include <ATK/Delay/DelayInterface.h>

namespace ATK
{
  DelayInterface::~DelayInterface()
  {
  }
  
  template<class DataType>
  UniversalDelayInterface<DataType>::~UniversalDelayInterface()
  {
  }
  
  template class UniversalDelayInterface<float>;
  template class UniversalDelayInterface<double>;
}
