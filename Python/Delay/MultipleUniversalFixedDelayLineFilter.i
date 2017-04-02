
%{
#include <ATK/Delay/MultipleUniversalFixedDelayLineFilter.h>
%}

namespace ATK
{
  template<class DataType, unsigned int nb_channels>
  class MultipleUniversalFixedDelayLineFilter: public BaseFilter
  {
  public:
    MultipleUniversalFixedDelayLineFilter(std::size_t max_delay);
    ~MultipleUniversalFixedDelayLineFilter();

    /// Set the initial delay from a channel
    void set_delay(unsigned int channel, std::size_t delay);
    std::size_t get_delay(unsigned int channel) const;

    void set_blend(unsigned int channel, double blend);
    double get_blend(unsigned int channel) const;

    /// Set the feedback from channel to channel
    void set_feedback(unsigned int from_channel, unsigned int to_channel, double feedback);
    double get_feedback(unsigned int from_channel, unsigned int to_channel) const;

    /// Set the feedforward from channel to channel
    void set_feedforward(unsigned int from_channel, unsigned int to_channel, double feedforward);
    double get_feedforward(unsigned int from_channel, unsigned int to_channel) const;
  };
}

%template(FloatStereoUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<float, 2>;
%template(DoubleStereoUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<double, 2>;
%template(ComplexFloatStereoUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<std::complex<float>, 2>;
%template(ComplexDoubleStereoUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<std::complex<double>, 2>;

%template(FloatQuadrupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<float, 4>;
%template(DoubleQuadrupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<double, 4>;
%template(ComplexFloatQuadrupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<std::complex<float>, 4>;
%template(ComplexDoubleQuadrupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<std::complex<double>, 4>;

%template(FloatOctupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<float, 8>;
%template(DoubleOctupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<double, 8>;
%template(ComplexFloatOctupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<std::complex<float>, 8>;
%template(ComplexDoubleOctupleUniversalFixedDelayLineFilter) ATK::MultipleUniversalFixedDelayLineFilter<std::complex<double>, 8>;
