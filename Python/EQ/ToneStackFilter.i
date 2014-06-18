
%{
#include <ATK/EQ/ToneStackFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ToneStackFilter: public BaseFilter
  {
  public:
    ToneStackFilter();
    ~ToneStackFilter();
    
    void set_low(DataType low);
    DataType get_low() const;

    void set_middle(DataType middle);
    DataType get_middle() const;

    void set_high(DataType high);
    DataType get_high() const;
  };
}

%template(FloatSD1ToneCoefficients) ATK::ToneStackFilter<float>;
%template(DoubleSD1ToneCoefficients) ATK::ToneStackFilter<double>;

%template(FloatSD1ToneFilter) ATK::IIRFilter<ATK::ToneStackFilter<float> >;
%template(DoubleSD1ToneFilter) ATK::IIRFilter<ATK::ToneStackFilter<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackFilter<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackFilter<double> >, double);
