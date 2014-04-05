/**
 * \file ButterworthFilter.cpp
 */

#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/polynomial.hpp>

#include "ButterworthFilter.h"
#include "IIRFilter.h"

namespace
{
  template<typename DataType>
  void create_default_coeffs(int order, DataType Wn, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    DataType coeff = 1 / Wn;
    DataType temp1[2] = {1,-1};
    DataType temp2[2] = {1,+1};
    boost::math::tools::polynomial<DataType> poly1(temp1, 1);
    boost::math::tools::polynomial<DataType> poly2(temp2, 1);
    
    for (int i = 0; i < order+1; ++i)
    {
      coefficients_in[i] = boost::math::binomial_coefficient<DataType>(order, i);
    }
    
    boost::math::tools::polynomial<DataType> poly(1);
    
    if(order % 2 != 0)
    {
      poly = poly2 + coeff * poly1;
    }
    
    for(int i = 1; i <= order/2; ++i)
    {
      boost::math::tools::polynomial<DataType> polytemp = coeff * coeff * poly1 * poly1;
      polytemp -= 2 * coeff * std::cos((2. * i + order - 1) / (2 * order) * boost::math::constants::pi<DataType>()) * poly1 * poly2;
      polytemp += poly2 * poly2;
      
      poly *= polytemp;
    }
    
    for (int i = 1; i < poly.size(); ++i)
    {
      coefficients_out[order - i] = - poly[i] / poly[0];
    }
    for (int i = 0; i < order+1; ++i)
    {
      coefficients_in[order - i] /= poly[0];
    }
  }
}

namespace ATK
{
  template <typename DataType>
  ButterworthLowPassCoefficients<DataType>::ButterworthLowPassCoefficients()
  :Parent(1, 1), in_order(1), out_order(1)
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
  void ButterworthLowPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_coeffs(in_order, (boost::math::constants::pi<DataType>() * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
  }

  template <typename DataType>
  ButterworthHighPassCoefficients<DataType>::ButterworthHighPassCoefficients()
  :Parent(1, 1), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType>
  typename ButterworthHighPassCoefficients<DataType>::DataType ButterworthHighPassCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_coeffs(in_order, 2 * boost::math::constants::pi<DataType>() * (1 - DataType(cut_frequency) / (input_sampling_rate / 2)), coefficients_in, coefficients_out);
    /*for(int i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }*/
  }

  template class ButterworthLowPassCoefficients<float>;
  template class ButterworthLowPassCoefficients<double>;
  template class ButterworthHighPassCoefficients<float>;
  template class ButterworthHighPassCoefficients<double>;
  
  template class IIRFilter<ButterworthLowPassCoefficients<float> >;
  template class IIRFilter<ButterworthLowPassCoefficients<double> >;
  template class IIRFilter<ButterworthHighPassCoefficients<float> >;
  template class IIRFilter<ButterworthHighPassCoefficients<double> >;

}
