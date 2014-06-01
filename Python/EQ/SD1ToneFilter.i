
%{
#include <ATK/EQ/SD1ToneFilter.h>
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
}

%template(FloatSD1ToneCoefficients) ATK::SD1ToneCoefficients<float>;
%template(DoubleSD1ToneCoefficients) ATK::SD1ToneCoefficients<double>;

%template(FloatSD1ToneFilter) ATK::IIRFilter<ATK::SD1ToneCoefficients<float> >;
%template(DoubleSD1ToneFilter) ATK::IIRFilter<ATK::SD1ToneCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::SD1ToneCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SD1ToneCoefficients<double> >, double);
