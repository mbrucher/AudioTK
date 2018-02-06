/**
 * \file PipelineGlobalSinkFilter.cpp
 */

#include <ATK/Core/PipelineGlobalSinkFilter.h>

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
  
  void PipelineGlobalSinkFilter::add_filter(gsl::not_null<BaseFilter*> filter)
  {
    if(std::find(filters.begin(), filters.end(), filter) == filters.end())
    {
      filters.push_back(filter);
    }
    else
    {
      throw std::runtime_error("Try to ad a filter that was aleady added");
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
      throw std::runtime_error("Try to remove a filter that was not added");
    }
  }

  int PipelineGlobalSinkFilter::get_type() const
  {
    return 0; // bogus
  }

  void PipelineGlobalSinkFilter::set_input_port(std::size_t input_port, gsl::not_null<BaseFilter*> filter, std::size_t output_port)
  {
    set_input_port(input_port, *filter, output_port);
  }

  void PipelineGlobalSinkFilter::set_input_port(std::size_t input_port, BaseFilter& filter, std::size_t output_port)
  {
    throw std::runtime_error("This function must not be called on pipelines");
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
        (*it)->process_conditionnally<true>(size * (*it)->get_output_sampling_rate() / input_sampling_rate);
      }
    }
  }

}
