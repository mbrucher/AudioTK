
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

  ATKProperty(UniversalVariableDelayLineFilter<float>, blend, get_blend, set_blend);
  ATKProperty(UniversalVariableDelayLineFilter<float>, feedback, get_feedback, set_feedback);
  ATKProperty(UniversalVariableDelayLineFilter<float>, feedforward, get_feedforward, set_feedforward);
  ATKProperty(UniversalVariableDelayLineFilter<double>, blend, get_blend, set_blend);
  ATKProperty(UniversalVariableDelayLineFilter<double>, feedback, get_feedback, set_feedback);
  ATKProperty(UniversalVariableDelayLineFilter<double>, feedforward, get_feedforward, set_feedforward);
}

%template(FloatUniversalVariableDelayLineFilter) ATK::UniversalVariableDelayLineFilter<float>;
%template(DoubleUniversalVariableDelayLineFilter) ATK::UniversalVariableDelayLineFilter<double>;
