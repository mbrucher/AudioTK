
%{
#include <ATK/EQ/ToneStackFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ToneStackCoefficients: public BaseFilter
  {
  public:
    ~ToneStackCoefficients();
    
    void set_low(DataType low);
    DataType get_low() const;

    void set_middle(DataType middle);
    DataType get_middle() const;

    void set_high(DataType high);
    DataType get_high() const;

    /// Builds a Bassman stack equivalent filter (bass, Fender)
    static IIRFilter<ToneStackCoefficients<DataType> >&& buildBassmanStack();
    /// Builds a JCM800 stack equivalent filter (guitar, Marshall)
    static IIRFilter<ToneStackCoefficients<DataType> >&& buildJCM800Stack();
  };
}

%template(FloatToneStackCoefficients) ATK::ToneStackCoefficients<float>;
%template(DoubleToneStackCoefficients) ATK::ToneStackCoefficients<double>;

%template(FloatToneStackFilter) ATK::IIRFilter<ATK::ToneStackCoefficients<float> >;
%template(DoubleToneStackFilter) ATK::IIRFilter<ATK::ToneStackCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackCoefficients<double> >, double);

%define PedalToneStackExtend(name, T)
%extend name {
  %newobject buildBassmanStack;
  %newobject buildJCM800Stack;
  static ATK::IIRFilter<ATK::ToneStackCoefficients<T> >* buildBassmanStack()
  {
    return new ATK::IIRFilter<ATK::ToneStackCoefficients<T> >(ATK::IIRFilter<ATK::ToneStackCoefficients<T> >::buildBassmanStack());
  }
  static ATK::IIRFilter<ATK::ToneStackCoefficients<T> >* buildJCM800Stack()
  {
    return new ATK::IIRFilter<ATK::ToneStackCoefficients<T> >(ATK::IIRFilter<ATK::ToneStackCoefficients<T> >::buildJCM800Stack());
  }
}
%enddef

PedalToneStackExtend(ATK::IIRFilter<ATK::ToneStackCoefficients<float> >, float);
PedalToneStackExtend(ATK::IIRFilter<ATK::ToneStackCoefficients<double> >, double);
