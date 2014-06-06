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
  class ATK_CORE_EXPORT BaseFilter
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
    void set_input_port(int input_port, BaseFilter* filter, int output_port);
    
    /// Starts processing after calling reset
    void process(std::int64_t size);
    
    void set_input_sampling_rate(int rate);
    int get_input_sampling_rate() const;
    void set_output_sampling_rate(int rate);
    int get_output_sampling_rate() const;
    
    int get_nb_input_ports() const;
    virtual void set_nb_input_ports(int nb_ports);
    int get_nb_output_ports() const;
    virtual void set_nb_output_ports(int nb_ports);

    /// Resets the filter so that it will process something if needed
    void reset();
    /// Returns the type that the filter processes
    int virtual get_type() const = 0;
  
  protected:
    /// Starts processing without calling reset
    void process_conditionnally(std::int64_t size);
    /// The actual filter processing part
    void virtual process_impl(std::int64_t size) = 0;
    /// Prepares the filter by retrieving the inputs arrays
    void virtual prepare_process(std::int64_t size) = 0;
    /// Prepares the filter by resizing the outputs arrays
    void virtual prepare_outputs(std::int64_t size) = 0;
    bool is_reset;
    
    virtual void setup();
    
    int nb_input_ports;
    int nb_output_ports;
    int input_sampling_rate;
    int output_sampling_rate;
    /// The connections to the output pins of some filters
    std::vector<std::pair<int, BaseFilter*> > connections;

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

