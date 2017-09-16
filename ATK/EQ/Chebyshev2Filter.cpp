/**
 * \file Chebyshev2Filter.cpp
 */

#include <ATK/EQ/Chebyshev2Filter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class Chebyshev2LowPassCoefficients<float>;
  template class Chebyshev2LowPassCoefficients<double>;
  template class Chebyshev2LowPassCoefficients<std::complex<float> >;
  template class Chebyshev2LowPassCoefficients<std::complex<double> >;
  template class Chebyshev2HighPassCoefficients<float>;
  template class Chebyshev2HighPassCoefficients<double>;
  template class Chebyshev2HighPassCoefficients<std::complex<float> >;
  template class Chebyshev2HighPassCoefficients<std::complex<double> >;
  template class Chebyshev2BandPassCoefficients<float>;
  template class Chebyshev2BandPassCoefficients<double>;
  template class Chebyshev2BandPassCoefficients<std::complex<float> >;
  template class Chebyshev2BandPassCoefficients<std::complex<double> >;
  template class Chebyshev2BandStopCoefficients<float>;
  template class Chebyshev2BandStopCoefficients<double>;
  template class Chebyshev2BandStopCoefficients<std::complex<float> >;
  template class Chebyshev2BandStopCoefficients<std::complex<double> >;
  
  template class IIRFilter<Chebyshev2LowPassCoefficients<float> >;
  template class IIRFilter<Chebyshev2LowPassCoefficients<double> >;
  template class IIRFilter<Chebyshev2LowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev2LowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<Chebyshev2HighPassCoefficients<float> >;
  template class IIRFilter<Chebyshev2HighPassCoefficients<double> >;
  template class IIRFilter<Chebyshev2HighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev2HighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<Chebyshev2BandPassCoefficients<float> >;
  template class IIRFilter<Chebyshev2BandPassCoefficients<double> >;
  template class IIRFilter<Chebyshev2BandPassCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev2BandPassCoefficients<std::complex<double> > >;
  template class IIRFilter<Chebyshev2BandStopCoefficients<float> >;
  template class IIRFilter<Chebyshev2BandStopCoefficients<double> >;
  template class IIRFilter<Chebyshev2BandStopCoefficients<std::complex<float> > >;
  template class IIRFilter<Chebyshev2BandStopCoefficients<std::complex<double> > >;
  
  template class IIRTDF2Filter<Chebyshev2LowPassCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev2LowPassCoefficients<double> >;
  template class IIRTDF2Filter<Chebyshev2HighPassCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev2HighPassCoefficients<double> >;
  template class IIRTDF2Filter<Chebyshev2BandPassCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev2BandPassCoefficients<double> >;
  template class IIRTDF2Filter<Chebyshev2BandStopCoefficients<float> >;
  template class IIRTDF2Filter<Chebyshev2BandStopCoefficients<double> >;
}
