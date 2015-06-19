/**
 * \file CustomIIRFilter.cpp
 */

#include "CustomIIRFilter.h"
#include "IIRFilter.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType>
  CustomIIRCoefficients<DataType>::CustomIIRCoefficients(int nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_in( std::vector<DataType> coefficients_in )
  {
    in_order = static_cast<int>(coefficients_in.size() - 1);
    this->coefficients_in = std::move(coefficients_in);

    setup();
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_out( std::vector<DataType> coefficients_out )
  {
    out_order = static_cast<int>(coefficients_out.size());
    this->coefficients_out = std::move(coefficients_out);

    setup();
  }

  template class CustomIIRCoefficients<float>;
  template class CustomIIRCoefficients<double>;
  
  template class IIRFilter<CustomIIRCoefficients<float> >;
  template class IIRFilter<CustomIIRCoefficients<double> >;
}
