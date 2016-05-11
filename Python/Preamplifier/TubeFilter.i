
%{
#include <ATK/Preamplifier/TubeFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class TubeFilter: public BaseFilter
  {
  public:
    ~TubeFilter();
  };
}

%template(FloatTubeFilter) ATK::TubeFilter<float>;
%template(DoubleTubeFilter) ATK::TubeFilter<double>;

%define TubeExtend(name, T)
%extend name {
  %newobject build_standard_filter;
  static ATK::TubeFilter<T>* build_standard_filter()
  {
    return new ATK::TubeFilter<T>(ATK::TubeFilter<T>::build_standard_filter());
  }
}
%enddef

TubeExtend(ATK::TubeFilter<float>, float);
TubeExtend(ATK::TubeFilter<double>, double);
