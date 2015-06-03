/**
 * \file PipelineGlobalSinkFilter.cpp
 */

#include "PipelineGlobalSinkFilter.h"

#include <algorithm>

namespace ATK
{
  PipelineGlobalSinkFilter::PipelineGlobalSinkFilter()
  :Parent(0, 0)
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

  void PipelineGlobalSinkFilter::prepare_process( std::int64_t size )
  {
  }

  void PipelineGlobalSinkFilter::prepare_outputs( std::int64_t size )
  {
  }

  void PipelineGlobalSinkFilter::process_impl( std::int64_t size )
  {
    for (auto it = filters.begin(); it != filters.end(); ++it)
    {
      if ((*it) != nullptr)
      {
        (*it)->reset();
      }
    }
    for (auto it = filters.begin(); it != filters.end(); ++it)
    {
      (*it)->process_conditionnally(size * (*it)->get_output_sampling_rate() / input_sampling_rate);
    }
  }

}
