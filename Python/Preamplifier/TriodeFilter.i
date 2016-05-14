
%{
#include <ATK/Preamplifier/EnhancedKorenTriodeFunction.h>
#include <ATK/Preamplifier/KorenTriodeFunction.h>
#include <ATK/Preamplifier/TriodeFilter.h>
%}

namespace ATK
{
  template<typename DataType>
  class KorenTriodeFunction
  {
  };

  template<typename DataType>
  class EnhancedKorenTriodeFunction
  {
  };

  template<typename DataType, typename TubeFunction>
  class TriodeFilter: public BaseFilter
  {
  public:
    ~TriodeFilter();
  };
}

%template(FloatKorenTriodeFilter) ATK::TriodeFilter<float, ATK::KorenTriodeFunction<float> >;
%template(DoubleKorenTriodeFilter) ATK::TriodeFilter<double, ATK::KorenTriodeFunction<double>>;
%template(FloatEnhancedKorenTriodeFilter) ATK::TriodeFilter<float, ATK::EnhancedKorenTriodeFunction<float> >;
%template(DoubleEnhancedKorenTriodeFilter) ATK::TriodeFilter<double, ATK::EnhancedKorenTriodeFunction<double>>;

%define TubeExtend(name, T, T2)
%extend name<T, T2<T> > {
  %newobject build_standard_filter;
  static name<T, T2<T> >* build_standard_filter()
  {
    return new name<T, T2<T> >(name<T, T2<T> >::build_standard_filter());
  }
}
%enddef

TubeExtend(ATK::TriodeFilter,float, ATK::KorenTriodeFunction);
TubeExtend(ATK::TriodeFilter,double, ATK::KorenTriodeFunction);
TubeExtend(ATK::TriodeFilter,float, ATK::EnhancedKorenTriodeFunction);
TubeExtend(ATK::TriodeFilter,double, ATK::EnhancedKorenTriodeFunction);
