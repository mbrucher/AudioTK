
%{
#include <ATK/Tools/PanFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class PanFilter: public BaseFilter
  {
  public:
    PanFilter(unsigned int nb_channels = 1);
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
    double get_pan() const;
  };

  ATKProperty(PanFilter<std::int16_t>, pan, get_pan, set_pan);
  ATKProperty(PanFilter<std::int32_t>, pan, get_pan, set_pan);
  ATKProperty(PanFilter<std::int64_t>, pan, get_pan, set_pan);
  ATKProperty(PanFilter<float>, pan, get_pan, set_pan);
  ATKProperty(PanFilter<double>, pan, get_pan, set_pan);
  ATKProperty(PanFilter<std::complex<float> >, pan, get_pan, set_pan);
  ATKProperty(PanFilter<std::complex<double> >, pan, get_pan, set_pan);
}

%template(Int16PanFilter) ATK::PanFilter<std::int16_t>;
%template(Int32PanFilter) ATK::PanFilter<std::int32_t>;
%template(Int64PanFilter) ATK::PanFilter<std::int64_t>;
%template(FloatPanFilter) ATK::PanFilter<float>;
%template(DoublePanFilter) ATK::PanFilter<double>;
%template(ComplexFloatPanFilter) ATK::PanFilter<std::complex<float> >;
%template(ComplexDoublePanFilter) ATK::PanFilter<std::complex<double> >;
