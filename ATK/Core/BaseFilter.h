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
    void set_input_port(int input_port, BaseFilter* filter, int output_port);
    
    /// Starts processing if reset
    void process(long size);
    
    void set_input_sampling_rate(int rate);
    int get_input_sampling_rate() const;
    void set_output_sampling_rate(int rate);
    int get_output_sampling_rate() const;
    
    /// Resets the filter so that it will process something if needed
    void reset();
    
  protected:
    /// The actual filter processing part
    void virtual process_impl(long size) = 0;
    /// Prepares the filter by retrieving the inputs arrays
    void virtual prepare_process(long size) = 0;
    /// Prepares the filter by resizing the outputs arrays
    void virtual prepare_outputs(long size) = 0;
    /// Returns the type that the filter processes
    int virtual get_type() const = 0;
    bool is_reset;
    
    virtual void setup();
    
    int nb_input_ports;
    int nb_output_ports;
    int input_sampling_rate;
    int output_sampling_rate;
    /// The connections to the output pins of some filters
    std::vector<std::pair<int, BaseFilter*> > connections;
  };
}

#endif

