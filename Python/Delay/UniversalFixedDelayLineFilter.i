
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

  ATKProperty(UniversalFixedDelayLineFilter<float>, delay, get_delay, set_delay);
  ATKProperty(UniversalFixedDelayLineFilter<float>, blend, get_blend, set_blend);
  ATKProperty(UniversalFixedDelayLineFilter<float>, feedback, get_feedback, set_feedback);
  ATKProperty(UniversalFixedDelayLineFilter<float>, feedforward, get_feedforward, set_feedforward);
  ATKProperty(UniversalFixedDelayLineFilter<double>, delay, get_delay, set_delay);
  ATKProperty(UniversalFixedDelayLineFilter<double>, blend, get_blend, set_blend);
  ATKProperty(UniversalFixedDelayLineFilter<double>, feedback, get_feedback, set_feedback);
  ATKProperty(UniversalFixedDelayLineFilter<double>, feedforward, get_feedforward, set_feedforward);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<float>>, delay, get_delay, set_delay);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<float>>, blend, get_blend, set_blend);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<float>>, feedback, get_feedback, set_feedback);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<float>>, feedforward, get_feedforward, set_feedforward);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<double>>, delay, get_delay, set_delay);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<double>>, blend, get_blend, set_blend);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<double>>, feedback, get_feedback, set_feedback);
  ATKProperty(UniversalFixedDelayLineFilter<std::complex<double>>, feedforward, get_feedforward, set_feedforward);
}

%template(FloatUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<float>;
%template(DoubleUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<double>;
%template(ComplexFloatUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<std::complex<float> >;
%template(ComplexDoubleUniversalFixedDelayLineFilter) ATK::UniversalFixedDelayLineFilter<std::complex<double> >;
