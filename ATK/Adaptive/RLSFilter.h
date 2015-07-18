/**
 * \file RLSFilter.h
 */

#ifndef ATK_ADAPTIVE_RLSFILTER_H
#define ATK_ADAPTIVE_RLSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Recursive
   */
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT RLSFilter : public TypedBaseFilter<DataType_>
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
    using Parent::input_delay;

  public:
    RLSFilter(int64_t size);
    ~RLSFilter();
    
    void set_size(int64_t delay);
    int64_t get_size() const;

  protected:
    virtual void process_impl(int64_t size);
    
    int64_t size;
  };
}

#endif
