/**
 * \file Base.cpp
 */

#include "Base.h"

#include <cstdint>

namespace ATK
{
  Base::Base(int nb_input_ports, int nb_output_ports)
  :nb_input_ports(nb_input_ports), nb_output_ports(nb_output_ports), connections(nb_input_ports, std::make_pair(-1, std::nullptr_t()))
  {
  }

  Base::~Base()
  {
  }

  void Base::setInputPort(int input_port, Base* filter, int output_port)
  {
    if(input_port >= 0 && input_port < nb_input_ports)
      connections[input_port] = std::make_pair(output_port, filter);
  }
}

