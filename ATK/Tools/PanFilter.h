/**
 * \file PanFilter.h
 */

#ifndef ATK_TOOLS_PANFILTER_H
#define ATK_TOOLS_PANFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename DataType_>
  class ATK_TOOLS_EXPORT PanFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;

  public:
    PanFilter();
    ~PanFilter();
    
    enum PAN_LAWS {
      SINCOS_0_CENTER, //< Sin/cos law, center = 0 dB on each channel
      SINCOS_3_CENTER, //< Sin/cos law, center = -3 dB on each channel
      SQUARE_0_CENTER, //< square root law, center = 0 dB on each channel
      SQUARE_3_CENTER, //< square root law, center = -3 dB on each channel
      LINEAR_TAPER, //< linear taper law, center = -6 dB on each channel
      BALANCE, //< balance law, center = hard left/right = 0 dB on each channel, 
    };
    
    void set_pan_law(PAN_LAWS law);
    void set_pan(double pan);
    
  protected:
    virtual void process_impl(std::int64_t size);

  private:
    PAN_LAWS law;
    double pan;
  };
}

#endif
