/**
 * \file DecimationFilter.h
 */

#ifndef ATK_TOOLS_DECIMATIONFILTER_H
#define ATK_TOOLS_DECIMATIONFILTER_H

#include "../Core/TypedBaseFilter.h"
#include "config.h"

namespace ATK
{
  template<class DataType_>
  class ATK_TOOLS_EXPORT DecimationFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;

    int decimation;

  public:
    DecimationFilter(int nb_channels = 1);
    ~DecimationFilter();
    
  protected:
    virtual void process_impl(std::int64_t size);
    void setup();
  };
}

#endif
