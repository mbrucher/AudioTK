/**
 * \file ToneStackFilter.cpp
 */

#include <ATK/EQ/ToneStackFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class ATK_EQ_EXPORT ToneStackCoefficients<float>;
  template class ATK_EQ_EXPORT ToneStackCoefficients<double>;
  template class ATK_EQ_EXPORT ToneStackCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT ToneStackCoefficients<std::complex<double> >;
}
