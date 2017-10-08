/**
 * \file LinkwitzRileyFilter.cpp
 */

#include <ATK/EQ/LinkwitzRileyFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class LinkwitzRileyLowPassCoefficients<float>;
  template class LinkwitzRileyLowPassCoefficients<double>;
  template class LinkwitzRileyLowPassCoefficients<std::complex<float> >;
  template class LinkwitzRileyLowPassCoefficients<std::complex<double> >;
  template class LinkwitzRileyHighPassCoefficients<float>;
  template class LinkwitzRileyHighPassCoefficients<double>;
  template class LinkwitzRileyHighPassCoefficients<std::complex<float> >;
  template class LinkwitzRileyHighPassCoefficients<std::complex<double> >;
  template class LinkwitzRiley4LowPassCoefficients<float>;
  template class LinkwitzRiley4LowPassCoefficients<double>;
  template class LinkwitzRiley4LowPassCoefficients<std::complex<float> >;
  template class LinkwitzRiley4LowPassCoefficients<std::complex<double> >;
  template class LinkwitzRiley4HighPassCoefficients<float>;
  template class LinkwitzRiley4HighPassCoefficients<double>;
  template class LinkwitzRiley4HighPassCoefficients<std::complex<float> >;
  template class LinkwitzRiley4HighPassCoefficients<std::complex<double> >;
  
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<LinkwitzRiley4LowPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRiley4LowPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRiley4LowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<LinkwitzRiley4LowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<LinkwitzRiley4HighPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRiley4HighPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRiley4HighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<LinkwitzRiley4HighPassCoefficients<std::complex<double> > >;

  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<float> >;
  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<double> >;
  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<float> >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<double> >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<float> >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<double> >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<float> >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<double> >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<std::complex<double> > >;
  
}
