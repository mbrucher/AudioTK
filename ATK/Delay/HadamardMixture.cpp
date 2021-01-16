/**
 * \file HadamardMixture.cpp
 */

#include "HadamardMixture.hxx"

#include <complex>

namespace ATK
{
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 2>>;

#if ATK_ENABLE_INSTANTIATION
  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 1>>;

  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 2>>;
#endif
}
