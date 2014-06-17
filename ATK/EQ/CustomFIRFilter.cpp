/**
 * \file CustomFIRFilter.cpp
 */

#include "CustomFIRFilter.h"
//#include "FIRFilter.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType>
  CustomFIRCoefficients<DataType>::CustomFIRCoefficients()
    :Parent(1, 1)
  {
  }

  template<typename DataType_>
  void ATK::CustomFIRCoefficients<DataType_>::set_coefficients_in( const std::vector<DataType>& coefficients_in )
  {
    this->coefficients_in = coefficients_in;
    in_order = coefficients_in.size() - 1;

    setup();
  }

  template class CustomFIRCoefficients<float>;
  template class CustomFIRCoefficients<double>;
  
//  template class FIRFilter<CustomFIRCoefficients<float> >;
//  template class FIRFilter<CustomFIRCoefficients<double> >;
}
