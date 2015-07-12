/**
 * \file OffsetVolumeFilter.h
 */

#ifndef ATK_TOOLS_OFFSETVOLUMEFILTER_H
#define ATK_TOOLS_OFFSETVOLUMEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType_>
  class ATK_TOOLS_EXPORT OffsetVolumeFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    OffsetVolumeFilter(int nb_channels = 1);
    ~OffsetVolumeFilter();

    void set_volume(double volume);
    double get_volume() const;

    void set_offset(double offset);
    double get_offset() const;
    
  protected:
    virtual void process_impl(int64_t size) const override final;
    
  private:
    double offset;
    double volume;
  };
}

#endif
