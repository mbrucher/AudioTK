/**
 * \file ToneStackFilter.cpp
 */

#include <ATK/EQ/ToneStackFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class ToneStackCoefficients<float>;
  template class ToneStackCoefficients<double>;
  template class ToneStackCoefficients<std::complex<float> >;
  template class ToneStackCoefficients<std::complex<double> >;
  
  template class IIRFilter<ToneStackCoefficients<float> >;
  template class IIRFilter<ToneStackCoefficients<double> >;
  template class IIRFilter<ToneStackCoefficients<std::complex<float> > >;
  template class IIRFilter<ToneStackCoefficients<std::complex<double> > >;

  template class IIRTDF2Filter<ToneStackCoefficients<float> >;
  template class IIRTDF2Filter<ToneStackCoefficients<double> >;
  template class IIRTDF2Filter<ToneStackCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<ToneStackCoefficients<std::complex<double> > >;
}
