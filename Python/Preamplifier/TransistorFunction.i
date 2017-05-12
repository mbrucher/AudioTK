
%{
#include <ATK/Preamplifier/TransistorFunction.h>
%}

namespace ATK
{
  template <typename DataType>
  class TransistorFunction
  {
  public:
    ~TransistorFunction();
  };
}

%define TransistorExtend(T)
%extend ATK::TransistorFunction<T> {
  %newobject build_standard_function;
  static ATK::TransistorFunction<T>* build_standard_function(T Is=1e-12, T Vt=26e-3, T Br=1, T Bf=100)
  {
    return new ATK::TransistorFunction<T>(ATK::TransistorFunction<T>::build_standard_function(Is, Vt, Br, Bf));
  }
}
%enddef

%template(FloatTransistorFunction) ATK::TransistorFunction<float>;
%template(DoubleTransistorFunction) ATK::TransistorFunction<double>;

TransistorExtend(float)
TransistorExtend(double)
