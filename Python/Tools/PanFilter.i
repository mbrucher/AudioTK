
%{
#include <ATK/Tools/PanFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class PanFilter: public BaseFilter
  {
  public:
    PanFilter();
    ~PanFilter();
  };
}

%template(Int16PanFilter) ATK::PanFilter<std::int16_t>;
%template(Int32PanFilter) ATK::PanFilter<std::int32_t>;
%template(Int64PanFilter) ATK::PanFilter<std::int64_t>;
%template(FloatPanFilter) ATK::PanFilter<float>;
%template(DoublePanFilter) ATK::PanFilter<double>;
