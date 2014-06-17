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
  CustomIIRCoefficients<DataType>::CustomIIRCoefficients()
    :Parent(1, 1)
  {
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_in( const std::vector<DataType>& coefficients_in )
  {
    this->coefficients_in = coefficients_in;
    in_order = coefficients_in.size() - 1;

    setup();
  }

  template<typename DataType_>
  void ATK::CustomIIRCoefficients<DataType_>::set_coefficients_out( const std::vector<DataType>& coefficients_out )
  {
    this->coefficients_out = coefficients_out;
    out_order = coefficients_out.size();

    setup();
  }

  template class CustomIIRCoefficients<float>;
  template class CustomIIRCoefficients<double>;
  
  template class IIRFilter<CustomIIRCoefficients<float> >;
  template class IIRFilter<CustomIIRCoefficients<double> >;
}
