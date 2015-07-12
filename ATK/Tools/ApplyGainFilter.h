/**
 * \file ApplyGainFilter.h
 */

#ifndef ATK_TOOLS_APPLYGAINFILTER_H
#define ATK_TOOLS_APPLYGAINFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Gain "compressor". Has twice as many inputs channels as it has output channels
   * Even channels are signal, odd channels are gains, results is the product of both
   */
  template<typename DataType_>
  class ATK_TOOLS_EXPORT ApplyGainFilter : public TypedBaseFilter<DataType_>
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
    using Parent::output_delay;

  public:
    ApplyGainFilter(int nb_channels = 1);
    ~ApplyGainFilter();
    
  protected:
    virtual void process_impl(int64_t size) const override final;
    
  };
}

#endif
