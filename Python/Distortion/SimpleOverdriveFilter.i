
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

  template<class DataType>
  class BackwardSimpleOverdriveFilter: public BaseFilter
  {
  public:
    BackwardSimpleOverdriveFilter();
    ~BackwardSimpleOverdriveFilter();
  };

  template<class DataType>
  class ForwardSimpleOverdriveFilter: public BaseFilter
  {
  public:
    ForwardSimpleOverdriveFilter();
    ~ForwardSimpleOverdriveFilter();
  };
}

%template(FloatSimpleOverdriveFilter) ATK::SimpleOverdriveFilter<float>;
%template(DoubleSimpleOverdriveFilter) ATK::SimpleOverdriveFilter<double>;
%template(FloatBackwardSimpleOverdriveFilter) ATK::BackwardSimpleOverdriveFilter<float>;
%template(DoubleBackwardSimpleOverdriveFilter) ATK::BackwardSimpleOverdriveFilter<double>;
%template(FloatForwardSimpleOverdriveFilter) ATK::ForwardSimpleOverdriveFilter<float>;
%template(DoubleForwardSimpleOverdriveFilter) ATK::ForwardSimpleOverdriveFilter<double>;
