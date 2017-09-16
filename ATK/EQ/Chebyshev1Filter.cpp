/**
 * \file Chebyshev1Filter.cpp
 */

#include <ATK/EQ/Chebyshev1Filter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class Chebyshev1LowPassCoefficients<float>;
  template class Chebyshev1LowPassCoefficients<double>;
  template class Chebyshev1LowPassCoefficients<std::complex<float> >;
  template class Chebyshev1LowPassCoefficients<std::complex<double> >;
  template class Chebyshev1HighPassCoefficients<float>;
  template class Chebyshev1HighPassCoefficients<double>;
  template class Chebyshev1HighPassCoefficients<std::complex<float> >;
  template class Chebyshev1HighPassCoefficients<std::complex<double> >;
  template class Chebyshev1BandPassCoefficients<float>;
  template class Chebyshev1BandPassCoefficients<double>;
  template class Chebyshev1BandPassCoefficients<std::complex<float> >;
  template class Chebyshev1BandPassCoefficients<std::complex<double> >;
  template class Chebyshev1BandStopCoefficients<float>;
  template class Chebyshev1BandStopCoefficients<double>;
  template class Chebyshev1BandStopCoefficients<std::complex<float> >;
  template class Chebyshev1BandStopCoefficients<std::complex<double> >;
  
  template class IIRFilter<Chebyshev1LowPassCoefficients<float> >;
  template class IIRFilter<Chebyshev1LowPassCoefficients<double> >;
  template class IIRFilter<Chebyshev1LowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev1LowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<Chebyshev1HighPassCoefficients<float> >;
  template class IIRFilter<Chebyshev1HighPassCoefficients<double> >;
  template class IIRFilter<Chebyshev1HighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev1HighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<Chebyshev1BandPassCoefficients<float> >;
  template class IIRFilter<Chebyshev1BandPassCoefficients<double> >;
  template class IIRFilter<Chebyshev1BandPassCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev1BandPassCoefficients<std::complex<double> > >;
  template class IIRFilter<Chebyshev1BandStopCoefficients<float> >;
  template class IIRFilter<Chebyshev1BandStopCoefficients<double> >;
  template class IIRFilter<Chebyshev1BandStopCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev1BandStopCoefficients<std::complex<double> > >;
  
  template class IIRTDF2Filter<Chebyshev1LowPassCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev1LowPassCoefficients<double> >;
  template class IIRTDF2Filter<Chebyshev1HighPassCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev1HighPassCoefficients<double> >;
  template class IIRTDF2Filter<Chebyshev1BandPassCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev1BandPassCoefficients<double> >;
  template class IIRTDF2Filter<Chebyshev1BandStopCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev1BandStopCoefficients<double> >;
}
