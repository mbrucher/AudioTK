
%{
#include <ATK/Distortion/SVFSD1OverdriveFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class SVFSD1OverdriveFilter: public BaseFilter
  {
  public:
    SVFSD1OverdriveFilter();
    ~SVFSD1OverdriveFilter();
    void set_drive(DataType drive);
  };
}

%template(FloatSVFSD1OverdriveFilter) ATK::SVFSD1OverdriveFilter<float>;
%template(DoubleSVFSD1OverdriveFilter) ATK::SVFSD1OverdriveFilter<double>;
