/**
 * \file HadamardFeedbackDelayNetworkFilter.h
 */

#ifndef ATK_DELAY_HADAMARDFEEDBACKDELAYNETWORKFILTER_H
#define ATK_DELAY_HADAMARDFEEDBACKDELAYNETWORKFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>

#include <array>
#include <vector>

namespace ATK
{
  /// Mixture matrix for Hadamard
  template<typename DataType_, unsigned int order>
  class HadamardMixture
  {
  public:
    static constexpr gsl::index nb_channels = 1 << order;
    using DataType = DataType_;
    /// Gain factor to take into account in the feedback loop due to the instability of the mixture
    static constexpr float gain_factor = 1.F;

    class MixtureImpl;
  };
}

#endif
