/**
 * \file ButterworthFilter.cpp
 */

#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/polynomial.hpp>

#include "ButterworthFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template <typename DataType>
  ButterworthLowPassCoefficients<DataType>::ButterworthLowPassCoefficients()
  :Parent(1, 1)
  {
  }
  
  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }

  template <typename DataType>
  typename ButterworthLowPassCoefficients<DataType>::DataType ButterworthLowPassCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::setup()
  {
    DataType coeff = input_sampling_rate / (boost::math::constants::pi<DataType>() * cut_frequency);
    DataType temp1[2] = {1,-1};
    DataType temp2[2] = {1,+1};
    boost::math::tools::polynomial<DataType> poly1(temp1, 1);
    boost::math::tools::polynomial<DataType> poly2(temp2, 1);
    
    for (int i = 0; i < in_order+1; ++i)
    {
      coefficients_in[i] = boost::math::binomial_coefficient<DataType>(in_order, i);
    }
    
    boost::math::tools::polynomial<DataType> poly(1);
    
    if(out_order % 2 != 0)
    {
      poly = poly2 + coeff * poly1;
    }
    
    for(int i = 1; i <= out_order/2; ++i)
    {
      boost::math::tools::polynomial<DataType> polytemp = coeff * coeff * poly1 * poly1;
      polytemp -= 2 * coeff * std::cos((2. * i + out_order - 1) / (2 * out_order) * boost::math::constants::pi<DataType>()) * poly1 * poly2;
      polytemp += poly2 * poly2;
      
      poly *= polytemp;
    }
    
    for (int i = 0; i < poly.size(); ++i)
    {
      coefficients_out[out_order - i] = poly[i] / poly[0];
    }
    for (int i = 0; i < in_order+1; ++i)
    {
      coefficients_in[i] /= poly[0];
    }
  }

  template class ButterworthLowPassCoefficients<float>;
  template class ButterworthLowPassCoefficients<double>;
  
  template class IIRFilter<ButterworthLowPassCoefficients<float> >;
  template class IIRFilter<ButterworthLowPassCoefficients<double> >;

}
