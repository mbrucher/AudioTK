
%{
#include <ATK/EQ/PedalToneStackFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class SD1ToneCoefficients: public BaseFilter
  {
  public:
    SD1ToneCoefficients();
    ~SD1ToneCoefficients();
    
    void set_tone(DataType alpha);
    DataType get_tone() const;
  };

  template<class DataType>
  class TS9ToneCoefficients: public BaseFilter
  {
  public:
    TS9ToneCoefficients();
    ~TS9ToneCoefficients();
    
    void set_tone(DataType alpha);
    DataType get_tone() const;
  };

  ATKProperty(IIRFilter<SD1ToneCoefficients<float> >, tone, get_tone, set_tone);
  ATKProperty(IIRFilter<SD1ToneCoefficients<float> >, tone, get_tone, set_tone);
  ATKProperty(IIRFilter<TS9ToneCoefficients<double> >, tone, get_tone, set_tone);
  ATKProperty(IIRFilter<TS9ToneCoefficients<double> >, tone, get_tone, set_tone);
}

%template(FloatSD1ToneCoefficients) ATK::SD1ToneCoefficients<float>;
%template(DoubleSD1ToneCoefficients) ATK::SD1ToneCoefficients<double>;

%template(FloatSD1ToneFilter) ATK::IIRFilter<ATK::SD1ToneCoefficients<float> >;
%template(DoubleSD1ToneFilter) ATK::IIRFilter<ATK::SD1ToneCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::SD1ToneCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SD1ToneCoefficients<double> >, double);

%template(FloatTS9ToneCoefficients) ATK::TS9ToneCoefficients<float>;
%template(DoubleTS9ToneCoefficients) ATK::TS9ToneCoefficients<double>;

%template(FloatTS9ToneFilter) ATK::IIRFilter<ATK::TS9ToneCoefficients<float> >;
%template(DoubleTS9ToneFilter) ATK::IIRFilter<ATK::TS9ToneCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::TS9ToneCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::TS9ToneCoefficients<double> >, double);
