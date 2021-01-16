/**
 * \file ToneStackFilter.cpp
 */

#include "ToneStackFilter.hxx"
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT ToneStackCoefficients<float>;
  template class ATK_EQ_EXPORT ToneStackCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ToneStackCoefficients<std::complex<double> >;
#endif
  template class ATK_EQ_EXPORT ToneStackCoefficients<double>;
}
