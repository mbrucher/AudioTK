
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

  ATKProperty(FixedDelayLineFilter<float>, delay, get_delay, set_delay);
  ATKProperty(FixedDelayLineFilter<double>, delay, get_delay, set_delay);
  ATKProperty(FixedDelayLineFilter<std::complex<float>>, delay, get_delay, set_delay);
  ATKProperty(FixedDelayLineFilter<std::complex<double>>, delay, get_delay, set_delay);
}

%template(FloatFixedDelayLineFilter) ATK::FixedDelayLineFilter<float>;
%template(DoubleFixedDelayLineFilter) ATK::FixedDelayLineFilter<double>;
%template(ComplexFloatFixedDelayLineFilter) ATK::FixedDelayLineFilter<std::complex<float> >;
%template(ComplexDoubleFixedDelayLineFilter) ATK::FixedDelayLineFilter<std::complex<double> >;
