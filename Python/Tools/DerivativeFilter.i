
%{
#include <ATK/Tools/DerivativeFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class DerivativeFilter: public BaseFilter
  {
  public:
    DerivativeFilter(int nb_channels = 1);
    ~DerivativeFilter();
  };
}

%template(Int16DerivativeFilter) ATK::DerivativeFilter<int16_t>;
%template(Int32DerivativeFilter) ATK::DerivativeFilter<int32_t>;
%template(Int64DerivativeFilter) ATK::DerivativeFilter<int64_t>;
%template(FloatDerivativeFilter) ATK::DerivativeFilter<float>;
%template(DoubleDerivativeFilter) ATK::DerivativeFilter<double>;
