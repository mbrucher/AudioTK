
%{
#include <ATK/Preamplifier/FollowerTransistorClassAFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class FollowerTransistorClassAFilter: public BaseFilter
  {
  public:
    ~FollowerTransistorClassAFilter();
  };
}

%define FollowerTransistorClassAExtend(T)
%extend ATK::FollowerTransistorClassAFilter<T> {
  %newobject build_standard_filter;
  static ATK::FollowerTransistorClassAFilter<T>* build_standard_filter(T Rp=10e3, T Rg1=220e3, T Rg2=27e3, T Ro=8, T Rk1=1.5e3, T Rk2=1e3, T Vbias=10, T Cg=0.47e-6, T Co=4.7e-6, T Ck=33e-6,
    ATK::TransistorFunction<T>* function1=nullptr, ATK::TransistorFunction<T>* function2=nullptr)
  {
    std::unique_ptr<ATK::TransistorFunction<T> > actual_function1;
    if(function1 == nullptr)
    {
      actual_function1.reset(new ATK::TransistorFunction<T>(ATK::TransistorFunction<T>::build_standard_function()));
      function1 = actual_function1.get();
    }
    std::unique_ptr<ATK::TransistorFunction<T> > actual_function2;
    if(function2 == nullptr)
    {
      actual_function2.reset(new ATK::TransistorFunction<T>(ATK::TransistorFunction<T>::build_standard_function()));
      function2 = actual_function2.get();
    }
    return new ATK::FollowerTransistorClassAFilter<T>(ATK::FollowerTransistorClassAFilter<T>::build_standard_filter(Rp, Rg1, Rg2, Ro, Rk1, Rk2, Vbias, Cg, Co, Ck, *function1, *function2));
  }
}
%enddef

%template(FloatFollowerTransistorClassAFilter) ATK::FollowerTransistorClassAFilter<float>;
%template(DoubleFollowerTransistorClassAFilter) ATK::FollowerTransistorClassAFilter<double>;

FollowerTransistorClassAExtend(float)
FollowerTransistorClassAExtend(double)
