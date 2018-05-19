/**
 * \file RIAAFilter.cpp
 */

#include <gsl/gsl>

#include <ATK/EQ/RIAAFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template<typename DataType_>
  const static gsl::index RIAACoefficients<DataType_>::in_order = 4;
  template<typename DataType_>
  const static gsl::index RIAACoefficients<DataType_>::out_order = 4;
  template<typename DataType_>
  const static gsl::index InverseRIAACoefficients<DataType_>::in_order = 4;
  template<typename DataType_>
  const static gsl::index InverseRIAACoefficients<DataType_>::out_order = 4;

  template class ATK_EQ_EXPORT RIAACoefficients<float>;
  template class ATK_EQ_EXPORT RIAACoefficients<double>;
  template class ATK_EQ_EXPORT InverseRIAACoefficients<float>;
  template class ATK_EQ_EXPORT InverseRIAACoefficients<double>;
}
