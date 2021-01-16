/**
 * \file BaseFilter.h
 */

#ifndef ATK_CORE_BASEFILTER_H
#define ATK_CORE_BASEFILTER_H

#include <ATK/config.h>
#include <ATK/Core/config.h>

#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <gsl/gsl>

#if ATK_USE_THREADPOOL == 1
#include <tbb/queuing_mutex.h>
#endif

#if ATK_PROFILING == 1
#include <chrono>
#endif

#include <cstdint>
#include <string>
#include <vector>

namespace ATK
{
  /// Base class for all filters
  class BaseFilter
  {
  public:
    BaseFilter(const BaseFilter&) = delete;
    BaseFilter& operator=(const BaseFilter&) = delete;
    /*!
     * @brief Constructor for the core filter
     * @param nb_input_ports is the total number of input ports of this filter
     * @param nb_output_ports is the total number of output ports of this filter
     */
    ATK_CORE_EXPORT BaseFilter(gsl::index nb_input_ports, gsl::index nb_output_ports);
    /// Move constructor
    ATK_CORE_EXPORT BaseFilter(BaseFilter&& other) noexcept;
    /// Destructor
    virtual ATK_CORE_EXPORT ~BaseFilter();
    
    /*!
     * @brief Links this filter port to another filter's output port
     * @param input_port is the port number where this filter will receive something
     * @param filter is a pointer to the previous filter
     * @param output_port is the port number where this filter will be connected
     */
    ATK_CORE_EXPORT virtual void set_input_port(gsl::index input_port, gsl::not_null<BaseFilter*> filter, gsl::index output_port) = 0;
    ATK_CORE_EXPORT virtual void set_input_port(gsl::index input_port, BaseFilter& filter, gsl::index output_port);
    
    /// Starts processing after calling reset
    ATK_CORE_EXPORT void process(gsl::index size);
    /// As process, but doesn't call process_impl
    ATK_CORE_EXPORT void dryrun(gsl::index size);

#if ATK_USE_THREADPOOL == 1
    /// Allows threaded processing
    ATK_CORE_EXPORT void process_parallel(gsl::index size);
#endif

    /*!
     * @brief Setup the input sampling rate, must be in sync with the rest of the pipeline
     * @param rate is the input sampling rate of the plugin
     */
    ATK_CORE_EXPORT void set_input_sampling_rate(gsl::index rate);
    /// Returns this filter internal input sampling rate
    ATK_CORE_EXPORT gsl::index get_input_sampling_rate() const;
    /*!
    * @brief Setup the output sampling rate, must be in sync with the rest of the pipeline
    * @param rate is the output sampling rate of the plugin
    */
    ATK_CORE_EXPORT void set_output_sampling_rate(gsl::index rate);
    /// Returns this filter internal output sampling rate
    ATK_CORE_EXPORT gsl::index get_output_sampling_rate() const;
    
    /// Returns this filter number of input ports
    ATK_CORE_EXPORT gsl::index get_nb_input_ports() const;
    /*!
    * @brief Changes the number of input ports
    * Will trigger a full setup
    * @param nb_ports is the new number of input ports of the plugin
    */
    ATK_CORE_EXPORT virtual void set_nb_input_ports(gsl::index nb_ports);
    /// Returns this filter number of input ports
    ATK_CORE_EXPORT gsl::index get_nb_output_ports() const;
    /*!
    * @brief Changes the number of output ports
    * Will trigger a full setup
    * @param nb_ports is the new number of output ports of the plugin
    */
    ATK_CORE_EXPORT virtual void set_nb_output_ports(gsl::index nb_ports);
    /// Returns this filter input delay (additional pre-0 samples)
    ATK_CORE_EXPORT void set_input_delay(gsl::index delay);
    /// Returns this filter input delay (additional pre-0 samples)
    ATK_CORE_EXPORT gsl::index get_input_delay() const;
    /// Returns this filter output delay (additional pre-0 samples)
    ATK_CORE_EXPORT void set_output_delay(gsl::index delay);
    /// Returns this filter output delay (additional pre-0 samples)
    ATK_CORE_EXPORT gsl::index get_output_delay() const;
    /*!
    * @brief Changes the filter's latency
    * @param latency is the new latency
    */
    ATK_CORE_EXPORT virtual void set_latency(gsl::index latency);
    /// Returns this filter latency
    ATK_CORE_EXPORT gsl::index get_latency() const;
    /// Returns the pipeline global latency from this plugin
    ATK_CORE_EXPORT gsl::index get_global_latency() const;

    /// Resets the internal state of the filter (mandatory before processing a new clip in a DAW for instance)
    ATK_CORE_EXPORT virtual void full_setup();

    /// Resets the filter so that it will process something if needed
    void reset();
    /// Returns the type that the filter processes
    virtual int get_type() const = 0;
    /// Starts processing without calling reset
    template<bool must_process>
    void process_conditionnally(gsl::index size);
#if ATK_USE_THREADPOOL == 1
    /// Starts parallel processing without calling reset
    void process_conditionnally_parallel(gsl::index size);
#endif
  
  protected:
    /// The actual filter processing part
    virtual void process_impl(gsl::index size) const = 0;

    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(gsl::index size) = 0;
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(gsl::index size) = 0;
    /// Changes the internal check to allow a disconnected input port
    void allow_inactive_connection(unsigned int port);
    
    /// Use this call to recompute internal parameters
    ATK_CORE_EXPORT virtual void setup();

    /// Number of input ports
    gsl::index nb_input_ports{0};
    /// Number of output ports
    gsl::index nb_output_ports{0};
    /// Input sampling rate of the plugin
    gsl::index input_sampling_rate{0};
    /// Output sampling rate of the plugin
    gsl::index output_sampling_rate{0};
    /// The connections to the output pins of some filters
    std::vector<std::pair<gsl::index, BaseFilter*> > connections;

    /// Input delay of the input port
    gsl::index input_delay{0};
    /// Output delay of the input port
    gsl::index output_delay{0};
    
    /// Latency of the plugin
    gsl::index latency{0};
    /// Last processed size
    gsl::index last_size{0};

  private:
    boost::dynamic_bitset<> input_mandatory_connection;
    bool is_reset{false};
#if ATK_PROFILING == 1
    std::string class_name;
    std::chrono::steady_clock::duration input_conversion_time{0};
    std::chrono::steady_clock::duration output_conversion_time{0};
    std::chrono::steady_clock::duration process_time{0};
#endif
#if ATK_USE_THREADPOOL == 1
    tbb::queuing_mutex mutex;
#endif
  };
}

#endif

