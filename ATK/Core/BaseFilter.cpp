/**
 * \file BaseFilter.cpp
 */

#include "BaseFilter.h"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#if ATK_USE_THREADPOOL == 1
#include <tbb/task_group.h>
#endif

namespace ATK
{
  BaseFilter::BaseFilter(unsigned int nb_input_ports, unsigned int nb_output_ports)
  :nb_input_ports(nb_input_ports), nb_output_ports(nb_output_ports),
   input_sampling_rate(0), output_sampling_rate(0),
   connections(nb_input_ports, std::make_pair(-1, nullptr)), input_delay(0), output_delay(0),
   latency(0), is_reset(false)
#if ATK_PROFILING == 1
  , input_conversion_time(0), output_conversion_time(0), process_time(0)
#endif
  {
  }
  
  BaseFilter::BaseFilter(BaseFilter&& other)
  :nb_input_ports(other.nb_input_ports), nb_output_ports(other.nb_output_ports), input_sampling_rate(other.input_sampling_rate), output_sampling_rate(other.output_sampling_rate), connections(std::move(other.connections)), input_delay(other.input_delay), output_delay(std::move(other.output_delay)), latency(std::move(other.latency)), is_reset(std::move(other.is_reset))
#if ATK_PROFILING == 1
  , input_conversion_time(0), output_conversion_time(0), process_time(0)
#endif
  {
    
  }

  BaseFilter::~BaseFilter()
  {
#if ATK_PROFILING == 1
    std::cerr << "Object of type " << class_name << std::endl;
    std::cerr << "Input conversion time " << std::chrono::duration_cast<std::chrono::microseconds>(input_conversion_time).count() << "us" << std::endl;
    std::cerr << "Output conversion time " << std::chrono::duration_cast<std::chrono::microseconds>(output_conversion_time).count() << "us" << std::endl;
    std::cerr << "Process time " << std::chrono::duration_cast<std::chrono::microseconds>(process_time).count() << "us" << std::endl;
#endif
  }
  
  void BaseFilter::reset()
  {
    if (!is_reset)
    {
      for (auto it = connections.begin(); it != connections.end(); ++it)
      {
        if (it->second)
        {
          it->second->reset();
        }
      }
      is_reset = true;
    }
  }
  
  void BaseFilter::setup()
  {
  }

  void BaseFilter::full_setup()
  {
#if ATK_PROFILING == 1
    class_name = typeid(*this).name();
#endif
    setup();
  }

  void BaseFilter::set_input_port(unsigned int input_port, BaseFilter* filter, unsigned int output_port)
  {
    if(output_port >= filter->nb_output_ports)
    {
      throw std::runtime_error("Output port does not exist for this filter");
    }
    if(input_port < nb_input_ports)
    {
      connections[input_port] = std::make_pair(output_port, filter);
      if(filter->get_output_sampling_rate() != get_input_sampling_rate())
      {
        throw std::runtime_error("Input sample rate from this filter must be equal to the output sample rate of the connected filter");
      }
    }
    else
    {
      throw std::runtime_error("Input port doesn't exist for this filter");
    }
  }
  
  void BaseFilter::set_input_sampling_rate(std::size_t rate)
  {
    input_sampling_rate = rate;
    if(output_sampling_rate == 0)
    {
      output_sampling_rate = rate;
    }
    full_setup();
  }
  
  std::size_t BaseFilter::get_input_sampling_rate() const
  {
    return input_sampling_rate;
  }
  
  void BaseFilter::set_output_sampling_rate(std::size_t rate)
  {
    output_sampling_rate = rate;
    full_setup();
  }
  
  std::size_t BaseFilter::get_output_sampling_rate() const
  {
    return output_sampling_rate;
  }

  std::size_t BaseFilter::get_input_delay() const
  {
    return input_delay;
  }

  std::size_t BaseFilter::get_output_delay() const
  {
    return output_delay;
  }

  void BaseFilter::process(std::size_t size)
  {
    reset();
    process_conditionnally(size);
  }

#if ATK_USE_THREADPOOL == 1
  void BaseFilter::process_parallel(std::size_t size)
  {
    reset();
    process_conditionnally_parallel(size);
  }
#endif

  void BaseFilter::process_conditionnally(std::size_t size)
  {
    if(size == 0)
    {
      return;
    }
    if(output_sampling_rate == 0)
    {
      throw std::runtime_error("Output sampling rate is 0, must be non 0 to compute the needed size for filters processing");
    }
    if(!is_reset)
    {
      return;
    }
    for(std::size_t port = 0; port < connections.size(); ++port)
    {
      if(connections[port].second == nullptr)
      {
        if(!input_mandatory_connection[port])
          throw std::runtime_error("Input port " + std::to_string(port) + " is not connected");
      }
      else
      {
        assert(output_sampling_rate);
        connections[port].second->process_conditionnally(uint64_t(size) * input_sampling_rate / output_sampling_rate);
      }
    }
#if ATK_PROFILING == 1
    auto timer = std::chrono::steady_clock::now();
#endif
    prepare_process(uint64_t(size) * input_sampling_rate / output_sampling_rate);
#if ATK_PROFILING == 1
    auto timer2 = std::chrono::steady_clock::now();
    input_conversion_time += (timer2 - timer);
    timer = timer2;
#endif
    prepare_outputs(size);
#if ATK_PROFILING == 1
    timer2 = std::chrono::steady_clock::now();
    output_conversion_time += (timer2 - timer);
    timer = timer2;
#endif
    process_impl(size);
#if ATK_PROFILING == 1
    timer2 = std::chrono::steady_clock::now();
    process_time += (timer2 - timer);
    timer = timer2;
#endif
    is_reset = false;
    last_size = size;
  }

#if ATK_USE_THREADPOOL == 1
  void BaseFilter::process_conditionnally_parallel(std::size_t size)
  {
    if (size == 0)
    {
      return;
    }
    if (output_sampling_rate == 0)
    {
      throw std::runtime_error("Output sampling rate is 0, must be non 0 to compute the needed size for filters processing");
    }
    { // lock this entire loop, as we only want to do the processing if we are not reseted
      tbb::queuing_mutex::scoped_lock lock(mutex);
      if (!is_reset)
      {
        return;
      }
      tbb::task_group g;
      for(std::size_t port = 0; port < connections.size(); ++port)
      {
        if(connections[port].second == nullptr)
        {
          if(!input_mandatory_connection[port])
          throw std::runtime_error("Input port " + std::to_string(port) + " is not connected");
        }
        else
        {
          assert(output_sampling_rate);
          auto filter = connections[port];
          g.run([=]{filter->process_conditionnally_parallel(size * input_sampling_rate / output_sampling_rate); });
        }
      }
      g.wait();
#if ATK_PROFILING == 1
      boost::timer::cpu_timer timer;
#endif
      prepare_process(size * input_sampling_rate / output_sampling_rate);
#if ATK_PROFILING == 1
      boost::timer::cpu_times const input_elapsed_times(timer.elapsed());
      input_conversion_time += (input_elapsed_times.system + input_elapsed_times.user);
#endif
      prepare_outputs(size);
#if ATK_PROFILING == 1
      boost::timer::cpu_times const output_elapsed_times(timer.elapsed());
      output_conversion_time += (output_elapsed_times.system + output_elapsed_times.user);
#endif
      process_impl(size);
#if ATK_PROFILING == 1
      boost::timer::cpu_times const process_elapsed_times(timer.elapsed());
      process_time += (process_elapsed_times.system + process_elapsed_times.user);
#endif
      is_reset = false;
      last_size = size;
    }
  }
#endif

  std::size_t BaseFilter::get_nb_input_ports() const
  {
    return nb_input_ports;
  }

  void BaseFilter::set_nb_input_ports(std::size_t nb_ports)
  {
    connections.resize(nb_ports, std::make_pair(-1, nullptr));
    input_mandatory_connection.reset(nb_ports);
    nb_input_ports = nb_ports;
  }
  
  void BaseFilter::allow_inactive_connection(unsigned int port)
  {
    input_mandatory_connection[port] = true;
  }

  std::size_t BaseFilter::get_nb_output_ports() const
  {
    return nb_output_ports;
  }
  
  void BaseFilter::set_nb_output_ports(std::size_t nb_ports)
  {
    nb_output_ports = nb_ports;
  }
  
  void BaseFilter::set_latency(std::size_t latency)
  {
    this->latency = latency;
  }

  std::size_t BaseFilter::get_latency() const
  {
    return latency;
  }

  std::size_t BaseFilter::get_global_latency() const
  {
    std::size_t global_latency = 0;
    for(auto it = connections.begin(); it != connections.end(); ++it)
    {
      if(it->second == nullptr)
      {
        throw std::runtime_error("Input port " + std::to_string(it - connections.begin()) + " is not connected");
      }
      
      global_latency = std::max(global_latency, it->second->get_global_latency());
    }
    return global_latency + latency;
  }

}
