/**
 * \file BaseFilter.cpp
 */

#include "BaseFilter.h"

#include <cstdint>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

namespace ATK
{
  BaseFilter::BaseFilter(int nb_input_ports, int nb_output_ports)
  :is_reset(true), nb_input_ports(nb_input_ports), nb_output_ports(nb_output_ports),
   input_sampling_rate(0), output_sampling_rate(0),
   connections(nb_input_ports, std::make_pair(-1, std::nullptr_t()))
  {
  }

  BaseFilter::~BaseFilter()
  {
  }
  
  void BaseFilter::reset()
  {
    for(auto it = connections.begin(); it != connections.end(); ++it)
    {
      it->second->reset();
    }
    is_reset = true;
  }
  
  void BaseFilter::setup()
  {
  }

  void BaseFilter::set_input_port(int input_port, BaseFilter* filter, int output_port)
  {
    if(input_port >= 0 && input_port < nb_input_ports)
    {
      connections[input_port] = std::make_pair(output_port, filter);
      if(filter->get_output_sampling_rate() != get_input_sampling_rate())
      {
        throw std::runtime_error("Input sample rate from this filter must be equal to the output sample rate of the connected filter");
      }
    }
  }
  
  void BaseFilter::set_input_sampling_rate(int rate)
  {
    input_sampling_rate = rate;
    if(output_sampling_rate == 0)
    {
      output_sampling_rate = rate;
    }
    setup();
  }
  
  int BaseFilter::get_input_sampling_rate() const
  {
    return input_sampling_rate;
  }
  
  void BaseFilter::set_output_sampling_rate(int rate)
  {
    output_sampling_rate = rate;
    setup();
  }
  
  int BaseFilter::get_output_sampling_rate() const
  {
    return output_sampling_rate;
  }

  void BaseFilter::process(long size)
  {
    if(!is_reset)
    {
      return;
    }
    for(auto it = connections.begin(); it != connections.end(); ++it)
    {
      if(it->second == std::nullptr_t(0))
      {
        throw std::runtime_error("Input port " + boost::lexical_cast<std::string>(it - connections.begin()) + " is not connected");
      }
      it->second->process(size * input_sampling_rate / output_sampling_rate);
    }
    prepare_process(size * input_sampling_rate / output_sampling_rate);
    prepare_outputs(size);
    process_impl(size);
    is_reset = false;
  }
}
