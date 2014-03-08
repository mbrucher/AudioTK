/**
 * \file SimpleOverdriveFilter.h
 */

#ifndef ATK_DISTORTION_SIMPLEOVERDRIVEFILTER_H
#define ATK_DISTORTION_SIMPLEOVERDRIVEFILTER_H

#include "../Core/TypedBaseFilter.h"

namespace ATK
{
  /**
   * First order filter template class
   */
  template<typename DataType_>
  class SimpleOverdriveFilter: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    
  public:
    SimpleOverdriveFilter();
    
  protected:
    void setup();
    void process_impl(long size);
    
  private:
  };
}

#endif
