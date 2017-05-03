
%{
#include <ATK/Delay/FeedbackDelayNetworkFilter.h>
#include <ATK/Delay/HadamardMixture.h>
#include <ATK/Delay/HouseholderMixture.h>
%}

namespace ATK
{
  template<typename DataType_, unsigned int order>
  class HadamardMixture
  {
  public:
    typedef DataType_ DataType;
  };

  template<typename DataType_, unsigned int nb_channels>
  class HouseholderMixture
  {
  public:
    typedef DataType_ DataType;
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

    void set_ingain(unsigned int channel, double ingain);
    /// Gets the input gain of a channel
    double get_ingain(unsigned int channel) const;

    /// Sets the feedback of a channel
    void set_feedback(unsigned int channel, double feedback);
    /// Gets the feedback of a channel
    double get_feedback(unsigned int channel) const;

    /// Sets the output gain of a channel (between -1 and 1)
    void set_outgain(unsigned int channel, double ingain);
    /// Gets the output gain of a channel
    double get_outgain(unsigned int channel) const;
  };
}

%template(FloatDualHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 1>>;
%template(DoubleDualHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 1>>;

%template(FloatHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>>;
%template(DoubleHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 2>>;

%template(FloatQuadHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 2>>;
%template(DoubleQuadHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 2>>;

%template(FloatOctHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<float, 3>>;
%template(DoubleOctHadamardFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HadamardMixture<double, 3>>;

%template(FloatDualHouseholderFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<float, 2>>;
%template(DoubleDualHouseholderFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>>;

%template(FloatQuadHouseholderFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<float, 4>>;
%template(DoubleQuadHouseholderFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 4>>;

%template(FloatOctHouseholderFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<float, 8>>;
%template(DoubleOctHouseholderFeedbackDelayNetworkFilter) ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 8>>;

