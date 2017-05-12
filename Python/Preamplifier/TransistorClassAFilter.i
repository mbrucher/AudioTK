
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

%define TransistorClassAExtend(T)
%extend ATK::TransistorClassAFilter<T> {
  %newobject build_standard_filter;
  static ATK::TransistorClassAFilter<T>* build_standard_filter(T Rp = 1e3, T Rg1 = 15e3, T Rg2 = 1.5e3, T Ro = 22e3, T Rk = 100,
    T Vbias = 5, T Cg = 3.3e-6, T Co = 1e-6, T Ck = 160e-6, ATK::TransistorFunction<T>* function=nullptr)
  {
    std::unique_ptr<ATK::TransistorFunction<T> > actual_function;
    if(function == nullptr)
    {
      actual_function.reset(new ATK::TransistorFunction<T>(ATK::TransistorFunction<T>::build_standard_function()));
      function = actual_function.get();
    }
    return new ATK::TransistorClassAFilter<T>(ATK::TransistorClassAFilter<T>::build_standard_filter(Rp, Rg1, Rg2, Ro, Rk, Vbias, Cg, Co, Ck, *function));
  }
}
%enddef

%template(FloatTransistorClassAFilter) ATK::TransistorClassAFilter<float>;
%template(DoubleTransistorClassAFilter) ATK::TransistorClassAFilter<double>;

TransistorClassAExtend(float)
TransistorClassAExtend(double)
