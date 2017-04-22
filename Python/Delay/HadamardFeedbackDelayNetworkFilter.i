
%{
#include <ATK/Delay/FeedbackDelayNetworkFilter.h>
#include <ATK/Delay/HadamardMixture.h>
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

    void set_ingain(unsigned int channel, Mixture::DataType ingain);
    /// Gets the input gain of a channel
    Mixture::DataType get_ingain(unsigned int channel) const;

    /// Sets the feedback of a channel
    void set_feedback(unsigned int channel, Mixture::DataType feedback);
    /// Gets the feedback of a channel
    Mixture::DataType get_feedback(unsigned int channel) const;

    /// Sets the output gain of a channel (between -1 and 1)
    void set_outgain(unsigned int channel, Mixture::DataType ingain);
    /// Gets the output gain of a channel
    Mixture::DataType get_outgain(unsigned int channel) const;
  };
}

%template(FloatDualHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 1>>;
%template(DoubleDualHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 1>>;
%template(ComplexFloatDualHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 1>>;
%template(ComplexDoubleDualHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 1>>;

%template(FloatHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>>;
%template(DoubleHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 2>>;
%template(ComplexFloatHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 2>>;
%template(ComplexDoubleHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 2>>;

%template(FloatQuadHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>>;
%template(DoubleQuadHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 2>>;
%template(ComplexFloatQuadHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 2>>;
%template(ComplexDoubleQuadHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 2>>;

%template(FloatOctHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 3>>;
%template(DoubleOctHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 3>>;
%template(ComplexFloatOctHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 3>>;
%template(ComplexDoubleOctHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<std::complex<double>, 3>>;

