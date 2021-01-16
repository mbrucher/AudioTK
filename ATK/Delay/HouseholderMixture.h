/**
 * \file HouseholderFeedbackDelayNetworkFilter.h
 */

#ifndef ATK_DELAY_HOUSEHOLDERFEEDBACKDELAYNETWORKFILTER_H
#define ATK_DELAY_HOUSEHOLDERFEEDBACKDELAYNETWORKFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>

#include <array>
#include <vector>

namespace ATK
{
  /// Mixture matrix for Householder
  template<typename DataType_, unsigned int nb_channels_>
  class HouseholderMixture
  {
  public:
    static const gsl::index nb_channels = nb_channels_;
    using DataType = DataType_;
    /// Gain factor to take into account in the feedback loop due to the instability of the mixture
    static constexpr float gain_factor = 0.5F; // should be std::pow(2, -order / 2.);, but pow is not constexpr :/

    class MixtureImpl;
  };
}

#endif
