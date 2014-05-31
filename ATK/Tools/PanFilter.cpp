/**
 * \file PanFilter.cpp
 */

#include "PanFilter.h"

#include <cmath>
#include <cstdint>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType_>
  PanFilter<DataType_>::PanFilter()
  :Parent(1, 2), law(SINCOS_0_CENTER), pan(0)
  {
    
  }
  
  template<typename DataType_>
  PanFilter<DataType_>::~PanFilter()
  {
    
  }
  
  template<typename DataType_>
  void PanFilter<DataType_>::set_pan_law(PAN_LAWS law)
  {
    this->law = law;
  }
  
  template<typename DataType_>
  void PanFilter<DataType_>::set_pan(double pan)
  {
    this->pan = pan;
  }

  template<typename DataType_>
  void PanFilter<DataType_>::process_impl(std::int64_t size)
  {
    double left_coeff = 1;
    double right_coeff = 1;
    
    switch(law)
    {
      case SINCOS_0_CENTER:
        left_coeff = std::sqrt(2) * std::cos((pan + 1) / 4 * boost::math::constants::pi<double>());
        right_coeff = std::sqrt(2) * std::sin((pan + 1) / 4 * boost::math::constants::pi<double>());
        break;
      case SINCOS_3_CENTER:
        left_coeff = std::cos((pan + 1) / 4 * boost::math::constants::pi<double>());
        right_coeff = std::sin((pan + 1) / 4 * boost::math::constants::pi<double>());
        break;
      case SQUARE_0_CENTER:
        left_coeff = std::sqrt(2) * std::sqrt((1 - pan) / 2);
        right_coeff = std::sqrt(2) * std::sqrt((1 + pan) / 2);
        break;
      case SQUARE_3_CENTER:
        left_coeff = std::sqrt((1 - pan) / 2);
        right_coeff = std::sqrt((1 + pan) / 2);
        break;
      case LINEAR_TAPER:
        left_coeff = (1 - pan) / 2;
        right_coeff = (1 + pan) / 2;
        break;
      case BALANCE:
        left_coeff = pan < 0 ? 1 : 1 - pan;
        right_coeff = pan > 0 ? 1 : 1 + pan;
        break;
    }
    
    for(std::int64_t i = 0; i < size; ++i)
    {
      outputs[0][i] = static_cast<DataType>(left_coeff * converted_inputs[0][i]);
      outputs[1][i] = static_cast<DataType>(right_coeff * converted_inputs[0][i]);
    }
    
  }
  
  template class PanFilter<std::int16_t>;
  template class PanFilter<std::int32_t>;
  template class PanFilter<std::int64_t>;
  template class PanFilter<float>;
  template class PanFilter<double>;
}
