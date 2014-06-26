
%{
#include <ATK/Distortion/SimpleOverdriveFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class SimpleOverdriveFilter: public BaseFilter
  {
  public:
    SimpleOverdriveFilter(int nb_channels = 1);
    ~SimpleOverdriveFilter();
  };
}

%template(FloatSimpleOverdriveFilter) ATK::SimpleOverdriveFilter<float>;
%template(DoubleSimpleOverdriveFilter) ATK::SimpleOverdriveFilter<double>;
