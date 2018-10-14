/**
 * \file RIAAFilter.cpp
 */

#include <gsl/gsl>

#include <ATK/EQ/RIAAFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT RIAACoefficients<float>;
  template class ATK_EQ_EXPORT InverseRIAACoefficients<float>;
#endif
  template class ATK_EQ_EXPORT RIAACoefficients<double>;
  template class ATK_EQ_EXPORT InverseRIAACoefficients<double>;
}
