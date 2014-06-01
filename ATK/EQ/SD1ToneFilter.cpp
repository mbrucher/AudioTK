/**
 * \file SD1ToneFilter.cpp
 */

#include "SD1ToneFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  SD1ToneCoefficients<DataType>::SD1ToneCoefficients()
  :TypedBaseFilter<DataType>(1, 1), R1(1000), R2(22000), R3(470), R4(10000),
    C1(0.000000018), C2(0.000000027), C3(0.00000001), alpha(1), in_order(2), out_order(2)
  {
  }

  template<typename DataType>
  void SD1ToneCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);

    DataType tempm[2] = {-2 * input_sampling_rate, 2 * input_sampling_rate};
    DataType tempp[2] = {1, 1};
    boost::math::tools::polynomial<DataType> poly1(tempm, 1);
    boost::math::tools::polynomial<DataType> poly2(tempp, 1);

    boost::math::tools::polynomial<DataType> b;
    boost::math::tools::polynomial<DataType> a;
    
    b += poly2 * poly2;
    b += poly2 * poly1 * (C2*R3+R4*C3-alpha*(1-alpha)*R2*C2-alpha*C2*R4);
    b += poly1 * poly1 * (C3*R4*(R3*C2-alpha*(1-alpha)*R2*C2));

    a += poly2 * poly2;
    a += poly2 * poly1 * (C2*R3+R1*C1-alpha*(1-alpha)*R2*C2-(1-alpha)*C2*R1);
    a += poly1 * poly1 * (C1*R1*(R3*C2-alpha*(1-alpha)*R2*C2));

    for(int i = 0; i < in_order + 1; ++i)
    {
      coefficients_in[i] = b[i];
    }
    for(int i = 0; i < out_order; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }

  template<typename DataType>
  void SD1ToneCoefficients<DataType>::set_tone(DataType alpha)
  {
    if(alpha < 0 || alpha > 1)
    {
      throw std::range_error("Tone is outside the interval [0,1]");
    }
    this->alpha = alpha;

    setup();
  }
  
  template<typename DataType>
  typename SD1ToneCoefficients<DataType>::DataType SD1ToneCoefficients<DataType>::get_tone() const
  {
    return alpha;
  }

  template class SD1ToneCoefficients<float>;
  template class SD1ToneCoefficients<double>;
  
  template class IIRFilter<SD1ToneCoefficients<float> >;
  template class IIRFilter<SD1ToneCoefficients<double> >;
}
