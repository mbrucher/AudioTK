/**
 * \file CustomIIRFilter.cpp
 */

#include <ATK/EQ/config.h>
#include <ATK/EQ/CustomIIRFilter.h>

#include <cassert>
#include <cmath>
#include <complex>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType>
  CustomIIRCoefficients<DataType>::CustomIIRCoefficients(gsl::index nb_channels)
    :Parent(nb_channels, nb_channels), in_order(0), out_order(0)
  {
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_in(const std::vector<typename TypeTraits<DataType>::Scalar>& coefficients_in )
  {
    in_order = static_cast<int>(coefficients_in.size() - 1);
    this->coefficients_in.assign(coefficients_in.begin(), coefficients_in.end());

    setup();
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_out(const std::vector<typename TypeTraits<DataType>::Scalar>& coefficients_out )
  {
    out_order = static_cast<int>(coefficients_out.size());
    this->coefficients_out.assign(coefficients_out.begin(), coefficients_out.end());

    setup();
  }

  template class ATK_EQ_EXPORT CustomIIRCoefficients<float>;
  template class ATK_EQ_EXPORT CustomIIRCoefficients<double>;
  
  template class ATK_EQ_EXPORT CustomIIRCoefficients<std::complex<float>>;
  template class ATK_EQ_EXPORT CustomIIRCoefficients<std::complex<double>>;
}
