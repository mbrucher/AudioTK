/**
 * \file PedalToneStackFilter.cpp
 */

#include "PedalToneStackFilter.hxx"
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT SD1ToneCoefficients<float>;
  template class ATK_EQ_EXPORT SD1ToneCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SD1ToneCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT TS9ToneCoefficients<float>;
  template class ATK_EQ_EXPORT TS9ToneCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT TS9ToneCoefficients<std::complex<double> >;
#endif
  template class ATK_EQ_EXPORT SD1ToneCoefficients<double>;
  template class ATK_EQ_EXPORT TS9ToneCoefficients<double>;
}
