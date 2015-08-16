/**
 * \file SinusGeneratorFilter.h
 */

#ifndef ATK_TOOLS_SINUSGENERATORFILTER_H
#define ATK_TOOLS_SINUSGENERATORFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   *
   */
  template<typename DataType_>
  class ATK_TOOLS_EXPORT SinusGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    SinusGeneratorFilter();
    ~SinusGeneratorFilter();

    void set_frequency(DataType_ frequency);
    DataType_ get_frequency() const;

    void set_volume(double volume);
    double get_volume() const;

    void set_offset(double offset);
    double get_offset() const;

    void full_setup() override final;

  protected:
    virtual void process_impl(int64_t size) const override final;
    
  private:
    DataType_ volume;
    DataType_ offset;
    DataType_ frequency;
    DataType_ frequ_cos;
    DataType_ frequ_sin;

    mutable DataType_ cos;
    mutable DataType_ sin;
  };
}

#endif
