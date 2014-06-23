/**
 * \file SD1ToneFilter.cpp
 */

#include "SD1ToneFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  SD1ToneCoefficients<DataType>::SD1ToneCoefficients(int nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels), R1(10e3), R2(22e3), R3(470), R4(10e3),
    C1(0.018e-6), C2(0.027e-6), C3(0.01e-6), alpha(1)
  {
  }

  template<typename DataType>
  void SD1ToneCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);

    DataType tempm[2] = {static_cast<DataType>(-2 * input_sampling_rate), static_cast<DataType>(2 * input_sampling_rate)};
    DataType tempp[2] = {static_cast<DataType>(1), static_cast<DataType>(1)};
    boost::math::tools::polynomial<DataType> poly1(tempm, 1);
    boost::math::tools::polynomial<DataType> poly2(tempp, 1);

    boost::math::tools::polynomial<DataType> b;
    boost::math::tools::polynomial<DataType> a;
    
    b += poly2 * poly2;
    b += poly2 * poly1 * (C2*R3+R4*C3+alpha*(1-alpha)*R2*C2+alpha*C2*R4);
    b += poly1 * poly1 * (C3*R4*(R3*C2+alpha*(1-alpha)*R2*C2));

    a += poly2 * poly2;
    a += poly2 * poly1 * (C2*R3+R1*C1+alpha*(1-alpha)*R2*C2+(1-alpha)*C2*R1);
    a += poly1 * poly1 * (C1*R1*(R3*C2+alpha*(1-alpha)*R2*C2));

    for(int i = 0; i < in_order + 1; ++i)
    {
      coefficients_in[i] = b[i] / a[out_order];
    }
    for(int i = 0; i < out_order; ++i)
    {
      coefficients_out[i] = -a[i] / a[out_order];
    }
  }

  template<typename DataType>
  void SD1ToneCoefficients<DataType>::set_tone(DataType alpha)
  {
    if(alpha < 0 || alpha > 1)
    {
      throw std::out_of_range("Tone is outside the interval [0,1]");
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
