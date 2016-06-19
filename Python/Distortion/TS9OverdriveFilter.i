
%{
#include <ATK/Distortion/TS9OverdriveFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class TS9OverdriveFilter: public BaseFilter
  {
  public:
    TS9OverdriveFilter();
    ~TS9OverdriveFilter();
    void set_drive(DataType drive);
  };
}

%template(FloatTS9OverdriveFilter) ATK::TS9OverdriveFilter<float>;
%template(DoubleTS9OverdriveFilter) ATK::TS9OverdriveFilter<double>;
