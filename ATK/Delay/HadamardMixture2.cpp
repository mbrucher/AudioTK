/**
 * \file HadamardMixture.cpp
 */

#include "HadamardMixture.hxx"

#include <complex>

namespace ATK
{
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 3>>;
#if ATK_ENABLE_INSTANTIATION
  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 3>>;
#endif
}
