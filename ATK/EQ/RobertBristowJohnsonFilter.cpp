/**
 * \file RobertBristowJohnsonFilter.cpp
 */

#include <ATK/EQ/RobertBristowJohnsonFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class RobertBristowJohnsonLowPassCoefficients<float>;
  template class RobertBristowJohnsonLowPassCoefficients<double>;
  template class RobertBristowJohnsonLowPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonLowPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonHighPassCoefficients<float>;
  template class RobertBristowJohnsonHighPassCoefficients<double>;
  template class RobertBristowJohnsonHighPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonHighPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandPassCoefficients<float>;
  template class RobertBristowJohnsonBandPassCoefficients<double>;
  template class RobertBristowJohnsonBandPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandPass2Coefficients<float>;
  template class RobertBristowJohnsonBandPass2Coefficients<double>;
  template class RobertBristowJohnsonBandPass2Coefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandPass2Coefficients<std::complex<double> >;
  template class RobertBristowJohnsonAllPassCoefficients<float>;
  template class RobertBristowJohnsonAllPassCoefficients<double>;
  template class RobertBristowJohnsonAllPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonAllPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandStopCoefficients<float>;
  template class RobertBristowJohnsonBandStopCoefficients<double>;
  template class RobertBristowJohnsonBandStopCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandStopCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<float>;
  template class RobertBristowJohnsonBandPassPeakCoefficients<double>;
  template class RobertBristowJohnsonBandPassPeakCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<float>;
  template class RobertBristowJohnsonLowShelvingCoefficients<double>;
  template class RobertBristowJohnsonLowShelvingCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<float>;
  template class RobertBristowJohnsonHighShelvingCoefficients<double>;
  template class RobertBristowJohnsonHighShelvingCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<std::complex<double> >;

  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<std::complex<double> > >;
}
