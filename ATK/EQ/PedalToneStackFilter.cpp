/**
 * \file PedalToneStackFilter.cpp
 */

#include <ATK/EQ/PedalToneStackFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class SD1ToneCoefficients<float>;
  template class SD1ToneCoefficients<double>;
  template class SD1ToneCoefficients<std::complex<float> >;
  template class SD1ToneCoefficients<std::complex<double> >;
  
  template class IIRFilter<SD1ToneCoefficients<float> >;
  template class IIRFilter<SD1ToneCoefficients<double> >;
  template class IIRFilter<SD1ToneCoefficients<std::complex<float> > >;
  template class IIRFilter<SD1ToneCoefficients<std::complex<double> > >;

  template class TS9ToneCoefficients<float>;
  template class TS9ToneCoefficients<double>;
  template class TS9ToneCoefficients<std::complex<float> >;
  template class TS9ToneCoefficients<std::complex<double> >;
  
  template class IIRFilter<TS9ToneCoefficients<float> >;
  template class IIRFilter<TS9ToneCoefficients<double> >;
  template class IIRFilter<TS9ToneCoefficients<std::complex<float> > >;
  template class IIRFilter<TS9ToneCoefficients<std::complex<double> > >;
}
