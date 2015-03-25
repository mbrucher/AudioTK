
%{
#include <ATK/Tools/DerivativeFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class DerivativeFilter: public BaseFilter
  {
  public:
    DerivativeFilter();
    ~DerivativeFilter();
  };
}

%template(Int16DerivativeFilter) ATK::DerivativeFilter<std::int16_t>;
%template(Int32DerivativeFilter) ATK::DerivativeFilter<std::int32_t>;
%template(Int64DerivativeFilter) ATK::DerivativeFilter<std::int64_t>;
%template(FloatDerivativeFilter) ATK::DerivativeFilter<float>;
%template(DoubleDerivativeFilter) ATK::DerivativeFilter<double>;
