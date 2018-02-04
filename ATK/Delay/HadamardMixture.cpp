/**
 * \file HadamardMixture.cpp
 */

#include <ATK/Delay/HadamardMixture.hxx>

#include <complex>
namespace ATK
{
  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 1>>;

  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 2>>;

  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 3>>;
}
