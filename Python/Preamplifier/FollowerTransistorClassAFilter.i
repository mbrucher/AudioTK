
%{
#include <ATK/Preamplifier/FollowerTransistorClassAFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class FollowerTransistorClassAFilter: public BaseFilter
  {
  public:
    ~FollowerTransistorClassAFilter();
  };
}

%template(FloatFollowerTransistorClassAFilter) ATK::FollowerTransistorClassAFilter<float>;
%template(DoubleFollowerTransistorClassAFilter) ATK::FollowerTransistorClassAFilter<double>;

PreampExtendSimple(ATK::FollowerTransistorClassAFilter, float);
PreampExtendSimple(ATK::FollowerTransistorClassAFilter, double);
