
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

%template(Int16OneMinusFilter) ATK::OneMinusFilter<int16_t>;
%template(Int32OneMinusFilter) ATK::OneMinusFilter<int32_t>;
%template(Int64OneMinusFilter) ATK::OneMinusFilter<int64_t>;
%template(FloatOneMinusFilter) ATK::OneMinusFilter<float>;
%template(DoubleOneMinusFilter) ATK::OneMinusFilter<double>;
