
%{
#include <ATK/Preamplifier/EnhancedKorenTriodeFunction.h>
#include <ATK/Preamplifier/KorenTriodeFunction.h>
#include <ATK/Preamplifier/LeachTriodeFunction.h>
#include <ATK/Preamplifier/MunroPiazzaTriodeFunction.h>
#include <ATK/Preamplifier/Triode2Filter.h>
%}

namespace ATK
{
  template<typename DataType, typename TubeFunction>
  class Triode2Filter: public BaseFilter
  {
  public:
    ~Triode2Filter();
  };
}

%template(FloatKorenTriode2Filter) ATK::Triode2Filter<float, ATK::KorenTriodeFunction<float> >;
%template(DoubleKorenTriode2Filter) ATK::Triode2Filter<double, ATK::KorenTriodeFunction<double>>;
%template(FloatEnhancedKorenTriode2Filter) ATK::Triode2Filter<float, ATK::EnhancedKorenTriodeFunction<float> >;
%template(DoubleEnhancedKorenTriode2Filter) ATK::Triode2Filter<double, ATK::EnhancedKorenTriodeFunction<double>>;
%template(FloatLeachTriode2Filter) ATK::Triode2Filter<float, ATK::LeachTriodeFunction<float> >;
%template(DoubleLeachTriode2Filter) ATK::Triode2Filter<double, ATK::LeachTriodeFunction<double>>;
%template(FloatMunroPiazzaTriode2Filter) ATK::Triode2Filter<float, ATK::MunroPiazzaTriodeFunction<float> >;
%template(DoubleMunroPiazzaTriode2Filter) ATK::Triode2Filter<double, ATK::MunroPiazzaTriodeFunction<double>>;

%define TubeExtend(name, T, T2)
%extend name<T, T2<T> > {
  %newobject build_standard_filter;
  static name<T, T2<T> >* build_standard_filter()
  {
    return new name<T, T2<T> >(name<T, T2<T> >::build_standard_filter());
  }
}
%enddef

TubeExtend(ATK::Triode2Filter,float, ATK::KorenTriodeFunction);
TubeExtend(ATK::Triode2Filter,double, ATK::KorenTriodeFunction);
TubeExtend(ATK::Triode2Filter,float, ATK::EnhancedKorenTriodeFunction);
TubeExtend(ATK::Triode2Filter,double, ATK::EnhancedKorenTriodeFunction);
TubeExtend(ATK::Triode2Filter,float, ATK::LeachTriodeFunction);
TubeExtend(ATK::Triode2Filter,double, ATK::LeachTriodeFunction);
TubeExtend(ATK::Triode2Filter,float, ATK::MunroPiazzaTriodeFunction);
TubeExtend(ATK::Triode2Filter,double, ATK::MunroPiazzaTriodeFunction);
