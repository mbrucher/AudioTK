/**
 * \file BaseFilter.h
 */

#ifndef ATK_CORE_BASEFILTER_H
#define ATK_CORE_BASEFILTER_H

#include <cstdint>
#include <string>
#include <vector>

#include <ATK/config.h>
#include "config.h"

#if ATK_PROFILING == 1
#include <boost/timer/timer.hpp>
#endif

namespace ATK
{
  class BaseFilter
  {
  public:
    ATK_CORE_EXPORT BaseFilter(int nb_input_ports, int nb_output_ports);
    virtual ATK_CORE_EXPORT ~BaseFilter();
    
    /*!
       Links this filter port to another filter's output port
       @param input_port is the port number where this filter will receive something
       @param filter is a pointer to the previous filter
       @param output_port is the port number where this filter will be connected
     */
    ATK_CORE_EXPORT void set_input_port(int input_port, BaseFilter* filter, int output_port);
    
    /// Starts processing after calling reset
    ATK_CORE_EXPORT void process(std::int64_t size);
    
    ATK_CORE_EXPORT void set_input_sampling_rate(int rate);
    ATK_CORE_EXPORT int get_input_sampling_rate() const;
    ATK_CORE_EXPORT void set_output_sampling_rate(int rate);
    ATK_CORE_EXPORT int get_output_sampling_rate() const;
    
    ATK_CORE_EXPORT int get_nb_input_ports() const;
    ATK_CORE_EXPORT virtual void set_nb_input_ports(int nb_ports);
    ATK_CORE_EXPORT int get_nb_output_ports() const;
    ATK_CORE_EXPORT virtual void set_nb_output_ports(int nb_ports);
    ATK_CORE_EXPORT int get_input_delay() const;
    ATK_CORE_EXPORT int get_output_delay() const;

    /// Resets the filter so that it will process something if needed
    void reset();
    /// Returns the type that the filter processes
    virtual int get_type() const = 0;
    /// Starts processing without calling reset
    void process_conditionnally(std::int64_t size);
  
  protected:
    /// The actual filter processing part
    virtual void process_impl(std::int64_t size) = 0;
    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(std::int64_t size) = 0;
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(std::int64_t size) = 0;
    bool is_reset;
    
    ATK_CORE_EXPORT virtual void setup();
    ATK_CORE_EXPORT virtual void full_setup();

    int nb_input_ports;
    int nb_output_ports;
    int input_sampling_rate;
    int output_sampling_rate;
    /// The connections to the output pins of some filters
    std::vector<std::pair<int, BaseFilter*> > connections;

    int input_delay;
    int output_delay;

  private:
#if ATK_PROFILING == 1
    std::string class_name;
    boost::timer::nanosecond_type input_conversion_time;
    boost::timer::nanosecond_type output_conversion_time;
    boost::timer::nanosecond_type process_time;
#endif

  };
}

#endif

