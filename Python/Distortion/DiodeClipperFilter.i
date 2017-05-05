
%{
#include <ATK/Distortion/DiodeClipperFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class DiodeClipperFilter: public BaseFilter
  {
  public:
    DiodeClipperFilter();
    ~DiodeClipperFilter();
  };
}

%template(FloatDiodeClipperFilter) ATK::DiodeClipperFilter<float>;
%template(DoubleDiodeClipperFilter) ATK::DiodeClipperFilter<double>;
