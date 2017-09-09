/**
 * \file CustomIIRFilter.cpp
 */

#include "CustomIIRFilter.h"
#include "IIRFilter.h"

#include <cassert>
#include <cmath>
#include <complex>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType>
  CustomIIRCoefficients<DataType>::CustomIIRCoefficients(std::size_t nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_in(const std::vector<typename TypeTraits<DataType>::Scalar>& coefficients_in )
  {
    in_order = static_cast<int>(coefficients_in.size() - 1);
    this->coefficients_in.clear();
    this->coefficients_in.insert(this->coefficients_in.end(), coefficients_in.begin(), coefficients_in.end());

    setup();
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_out(const std::vector<typename TypeTraits<DataType>::Scalar>& coefficients_out )
  {
    out_order = static_cast<int>(coefficients_out.size());
    this->coefficients_out.clear();
    this->coefficients_out.insert(this->coefficients_out.end(), coefficients_out.begin(), coefficients_out.end());

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
