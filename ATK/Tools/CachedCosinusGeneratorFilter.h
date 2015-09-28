/**
 * \file CachedCosinusGeneratorFilter.h
 */

#ifndef ATK_TOOLS_CACHEDCOSINUSGENERATORFILTER_H
#define ATK_TOOLS_CACHEDCOSINUSGENERATORFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   *
   */
  template<typename DataType_>
  class ATK_TOOLS_EXPORT CachedCosinusGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    CachedCosinusGeneratorFilter(int periods, int seconds = 1);
    ~CachedCosinusGeneratorFilter();

    void set_frequency(int periods, int seconds = 1);
    std::pair<int, int> get_frequency() const;

    void set_volume(DataType_ volume);
    DataType_ get_volume() const;

    void set_offset(DataType_ offset);
    DataType_ get_offset() const;

  protected:
    virtual void process_impl(int64_t size) const override final;
    virtual void setup() override final;
    
  private:
    mutable int64_t indice;
    int periods;
    int seconds;
    DataType_ volume;
    DataType_ offset;
    std::vector<DataType_> cache;
  };
}

#endif
