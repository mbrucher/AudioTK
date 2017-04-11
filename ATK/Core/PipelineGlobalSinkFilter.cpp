/**
 * \file PipelineGlobalSinkFilter.cpp
 */

#include "PipelineGlobalSinkFilter.h"

#include <algorithm>

#if ATK_USE_THREADPOOL == 1
#include <tbb/task_group.h>
#endif

namespace ATK
{
  PipelineGlobalSinkFilter::PipelineGlobalSinkFilter()
  :Parent(0, 0), activate_parallel(false)
  {
  }

  PipelineGlobalSinkFilter::~PipelineGlobalSinkFilter()
  {
  }
  
  void PipelineGlobalSinkFilter::add_filter(BaseFilter* filter)
  {
    if(std::find(filters.begin(), filters.end(), filter) == filters.end())
    {
      filters.push_back(filter);
    }
  }

  void PipelineGlobalSinkFilter::remove_filter(const BaseFilter* filter)
  {
    std::vector<BaseFilter*>::iterator it = std::find(filters.begin(), filters.end(), filter);
    if(it != filters.end())
    {
      filters.erase(it);
    }
  }

  int PipelineGlobalSinkFilter::get_type() const
  {
    return 0; // bogus
  }

  void PipelineGlobalSinkFilter::set_parallel(bool parallel)
  {
    activate_parallel = parallel;
  }

  void PipelineGlobalSinkFilter::prepare_process(std::size_t size)
  {
  }

  void PipelineGlobalSinkFilter::prepare_outputs(std::size_t size )
  {
  }

  void PipelineGlobalSinkFilter::process_impl(std::size_t size ) const
  {
    for (auto it = filters.begin(); it != filters.end(); ++it)
    {
      if ((*it) != nullptr)
      {
        (*it)->reset();
      }
    }
#if ATK_USE_THREADPOOL == 1
    if (activate_parallel)
    {
      tbb::task_group g;
      for (auto it = filters.begin(); it != filters.end(); ++it)
      {
        auto filter = (*it);
        g.run([=] {filter->process_conditionnally(size * (*it)->get_output_sampling_rate() / input_sampling_rate); });
      }
      g.wait();
    }
    else
#endif
    {
      for (auto it = filters.begin(); it != filters.end(); ++it)
      {
        (*it)->process_conditionnally(size * (*it)->get_output_sampling_rate() / input_sampling_rate);
      }
    }
  }

}
