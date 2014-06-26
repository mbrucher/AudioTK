
%{
#include <ATK/Distortion/SD1OverdriveFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class SD1OverdriveFilter: public BaseFilter
  {
  public:
    SD1OverdriveFilter(int nb_channels = 1);
    ~SD1OverdriveFilter();
    void set_drive(DataType drive);
  };
}

%template(FloatSD1OverdriveFilter) ATK::SD1OverdriveFilter<float>;
%template(DoubleSD1OverdriveFilter) ATK::SD1OverdriveFilter<double>;
