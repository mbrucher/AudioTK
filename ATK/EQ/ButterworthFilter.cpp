/**
 * \file ButterworthFilter.cpp
 */

#include <ATK/EQ/ButterworthFilter.hxx>

namespace ATK
{
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<double>;
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthLowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<double>;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthHighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<double>;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthBandPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<float>;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<double>;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ButterworthBandStopCoefficients<std::complex<double> >;
  }
