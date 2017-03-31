
%{
#include <ATK/Tools/MSFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class MiddleSideFilter: public BaseFilter
  {
  public:
    MiddleSideFilter();
    ~MiddleSideFilter();
  };
}

%template(Int16MiddleSideFilter) ATK::MiddleSideFilter<std::int16_t>;
%template(Int32MiddleSideFilter) ATK::MiddleSideFilter<std::int32_t>;
%template(Int64MiddleSideFilter) ATK::MiddleSideFilter<std::int64_t>;
%template(FloatMiddleSideFilter) ATK::MiddleSideFilter<float>;
%template(DoubleMiddleSideFilter) ATK::MiddleSideFilter<double>;
%template(ComplexFloatMiddleSideFilter) ATK::MiddleSideFilter<std::complex<float>>;
%template(ComplexDoubleMiddleSideFilter) ATK::MiddleSideFilter<std::complex<double>>;
