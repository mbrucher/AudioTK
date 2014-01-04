/**
 * \file PanFilter.h
 */

#ifndef ATK_TOOLS_PANFILTER_H
#define ATK_TOOLS_PANFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class PanFilter : public TypedBaseFilter<DataType_>
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
    };
    
    void set_pan_law(PAN_LAWS law);
    void set_pan(double pan);
    
  protected:
    virtual void process_impl(int size);

  private:
    PAN_LAWS law;
    double pan;
  };
}

#endif
