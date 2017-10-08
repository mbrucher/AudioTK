/**
 * \file SecondOrderFilter.cpp
 */

#include <ATK/EQ/SecondOrderFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class SecondOrderBaseCoefficients<float>;
  template class SecondOrderBaseCoefficients<double>;
  template class SecondOrderBaseCoefficients<std::complex<float> >;
  template class SecondOrderBaseCoefficients<std::complex<double> >;
  
  template class SecondOrderBandPassCoefficients<float>;
  template class SecondOrderBandPassCoefficients<double>;
  template class SecondOrderBandPassCoefficients<std::complex<float> >;
  template class SecondOrderBandPassCoefficients<std::complex<double> >;
  template class SecondOrderLowPassCoefficients<float>;
  template class SecondOrderLowPassCoefficients<double>;
  template class SecondOrderLowPassCoefficients<std::complex<float> >;
  template class SecondOrderLowPassCoefficients<std::complex<double> >;
  template class SecondOrderHighPassCoefficients<float>;
  template class SecondOrderHighPassCoefficients<double>;
  template class SecondOrderHighPassCoefficients<std::complex<float> >;
  template class SecondOrderHighPassCoefficients<std::complex<double> >;
  template class SecondOrderBandPassPeakCoefficients<float>;
  template class SecondOrderBandPassPeakCoefficients<double>;
  template class SecondOrderBandPassPeakCoefficients<std::complex<float> >;
  template class SecondOrderBandPassPeakCoefficients<std::complex<double> >;
  template class SecondOrderAllPassCoefficients<float>;
  template class SecondOrderAllPassCoefficients<double>;
  template class SecondOrderAllPassCoefficients<std::complex<float> >;
  template class SecondOrderAllPassCoefficients<std::complex<double> >;
  template class SecondOrderLowShelvingCoefficients<float>;
  template class SecondOrderLowShelvingCoefficients<double>;
  template class SecondOrderLowShelvingCoefficients<std::complex<float> >;
  template class SecondOrderLowShelvingCoefficients<std::complex<double> >;
  template class SecondOrderHighShelvingCoefficients<float>;
  template class SecondOrderHighShelvingCoefficients<double>;
  template class SecondOrderHighShelvingCoefficients<std::complex<float> >;
  template class SecondOrderHighShelvingCoefficients<std::complex<double> >;
  
  template class IIRFilter<SecondOrderBandPassCoefficients<float> >;
  template class IIRFilter<SecondOrderBandPassCoefficients<double> >;
  template class IIRFilter<SecondOrderBandPassCoefficients<std::complex<float> > >;
  template class IIRFilter<SecondOrderBandPassCoefficients<std::complex<double> > >;
  template class IIRFilter<SecondOrderLowPassCoefficients<float> >;
  template class IIRFilter<SecondOrderLowPassCoefficients<double> >;
  template class IIRFilter<SecondOrderLowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<SecondOrderLowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<SecondOrderHighPassCoefficients<float> >;
  template class IIRFilter<SecondOrderHighPassCoefficients<double> >;
  template class IIRFilter<SecondOrderHighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<SecondOrderHighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<SecondOrderBandPassPeakCoefficients<float> >;
  template class IIRFilter<SecondOrderBandPassPeakCoefficients<double> >;
  template class IIRFilter<SecondOrderBandPassPeakCoefficients<std::complex<float> > >;
  template class IIRFilter<SecondOrderBandPassPeakCoefficients<std::complex<double> > >;
  template class IIRFilter<SecondOrderAllPassCoefficients<float> >;
  template class IIRFilter<SecondOrderAllPassCoefficients<double> >;
  template class IIRFilter<SecondOrderAllPassCoefficients<std::complex<float> > >;
  template class IIRFilter<SecondOrderAllPassCoefficients<std::complex<double> > >;
  template class IIRFilter<SecondOrderLowShelvingCoefficients<float> >;
  template class IIRFilter<SecondOrderLowShelvingCoefficients<double> >;
  template class IIRFilter<SecondOrderLowShelvingCoefficients<std::complex<float> > >;
  template class IIRFilter<SecondOrderLowShelvingCoefficients<std::complex<double> > >;
  template class IIRFilter<SecondOrderHighShelvingCoefficients<float> >;
  template class IIRFilter<SecondOrderHighShelvingCoefficients<double> >;
  template class IIRFilter<SecondOrderHighShelvingCoefficients<std::complex<float> > >;
  template class IIRFilter<SecondOrderHighShelvingCoefficients<std::complex<double> > >;

  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<float> >;
  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<double> >;
  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<float> >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<double> >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<float> >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<double> >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<float> >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<double> >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<float> >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<double> >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<float> >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<double> >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<float> >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<double> >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<std::complex<double> > >;
}
