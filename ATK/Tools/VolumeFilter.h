/**
 * \file VolumeFilter.h
 */

#ifndef ATK_TOOLS_VOLUMEFILTER_H
#define ATK_TOOLS_VOLUMEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType_>
  class ATK_TOOLS_EXPORT VolumeFilter : public TypedBaseFilter<DataType_>
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
    VolumeFilter(int nb_channels);
    ~VolumeFilter();

    void set_volume(double volume);
    void set_volume_db(double volume_db);
    
  protected:
    virtual void process_impl(std::int64_t size);
    
  private:
    double volume;
  };
}

#endif
