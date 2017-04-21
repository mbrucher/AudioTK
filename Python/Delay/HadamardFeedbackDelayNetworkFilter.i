
%{
#include <ATK/Delay/HadamardFeedbackDelayNetworkFilter.h>
%}

namespace ATK
{
  template<typename DataType, unsigned int order>
  class HadamardMixture
  {
  };

  template<typename Mixture>
  class FeedbackDelayNetworkFilter : public BaseFilter
  {
  public:
    FeedbackDelayNetworkFilter(std::size_t max_delay);
    ~FeedbackDelayNetworkFilter();

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

%template(FloatHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>>;
%template(DoubleHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 2>>;
%template(ComplexFloatHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 2>>;
%template(ComplexDoubleHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 2>>;

