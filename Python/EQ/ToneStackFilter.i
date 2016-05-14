
%{
#include <ATK/EQ/ToneStackFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ToneStackFilterCoefficients: public BaseFilter
  {
  public:
    ~ToneStackFilterCoefficients();
    
    void set_low(DataType low);
    DataType get_low() const;

    void set_middle(DataType middle);
    DataType get_middle() const;

    void set_high(DataType high);
    DataType get_high() const;

    /// Builds a Bassman stack equivalent filter (bass, Fender)
    static IIRFilter<ToneStackFilterCoefficients<DataType> >&& buildBassmanStack();
    /// Builds a JCM800 stack equivalent filter (guitar, Marshall)
    static IIRFilter<ToneStackFilterCoefficients<DataType> >&& buildJCM800Stack();
  };
}

%template(FloatToneStackCoefficients) ATK::ToneStackFilterCoefficients<float>;
%template(DoubleToneStackCoefficients) ATK::ToneStackFilterCoefficients<double>;

%template(FloatToneStackFilter) ATK::IIRFilter<ATK::ToneStackFilterCoefficients<float> >;
%template(DoubleToneStackFilter) ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> >, double);

%define ToneStackExtend(name, T)
%extend name {
  %newobject buildBassmanStack;
  %newobject buildJCM800Stack;
  static ATK::IIRFilter<ATK::ToneStackFilterCoefficients<T> >* buildBassmanStack()
  {
    return new ATK::IIRFilter<ATK::ToneStackFilterCoefficients<T> >(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<T> >::buildBassmanStack());
  }
  static ATK::IIRFilter<ATK::ToneStackFilterCoefficients<T> >* buildJCM800Stack()
  {
    return new ATK::IIRFilter<ATK::ToneStackFilterCoefficients<T> >(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<T> >::buildJCM800Stack());
  }
}
%enddef

ToneStackExtend(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<float> >, float);
ToneStackExtend(ATK::IIRFilter<ATK::ToneStackFilterCoefficients<double> >, double);
