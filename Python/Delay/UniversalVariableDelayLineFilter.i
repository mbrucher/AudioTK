
%{
#include <ATK/Delay/UniversalVariableDelayLineFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class UniversalVariableDelayLineFilter: public BaseFilter
  {
  public:
    UniversalVariableDelayLineFilter(int max_delay);
    ~UniversalVariableDelayLineFilter();

    void set_blend(DataType blend);
    DataType get_blend() const;

    void set_feedback(DataType feedback);
    DataType get_feedback() const;

    void set_feedforward(DataType feedforward);
    DataType get_feedforward() const;
  };
}

%template(FloatUniversalVariableDelayLineFilter) ATK::UniversalVariableDelayLineFilter<float>;
%template(DoubleUniversalVariableDelayLineFilter) ATK::UniversalVariableDelayLineFilter<double>;
