
%{
#include <ATK/Delay/UniversalFixedDelayLineFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class UniversalFixedDelayLineFilter: public BaseFilter
  {
  public:
    UniversalFixedDelayLineFilter(int max_delay);
    ~UniversalFixedDelayLineFilter();
    
    void set_delay(int delay);
    int get_delay() const;

    void set_blend(DataType blend);
    DataType get_blend() const;

    void set_feedback(DataType feedback);
    DataType get_feedback() const;

    void set_feedforward(DataType feedforward);
    DataType get_feedforward() const;
  };
}

%template(FloatUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<float>;
%template(DoubleUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<double>;
%template(ComplexFloatUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<std::complex<float>>;
%template(ComplexDoubleUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<std::complex<double>>;
