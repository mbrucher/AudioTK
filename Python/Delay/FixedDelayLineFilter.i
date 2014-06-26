
%{
#include <ATK/Delay/FixedDelayLineFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class FixedDelayLineFilter: public BaseFilter
  {
  public:
    FixedDelayLineFilter(int max_delay);
    ~FixedDelayLineFilter();
    
    void set_delay(int delay);
    int get_delay() const;
  };
}

%template(FloatFixedDelayLineFilter) ATK::FixedDelayLineFilter<float>;
%template(DoubleFixedDelayLineFilter) ATK::FixedDelayLineFilter<double>;
