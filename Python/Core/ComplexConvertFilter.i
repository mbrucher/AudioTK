
%{
#include <cstdint>
#include <ATK/Core/ComplexConvertFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ComplexToRealFilter: public BaseFilter
  {
  public:
    ComplexToRealFilter(int channels = 1);
    ~ComplexToRealFilter();
  };
}

%template(FloatComplexToRealFilter) ATK::ComplexToRealFilter<float>;
%template(DoubleComplexToRealFilter) ATK::ComplexToRealFilter<double>;

namespace ATK
{
  template<class DataType>
  class RealToComplexFilter: public BaseFilter
  {
  public:
    RealToComplexFilter(int channels = 1);
    ~RealToComplexFilter();
  };
}

%template(FloatRealToComplexFilter) ATK::RealToComplexFilter<float>;
%template(DoubleRealToComplexFilter) ATK::RealToComplexFilter<double>;
