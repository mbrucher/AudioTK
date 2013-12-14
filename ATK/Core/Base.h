/**
 * \file Base.h
 */

#ifndef ATK_CORE_BASE_H
#define ATK_CORE_BASE_H

#include <vector>

namespace ATK
{
  template<typename DataType>
  class Base
  {
  public:
    Base(int nbInputPorts, int nbOutputPorts);
    virtual ~Base();
    
    void setInputPort(int port, Base<DataType>* filter);
    
  protected:
    void virtual process() = 0;
    int nbInputPorts;
    int nbOutputPorts;
    std::vector<std::pair<int, Base<DataType> >* > connections;
  };
}

#endif

