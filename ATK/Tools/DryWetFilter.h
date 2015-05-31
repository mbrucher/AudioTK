/**
 * \file DryWetFilter.h
 */

#ifndef ATK_TOOLS_DRYWETFILTER_H
#define ATK_TOOLS_DRYWETFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType_>
  class ATK_TOOLS_EXPORT DryWetFilter : public TypedBaseFilter<DataType_>
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
    DryWetFilter(int nb_channels = 1);
    ~DryWetFilter();

    void set_dry(double dry);
    double get_dry() const;
    
  protected:
    virtual void process_impl(std::int64_t size) override final;
    
  private:
    double dry;
  };
}

#endif
