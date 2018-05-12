/**
 * \file CustomIIRFilter.cpp
 */

#include <ATK/EQ/CustomIIRFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <cassert>
#include <cmath>
#include <complex>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType>
  CustomIIRCoefficients<DataType>::CustomIIRCoefficients(std::size_t nb_channels)
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

  template class CustomIIRCoefficients<float>;
  template class CustomIIRCoefficients<double>;
  
  template class CustomIIRCoefficients<std::complex<float>>;
  template class CustomIIRCoefficients<std::complex<double>>;

  template class IIRFilter<CustomIIRCoefficients<float>>;
  template class IIRFilter<CustomIIRCoefficients<double>>;
  template class IIRFilter<CustomIIRCoefficients<std::complex<float>>>;
  template class IIRFilter<CustomIIRCoefficients<std::complex<double>>>;

  template class IIRTDF2Filter<CustomIIRCoefficients<float>>;
  template class IIRTDF2Filter<CustomIIRCoefficients<double>>;
  template class IIRTDF2Filter<CustomIIRCoefficients<std::complex<float>>>;
  template class IIRTDF2Filter<CustomIIRCoefficients<std::complex<double>>>;
}
