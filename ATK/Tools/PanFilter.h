/**
 * \file PanFilter.h
 */

#ifndef ATK_TOOLS_PANFILTER_H
#define ATK_TOOLS_PANFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Creates a stereo signal with a specific pan law
  template<typename DataType_>
  class ATK_TOOLS_EXPORT PanFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /// Constructor
    explicit PanFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~PanFilter() override = default;
    
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
    /// Gets the pan law enum
    PAN_LAWS get_pan_law() const;
    /// Sets the pan value
    void set_pan(double pan);
    /// Gets the pan value
    double get_pan() const;
    
  protected:
    void process_impl(gsl::index size) const final;

  private:
    PAN_LAWS law = PAN_LAWS::SINCOS_0_CENTER;
    double pan{0};
  };
}

#endif
