/**
 * \file ButterworthFilter.cpp
 */

#include "ButterworthFilter.hxx"

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<std::complex<double> >;
#endif
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<double>;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<double>;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<double>;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<double>;
}
