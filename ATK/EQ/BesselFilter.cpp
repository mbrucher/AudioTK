/**
 * \file BesselFilter.cpp
 */

#include <ATK/EQ/BesselFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class BesselLowPassCoefficients<float>;
  template class BesselLowPassCoefficients<double>;
  template class BesselLowPassCoefficients<std::complex<float> >;
  template class BesselLowPassCoefficients<std::complex<double> >;
  template class BesselHighPassCoefficients<float>;
  template class BesselHighPassCoefficients<double>;
  template class BesselHighPassCoefficients<std::complex<float> >;
  template class BesselHighPassCoefficients<std::complex<double> >;
  template class BesselBandPassCoefficients<float>;
  template class BesselBandPassCoefficients<double>;
  template class BesselBandPassCoefficients<std::complex<float> >;
  template class BesselBandPassCoefficients<std::complex<double> >;
  template class BesselBandStopCoefficients<float>;
  template class BesselBandStopCoefficients<double>;
  template class BesselBandStopCoefficients<std::complex<float> >;
  template class BesselBandStopCoefficients<std::complex<double> >;
  
  template class IIRFilter<BesselLowPassCoefficients<float> >;
  template class IIRFilter<BesselLowPassCoefficients<double> >;
  template class IIRFilter<BesselLowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<BesselLowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<BesselHighPassCoefficients<float> >;
  template class IIRFilter<BesselHighPassCoefficients<double> >;
  template class IIRFilter<BesselHighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<BesselHighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<BesselBandPassCoefficients<float> >;
  template class IIRFilter<BesselBandPassCoefficients<double> >;
  template class IIRFilter<BesselBandPassCoefficients<std::complex<float> > >;
  template class IIRFilter<BesselBandPassCoefficients<std::complex<double> > >;
  template class IIRFilter<BesselBandStopCoefficients<float> >;
  template class IIRFilter<BesselBandStopCoefficients<double> >;
  template class IIRFilter<BesselBandStopCoefficients<std::complex<float> > >;
  template class IIRFilter<BesselBandStopCoefficients<std::complex<double> > >;
  
  template class IIRTDF2Filter<BesselLowPassCoefficients<float> >;
  template class IIRTDF2Filter<BesselLowPassCoefficients<double> >;
  template class IIRTDF2Filter<BesselHighPassCoefficients<float> >;
  template class IIRTDF2Filter<BesselHighPassCoefficients<double> >;
  template class IIRTDF2Filter<BesselBandPassCoefficients<float> >;
  template class IIRTDF2Filter<BesselBandPassCoefficients<double> >;
  template class IIRTDF2Filter<BesselBandStopCoefficients<float> >;
  template class IIRTDF2Filter<BesselBandStopCoefficients<double> >;
}
