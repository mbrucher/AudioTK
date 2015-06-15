/**
 * \file PowerFilter.h
 */

#ifndef ATK_DYNAMIC_POWERFILTER_H
#define ATK_DYNAMIC_POWERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Creates an output signal with the filter power of the input (computed with an AR1)
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT PowerFilter : public TypedBaseFilter<DataType_>
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
    PowerFilter(int nb_channels = 1);
    ~PowerFilter();

    void set_memory(DataType_ memory_factor);
    DataType_ get_memory() const;
    
  protected:
    virtual void process_impl(std::int64_t size) const override final;
    
  private:
    DataType_ memory_factor;
  };
}

#endif
