/**
 * \file RIAAFilter.cpp
 */

#include <ATK/EQ/RIAAFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class RIAACoefficients<float>;
  template class RIAACoefficients<double>;
  template class InverseRIAACoefficients<float>;
  template class InverseRIAACoefficients<double>;
  
  template class IIRFilter<RIAACoefficients<float> >;
  template class IIRFilter<RIAACoefficients<double> >;
  template class IIRFilter<InverseRIAACoefficients<float> >;
  template class IIRFilter<InverseRIAACoefficients<double> >;

  template class IIRTDF2Filter<RIAACoefficients<float> >;
  template class IIRTDF2Filter<RIAACoefficients<double> >;
  template class IIRTDF2Filter<InverseRIAACoefficients<float> >;
  template class IIRTDF2Filter<InverseRIAACoefficients<double> >;
}
