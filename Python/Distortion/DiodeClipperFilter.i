
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

  template<class DataType>
  class BackwardDiodeClipperFilter: public BaseFilter
  {
  public:
    BackwardDiodeClipperFilter();
    ~BackwardDiodeClipperFilter();
  };

  template<class DataType>
  class ForwardDiodeClipperFilter: public BaseFilter
  {
  public:
    ForwardDiodeClipperFilter();
    ~ForwardDiodeClipperFilter();
  };
}

%template(FloatDiodeClipperFilter) ATK::DiodeClipperFilter<float>;
%template(DoubleDiodeClipperFilter) ATK::DiodeClipperFilter<double>;
%template(FloatBackwardDiodeClipperFilter) ATK::BackwardDiodeClipperFilter<float>;
%template(DoubleBackwardDiodeClipperFilter) ATK::BackwardDiodeClipperFilter<double>;
%template(FloatForwardDiodeClipperFilter) ATK::ForwardDiodeClipperFilter<float>;
%template(DoubleForwardDiodeClipperFilter) ATK::ForwardDiodeClipperFilter<double>;
