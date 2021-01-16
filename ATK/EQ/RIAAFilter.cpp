/**
 * \file RIAAFilter.cpp
 */

#include "RIAAFilter.hxx"
#include <ATK/EQ/IIRFilter.h>

#include <gsl/gsl>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT RIAACoefficients<float>;
  template class ATK_EQ_EXPORT InverseRIAACoefficients<float>;
#endif
  template class ATK_EQ_EXPORT RIAACoefficients<double>;
  template class ATK_EQ_EXPORT InverseRIAACoefficients<double>;
}
