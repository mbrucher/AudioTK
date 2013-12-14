/**
 * \file Base.h
 */

#ifndef ATK_CORE_BASE_H
#define ATK_CORE_BASE_H

#include <vector>

namespace ATK
{
  class Base
  {
  public:
    Base(int nb_input_ports, int nb_output_ports);
    virtual ~Base();
    
    void setInputPort(int input_port, Base* filter, int output_port);
    
  protected:
    void virtual process() = 0;
    int nb_input_ports;
    int nb_output_ports;
    std::vector<std::pair<int, Base*> > connections;
  };
}

#endif

