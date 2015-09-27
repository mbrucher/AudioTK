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
    BaseFilter(const BaseFilter&);
    BaseFilter& operator=(const BaseFilter&);
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
    ATK_CORE_EXPORT void process(int64_t size);
    
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
    ATK_CORE_EXPORT virtual void set_latency(uint64_t latency);
    ATK_CORE_EXPORT uint64_t get_latency() const;
    ATK_CORE_EXPORT uint64_t get_global_latency() const;

    /// Resets the filter so that it will process something if needed
    void reset();
    /// Returns the type that the filter processes
    virtual int get_type() const = 0;
    /// Starts processing without calling reset
    void process_conditionnally(int64_t size);
    /// Resets the internal state of the filter (mandatory before processing a new clip in a DAW for instance)
    ATK_CORE_EXPORT virtual void full_setup();
  
  protected:
    /// The actual filter processing part
    virtual void process_impl(int64_t size) const = 0;
    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(int64_t size) = 0;
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(int64_t size) = 0;
    bool is_reset;
    
    /// Use this call to recompute internal parameters
    ATK_CORE_EXPORT virtual void setup();

    int nb_input_ports;
    int nb_output_ports;
    int input_sampling_rate;
    int output_sampling_rate;
    /// The connections to the output pins of some filters
    std::vector<std::pair<int, BaseFilter*> > connections;

    int64_t input_delay;
    int64_t output_delay;
    
    uint64_t latency;

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

