
%{
#include <ATK/Tools/OneMinusFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class OneMinusFilter: public BaseFilter
  {
  public:
    OneMinusFilter(int nb_channels = 1);
    ~OneMinusFilter();
  };
}

%template(FloatOneMinusFilter) ATK::OneMinusFilter<float>;
%template(DoubleOneMinusFilter) ATK::OneMinusFilter<double>;
%template(ComplexFloatOneMinusFilter) ATK::OneMinusFilter<std::complex<float>>;
%template(ComplexDoubleOneMinusFilter) ATK::OneMinusFilter<std::complex<double>>;
