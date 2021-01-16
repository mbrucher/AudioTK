/**
 * \file CustomFIRFilter.cpp
 */

#include "CustomFIRFilter.h"
#include <ATK/EQ/config.h>

#include <boost/math/constants/constants.hpp>

#include <complex>
#include <cassert>
#include <cmath>

namespace ATK
{
  template <typename DataType>
  CustomFIRCoefficients<DataType>::CustomFIRCoefficients(gsl::index nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template<typename DataType_>
  void ATK::CustomFIRCoefficients<DataType_>::set_coefficients_in(const std::vector<typename TypeTraits<DataType>::Scalar>& coefficients_in)
  {
    in_order = static_cast<int>(coefficients_in.size() - 1);
    this->coefficients_in.assign(coefficients_in.begin(), coefficients_in.end());

    setup();
  }

#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT CustomFIRCoefficients<float>;
  template class ATK_EQ_EXPORT CustomFIRCoefficients<std::complex<float>>;
  template class ATK_EQ_EXPORT CustomFIRCoefficients<std::complex<double>>;
#endif
  template class ATK_EQ_EXPORT CustomFIRCoefficients<double>;
}
