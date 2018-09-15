/**
 * \file CustomFIRFilter.cpp
 */

#include <ATK/EQ/config.h>
#include <ATK/EQ/CustomFIRFilter.h>

#include <complex>
#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType>
  CustomFIRCoefficients<DataType>::CustomFIRCoefficients(gsl::index nb_channels)
    :Parent(nb_channels, nb_channels), in_order(0)
  {
  }

  template<typename DataType_>
  void ATK::CustomFIRCoefficients<DataType_>::set_coefficients_in(const std::vector<typename TypeTraits<DataType>::Scalar>& coefficients_in)
  {
    in_order = static_cast<int>(coefficients_in.size() - 1);
    this->coefficients_in.assign(coefficients_in.begin(), coefficients_in.end());

    setup();
  }

  template class ATK_EQ_EXPORT CustomFIRCoefficients<float>;
  template class ATK_EQ_EXPORT CustomFIRCoefficients<double>;
  
  template class ATK_EQ_EXPORT CustomFIRCoefficients<std::complex<float>>;
  template class ATK_EQ_EXPORT CustomFIRCoefficients<std::complex<double>>;
}
