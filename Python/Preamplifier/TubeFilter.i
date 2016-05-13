
%{
#include <ATK/Preamplifier/TubeFilter.h>
%}

namespace ATK
{
  template<typename DataType>
  class BasicTubeFunction
  {
  };

  template<typename DataType, typename TubeFunction>
  class TubeFilter: public BaseFilter
  {
  public:
    ~TubeFilter();
  };
}

%template(FloatTubeFilter) ATK::TubeFilter<float, ATK::BasicTubeFunction<float> >;
%template(DoubleTubeFilter) ATK::TubeFilter<double, ATK::BasicTubeFunction<double>>;

%define TubeExtend(name, T, T2)
%extend name<T, T2<T> > {
  %newobject build_standard_filter;
  static name<T, T2<T> >* build_standard_filter()
  {
    return new name<T, T2<T> >(name<T, T2<T> >::build_standard_filter());
  }
}
%enddef

TubeExtend(ATK::TubeFilter,float, ATK::BasicTubeFunction);
TubeExtend(ATK::TubeFilter,double, ATK::BasicTubeFunction);
