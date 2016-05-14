
%{
#include <ATK/Preamplifier/TransistorClassAFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class TransistorClassAFilter: public BaseFilter
  {
  public:
    ~TransistorClassAFilter();
  };
}

%template(FloatTransistorClassAFilter) ATK::TransistorClassAFilter<float>;
%template(DoubleTransistorClassAFilter) ATK::TransistorClassAFilter<double>;

%define ClassAExtend(name, T)
%extend name {
  %newobject build_standard_filter;
  static ATK::TransistorClassAFilter<T>* build_standard_filter()
  {
    return new ATK::TransistorClassAFilter<T>(ATK::TransistorClassAFilter<T>::build_standard_filter());
  }
}
%enddef

ClassAExtend(ATK::TransistorClassAFilter<float>, float);
ClassAExtend(ATK::TransistorClassAFilter<double>, double);
