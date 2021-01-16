/**
 * \file RobertBristowJohnsonFilter.cpp
 */

#include "RobertBristowJohnsonFilter.hxx"
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowPassCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighPassCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPass2Coefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPass2Coefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPass2Coefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonAllPassCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonAllPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonAllPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandStopCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandStopCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandStopCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassPeakCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassPeakCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassPeakCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowShelvingCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowShelvingCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowShelvingCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighShelvingCoefficients<float>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighShelvingCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighShelvingCoefficients<std::complex<double> >;
#endif
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowPassCoefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighPassCoefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassCoefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPass2Coefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonAllPassCoefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandStopCoefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonBandPassPeakCoefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonLowShelvingCoefficients<double>;
  template class ATK_EQ_EXPORT RobertBristowJohnsonHighShelvingCoefficients<double>;
}
