
%{
#include <ATK/Delay/VariableDelayLineFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class VariableDelayLineFilter: public BaseFilter
  {
  public:
    VariableDelayLineFilter(int max_delay);
    ~VariableDelayLineFilter();
  };
}

%template(FloatVariableDelayLineFilter) ATK::VariableDelayLineFilter<float>;
%template(DoubleVariableDelayLineFilter) ATK::VariableDelayLineFilter<double>;
