
%{
#include <ATK/Delay/HadamardFeedbackDelayNetworkFilter.h>
%}

namespace ATK
{
  template<class DataType, unsigned int nb_channels>
  class HadamardFeedbackDelayNetworkFilter: public BaseFilter
  {
  public:
    HadamardFeedbackDelayNetworkFilter(std::size_t max_delay);
    ~HadamardFeedbackDelayNetworkFilter();

    /// Set the initial delay from a channel
    void set_delay(unsigned int channel, std::size_t delay);
    std::size_t get_delay(unsigned int channel) const;

    void set_ingain(unsigned int channel, DataType ingain);
    /// Gets the input gain of a channel
    DataType get_ingain(unsigned int channel) const;

    /// Sets the feedback of a channel
    void set_feedback(unsigned int channel, DataType feedback);
    /// Gets the feedback of a channel
    DataType get_feedback(unsigned int channel) const;

    /// Sets the output gain of a channel (between -1 and 1)
    void set_outgain(unsigned int channel, DataType ingain);
    /// Gets the output gain of a channel
    DataType get_outgain(unsigned int channel) const;
  };
}

%template(FloatHadamardFeedbackDelayNetworkFilter) ATK::HadamardFeedbackDelayNetworkFilter<float, 4>;
%template(DoubleHadamardFeedbackDelayNetworkFilter) ATK::HadamardFeedbackDelayNetworkFilter<double, 4>;
%template(ComplexFloatHadamardFeedbackDelayNetworkFilter) ATK::HadamardFeedbackDelayNetworkFilter<std::complex<float>, 4>;
%template(ComplexDoubleHadamardFeedbackDelayNetworkFilter) ATK::HadamardFeedbackDelayNetworkFilter<std::complex<double>, 4>;

