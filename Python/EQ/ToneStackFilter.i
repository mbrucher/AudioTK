
%{
#include <ATK/EQ/ToneStackFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ToneStackFilterCoefficients: public BaseFilter
  {
  public:
    ToneStackFilterCoefficients();
    ~ToneStackFilterCoefficients();
    
    void set_low(DataType low);
    DataType get_low() const;

    void set_middle(DataType middle);
    DataType get_middle() const;

    void set_high(DataType high);
    DataType get_high() const;
  };
}

%template(FloatToneStackCoefficients) ATK::ToneStackFilterCoefficients<float>;
%template(DoubleToneStackCoefficients) ATK::ToneStackFilterCoefficients<double>;

%template(FloatToneStackFilter) ATK::IIRFilter<ATK::ToneStackFilterCoefficients<float> >;
%template(DoubleToneStackFilter) ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> >, double);
