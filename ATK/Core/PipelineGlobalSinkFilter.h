/**
 * \file PipelineGlobalSinkFilter.h
 */

#ifndef ATK_CORE_PIPELINEGLOBALSINKFILTER_H
#define ATK_CORE_PIPELINEGLOBALSINKFILTER_H

#include "BaseFilter.h"

#include <vector>

namespace ATK
{
  /// Class that can be used to process a pipeline that has more than one final sink. By adding these sinks to this filter, the processing is done for all sinks.
  class ATK_CORE_EXPORT PipelineGlobalSinkFilter : public BaseFilter
  {
  protected:
    typedef BaseFilter Parent;

  public:
    PipelineGlobalSinkFilter();
    virtual ~PipelineGlobalSinkFilter();
    
    void add_filter(BaseFilter* filter);
    void remove_filter(const BaseFilter* filter);

    int get_type() const override;
    void set_parallel(bool parallel);
  protected:
    virtual void process_impl(int64_t size) const override final;
    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(int64_t size) override final;
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(int64_t size) override final;

    std::vector<BaseFilter*> filters;
    bool activate_parallel;
  };
}

#endif
