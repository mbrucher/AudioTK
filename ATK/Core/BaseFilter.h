/**
 * \file BaseFilter.h
 */

#ifndef ATK_CORE_BASEFILTER_H
#define ATK_CORE_BASEFILTER_H

#include <vector>

namespace ATK
{
  class BaseFilter
  {
  public:
    BaseFilter(int nb_input_ports, int nb_output_ports);
    virtual ~BaseFilter();
    
    /*!
       Links this filter port to another filter's output port
       @param input_port is the port number where this filter will receive something
       @param filter is a pointer to the previous filter
       @param output_port is the port number where this filter will be connected
     */
    void setInputPort(int input_port, BaseFilter* filter, int output_port);
    
    void update();
    void process();
    
  protected:
    void virtual update_impl() = 0;
    void virtual process_impl() = 0;
    
    int nb_input_ports;
    int nb_output_ports;
    std::vector<std::pair<int, BaseFilter*> > connections;
  };
}

#endif

