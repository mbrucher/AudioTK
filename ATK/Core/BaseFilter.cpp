/**
 * \file BaseFilter.cpp
 */

#include "BaseFilter.h"

#include <cstdint>

namespace ATK
{
  BaseFilter::BaseFilter(int nb_input_ports, int nb_output_ports)
  :nb_input_ports(nb_input_ports), nb_output_ports(nb_output_ports), connections(nb_input_ports, std::make_pair(-1, std::nullptr_t()))
  {
  }

  BaseFilter::~BaseFilter()
  {
  }

  void BaseFilter::setInputPort(int input_port, BaseFilter* filter, int output_port)
  {
    if(input_port >= 0 && input_port < nb_input_ports)
      connections[input_port] = std::make_pair(output_port, filter);
  }
  
  void BaseFilter::update()
  {
    update_impl();
  }
  
  void BaseFilter::process()
  {
    process_impl();
  }
}

