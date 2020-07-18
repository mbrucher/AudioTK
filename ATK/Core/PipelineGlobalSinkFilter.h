/**
 * \file PipelineGlobalSinkFilter.h
 */

#ifndef ATK_CORE_PIPELINEGLOBALSINKFILTER_H
#define ATK_CORE_PIPELINEGLOBALSINKFILTER_H

#include <ATK/Core/BaseFilter.h>

#include <vector>

namespace ATK
{
  /// Class that can be used to process a pipeline that has more than one final sink. By adding these sinks to this filter, the processing is done for all sinks.
  class ATK_CORE_EXPORT PipelineGlobalSinkFilter final : public BaseFilter
  {
  protected:
    /// Simplify parent calls
    using Parent = BaseFilter;

  public:
    /// Constructor of the multiple sinks filter
    PipelineGlobalSinkFilter();
    /// destructor
    ~PipelineGlobalSinkFilter() override = default;
    
    /*!
     * @brief Adds a filter to the list of filters to process
     * @param filter is an additional filter
     */
    void add_filter(gsl::not_null<BaseFilter*> filter);
    /*!
    * @brief Removes a filter from the list of filters to process
    * @param filter is an additional filter
    */
    void remove_filter(gsl::not_null<const BaseFilter*> filter);

    int get_type() const final;
    void set_input_port(gsl::index input_port, gsl::not_null<BaseFilter*> filter, gsl::index output_port) final;
    void set_input_port(gsl::index input_port, BaseFilter& filter, gsl::index output_port) final;
    /*!
     * @brief Indicates if we can process the pipeline in parallel
     */
    void set_parallel(bool parallel);
  protected:
    void process_impl(gsl::index size) const final;
    void prepare_process(gsl::index size) final;
    void prepare_outputs(gsl::index size) final;

    /// List of filters in this sink
    std::vector<gsl::not_null<BaseFilter*>> filters;
    /// Are we in parallel mode?
    bool activate_parallel = false;
  };
}

#endif
