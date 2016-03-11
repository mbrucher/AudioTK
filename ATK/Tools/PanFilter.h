/**
 * \file PanFilter.h
 */

#ifndef ATK_TOOLS_PANFILTER_H
#define ATK_TOOLS_PANFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Creates a stereo signal with a specific pan law
  template<typename DataType_>
  class ATK_TOOLS_EXPORT PanFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;

  public:
    /// Constructor
    PanFilter();
    /// Destructor
    ~PanFilter();
    
    /// Available laws
    enum class PAN_LAWS {
      /// Sin/cos law, center = 0 dB on each channel
      SINCOS_0_CENTER,
      /// Sin/cos law, center = -3 dB on each channel
      SINCOS_3_CENTER,
      /// square root law, center = 0 dB on each channel
      SQUARE_0_CENTER,
      /// square root law, center = -3 dB on each channel
      SQUARE_3_CENTER,
      /// linear taper law, center = -6 dB on each channel
      LINEAR_TAPER,
      /// balance law, center = hard left/right = 0 dB on each channel
      BALANCE,
    };
    
    /// Changes the pan law
    void set_pan_law(PAN_LAWS law);
    /// Sets the pan value
    void set_pan(double pan);
    /// Gets the pan value
    double get_pan() const;
    
  protected:
    virtual void process_impl(int64_t size) const override final;

  private:
    PAN_LAWS law;
    double pan;
  };
}

#endif
