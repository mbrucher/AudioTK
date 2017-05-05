
%{
#include <ATK/Distortion/SimpleOverdriveFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class SimpleOverdriveFilter: public BaseFilter
  {
  public:
    SimpleOverdriveFilter();
    ~SimpleOverdriveFilter();
  };
}

%template(FloatSimpleOverdriveFilter) ATK::SimpleOverdriveFilter<float>;
%template(DoubleSimpleOverdriveFilter) ATK::SimpleOverdriveFilter<double>;
