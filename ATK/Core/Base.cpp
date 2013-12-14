/**
 * \file Base.cpp
 */

#include "Base.h"

#include <cstdint>

namespace ATK
{
  template<typename DataType>
  Base<DataType>::Base(int nbInputPorts, int nbOutputPorts)
  :nbInputPorts(nbInputPorts), nbOutputPorts(nbOutputPorts), connections(nbInputPorts, NULL)
  {
  }

  template<typename DataType>
  Base<DataType>::~Base()
  {
  }

  template<typename DataType>
  void Base<DataType>::setInputPort(int port, Base<DataType> *filter)
  {
    if(port >= 0 && port < nbInputPorts)
      connections[port] = filter;
  }
  
  template Base<int16_t>;
  template Base<int32_t>;
  template Base<int64_t>;
  template Base<float>;
  template Base<double>;
}

