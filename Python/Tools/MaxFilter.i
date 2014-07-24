
%{
#include <ATK/Tools/MaxFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class MaxFilter: public BaseFilter
  {
  public:
    MaxFilter();
    ~MaxFilter();
  };
}

%template(Int16MaxFilter) ATK::MaxFilter<std::int16_t>;
%template(Int32MaxFilter) ATK::MaxFilter<std::int32_t>;
%template(Int64MaxFilter) ATK::MaxFilter<std::int64_t>;
%template(FloatMaxFilter) ATK::MaxFilter<float>;
%template(DoubleMaxFilter) ATK::MaxFilter<double>;
