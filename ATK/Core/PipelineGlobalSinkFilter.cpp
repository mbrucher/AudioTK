/**
 * \file PipelineGlobalSinkFilter.cpp
 */

#include <ATK/Core/PipelineGlobalSinkFilter.h>
#include <ATK/Core/Utilities.h>

#include <algorithm>

#if ATK_USE_THREADPOOL == 1
#include <tbb/task_group.h>
#endif

namespace ATK
{
  PipelineGlobalSinkFilter::PipelineGlobalSinkFilter()
  :Parent(0, 0)
  {
  }

  PipelineGlobalSinkFilter::~PipelineGlobalSinkFilter()
  {
  }
  
  void PipelineGlobalSinkFilter::add_filter(gsl::not_null<BaseFilter*> filter)
  {
    if(std::find(filters.begin(), filters.end(), filter) == filters.end())
    {
      filters.push_back(filter);
    }
    else
    {
      throw RuntimeError("Try to ad a filter that was aleady added");
    }
  }

  void PipelineGlobalSinkFilter::remove_filter(gsl::not_null<const BaseFilter*> filter)
  {
    auto it = std::find(filters.begin(), filters.end(), filter);
    if(it != filters.end())
    {
      filters.erase(it);
    }
    else
    {
      throw RuntimeError("Try to remove a filter that was not added");
    }
  }

  int PipelineGlobalSinkFilter::get_type() const
  {
    return 0; // bogus
  }

  void PipelineGlobalSinkFilter::set_input_port(gsl::index input_port, gsl::not_null<BaseFilter*> filter, gsl::index output_port)
  {
    set_input_port(input_port, *filter, output_port);
  }

  void PipelineGlobalSinkFilter::set_input_port(gsl::index input_port, BaseFilter& filter, gsl::index output_port)
  {
    throw RuntimeError("This function must not be called on pipelines");
  }

  void PipelineGlobalSinkFilter::set_parallel(bool parallel)
  {
    activate_parallel = parallel;
  }

  void PipelineGlobalSinkFilter::prepare_process(gsl::index size)
  {
    // Nothing to do
  }

  void PipelineGlobalSinkFilter::prepare_outputs(gsl::index size )
  {
    // Nothing to do
  }

  void PipelineGlobalSinkFilter::process_impl(gsl::index size ) const
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
        g.run([=] {filter->process_conditionnally(uint64_t(size) * (*it)->get_output_sampling_rate() / input_sampling_rate); });
      }
      g.wait();
      return;
    }
#endif
    for (auto it = filters.begin(); it != filters.end(); ++it)
    {
      (*it)->process_conditionnally<true>(uint64_t(size) * (*it)->get_output_sampling_rate() / input_sampling_rate);
    }
  }

}
