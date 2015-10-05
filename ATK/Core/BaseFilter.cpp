/**
 * \file BaseFilter.cpp
 */

#include "BaseFilter.h"

#include <cstdint>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#if ATK_USE_THREADPOOL == 1
#include <tbb/task_group.h>
#endif

namespace ATK
{
  BaseFilter::BaseFilter(int nb_input_ports, int nb_output_ports)
  :is_reset(true), nb_input_ports(nb_input_ports), nb_output_ports(nb_output_ports),
   input_sampling_rate(0), output_sampling_rate(0),
   connections(nb_input_ports, std::make_pair(-1, nullptr)), input_delay(0), output_delay(0)
  {
#if ATK_PROFILING == 1
    input_conversion_time = 0;
    output_conversion_time = 0;
    process_time = 0;
#endif
  }

  BaseFilter::~BaseFilter()
  {
#if ATK_PROFILING == 1
    std::cerr << "Object of type " << class_name << std::endl;
    std::cerr << "Input conversion time " << input_conversion_time / 1e9 << "s" << std::endl;
    std::cerr << "Output conversion time " << output_conversion_time / 1e9 << "s" << std::endl;
    std::cerr << "Process time " << process_time / 1e9 << "s" << std::endl;
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

  void BaseFilter::set_input_port(int input_port, BaseFilter* filter, int output_port)
  {
    if(output_port < 0 || output_port >= filter->nb_output_ports)
    {
      throw std::runtime_error("Output port does not exist for this filter");
    }
    if(input_port >= 0 && input_port < nb_input_ports)
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
  
  void BaseFilter::set_input_sampling_rate(int rate)
  {
    input_sampling_rate = rate;
    if(output_sampling_rate == 0)
    {
      output_sampling_rate = rate;
    }
    full_setup();
  }
  
  int BaseFilter::get_input_sampling_rate() const
  {
    return input_sampling_rate;
  }
  
  void BaseFilter::set_output_sampling_rate(int rate)
  {
    output_sampling_rate = rate;
    full_setup();
  }
  
  int BaseFilter::get_output_sampling_rate() const
  {
    return output_sampling_rate;
  }

  int BaseFilter::get_input_delay() const
  {
    return input_delay;
  }

  int BaseFilter::get_output_delay() const
  {
    return output_delay;
  }

  void BaseFilter::process(int64_t size)
  {
    reset();
    process_conditionnally(size);
  }

#if ATK_USE_THREADPOOL == 1
  void BaseFilter::process_parallel(int64_t size)
  {
    reset();
    process_conditionnally_parallel(size);
  }
#endif

  void BaseFilter::process_conditionnally(int64_t size)
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
    for(auto it = connections.begin(); it != connections.end(); ++it)
    {
      if(it->second == nullptr)
      {
        throw std::runtime_error("Input port " + boost::lexical_cast<std::string>(it - connections.begin()) + " is not connected");
      }
      it->second->process_conditionnally(size * input_sampling_rate / output_sampling_rate);
    }
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
  }

#if ATK_USE_THREADPOOL == 1
  void BaseFilter::process_conditionnally_parallel(int64_t size)
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
      for (auto it = connections.begin(); it != connections.end(); ++it)
      {
        if (it->second == nullptr)
        {
          throw std::runtime_error("Input port " + boost::lexical_cast<std::string>(it - connections.begin()) + " is not connected");
        }
        auto filter = it->second;
        g.run([=]{filter->process_conditionnally_parallel(size * input_sampling_rate / output_sampling_rate); });
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
    }
  }
#endif

  int BaseFilter::get_nb_input_ports() const
  {
    return nb_input_ports;
  }

  void BaseFilter::set_nb_input_ports(int nb_ports)
  {
    connections.resize(nb_ports, std::make_pair(-1, nullptr));
    nb_input_ports = nb_ports;
  }
  
  int BaseFilter::get_nb_output_ports() const
  {
    return nb_output_ports;
  }
  
  void BaseFilter::set_nb_output_ports(int nb_ports)
  {
    nb_output_ports = nb_ports;
  }
}
