/**
 * \file HouseholderMixture2.cpp
 */

#include <ATK/Delay/HouseholderMixture.hxx>

#include <complex>

namespace ATK
{
  template class FeedbackDelayNetworkFilter<HouseholderMixture<float, 8>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<double, 8>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 8>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 8>>;
}
