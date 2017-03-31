
%{
#include <ATK/Delay/StereoUniversalFixedDelayLineFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class StereoUniversalFixedDelayLineFilter: public BaseFilter
  {
  public:
    StereoUniversalFixedDelayLineFilter(int max_delay);
    ~StereoUniversalFixedDelayLineFilter();

    /// Set the initial delay from channel 1
    void set_delay_ch1(int delay);
    int get_delay_ch1() const;
    /// Set the initial delay from channel 2
    void set_delay_ch2(int delay);
    int get_delay_ch2() const;

    void set_blend_ch1(DataType blend);
    DataType get_blend_ch1() const;
    void set_blend_ch2(DataType blend);
    DataType get_blend_ch2() const;

    /// Set the feedback from channel 1 to channel 1
    void set_feedback_ch1_ch1(DataType feedback);
    DataType get_feedback_ch1_ch1() const;
    /// Set the feedback from channel 1 to channel 2
    void set_feedback_ch1_ch2(DataType feedback);
    DataType get_feedback_ch1_ch2() const;
    /// Set the feedback from channel 2 to channel 1
    void set_feedback_ch2_ch1(DataType feedback);
    DataType get_feedback_ch2_ch1() const;
    /// Set the feedback from channel 2 to channel 2
    void set_feedback_ch2_ch2(DataType feedback);
    DataType get_feedback_ch2_ch2() const;

    void set_feedforward_ch1_ch1(DataType feedforward);
    DataType get_feedforward_ch1_ch1() const;
    void set_feedforward_ch1_ch2(DataType feedforward);
    DataType get_feedforward_ch1_ch2() const;
    void set_feedforward_ch2_ch1(DataType feedforward);
    DataType get_feedforward_ch2_ch1() const;
    void set_feedforward_ch2_ch2(DataType feedforward);
    DataType get_feedforward_ch2_ch2() const;
  };
}

%template(FloatStereoUniversalFixedDelayLineFilter) ATK::StereoUniversalFixedDelayLineFilter<float>;
%template(DoubleStereoUniversalFixedDelayLineFilter) ATK::StereoUniversalFixedDelayLineFilter<double>;
%template(ComplexFloatStereoUniversalFixedDelayLineFilter) ATK::StereoUniversalFixedDelayLineFilter<std::complex<float>>;
%template(ComplexDoubleStereoUniversalFixedDelayLineFilter) ATK::StereoUniversalFixedDelayLineFilter<std::complex<double>>;
