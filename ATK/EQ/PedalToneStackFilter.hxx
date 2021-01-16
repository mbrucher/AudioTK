/**
 * \file PedalToneStackFilter.hxx
 */

#include "PedalToneStackFilter.h"

#include <boost/math/tools/polynomial.hpp>

namespace ATK
{
  template<typename DataType>
  SD1ToneCoefficients<DataType>::SD1ToneCoefficients(gsl::index nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels)
  {
  }

  template<typename DataType>
  void SD1ToneCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);

    CoeffDataType tempm[2] = {static_cast<CoeffDataType>(-2) * input_sampling_rate, static_cast<CoeffDataType>(2) * input_sampling_rate};
    CoeffDataType tempp[2] = {static_cast<CoeffDataType>(1), static_cast<CoeffDataType>(1)};
    boost::math::tools::polynomial<CoeffDataType> poly1(tempm, 1);
    boost::math::tools::polynomial<CoeffDataType> poly2(tempp, 1);

    boost::math::tools::polynomial<CoeffDataType> b;
    boost::math::tools::polynomial<CoeffDataType> a;
    
    b += poly2 * poly2;
    b += poly2 * poly1 * (C2*R3+R4*C3+alpha*(1-alpha)*R2*C2+alpha*C2*R4);
    b += poly1 * poly1 * (C3*R4*(R3*C2+alpha*(1-alpha)*R2*C2));

    a += poly2 * poly2;
    a += poly2 * poly1 * (C2*R3+R1*C1+alpha*(1-alpha)*R2*C2+(1-alpha)*C2*R1);
    a += poly1 * poly1 * (C1*R1*(R3*C2+alpha*(1-alpha)*R2*C2));

    for(gsl::index i = 0; i < in_order + 1; ++i)
    {
      coefficients_in[i] = b[i] / a[out_order];
    }
    for(gsl::index i = 0; i < out_order; ++i)
    {
      coefficients_out[i] = -a[i] / a[out_order];
    }
  }

  template<typename DataType_>
  void SD1ToneCoefficients<DataType_>::set_tone(CoeffDataType alpha)
  {
    if(alpha < 0 || alpha > 1)
    {
      throw std::out_of_range("Tone is outside the interval [0,1]");
    }
    this->alpha = alpha;

    setup();
  }
  
  template<typename DataType_>
  typename SD1ToneCoefficients<DataType_>::CoeffDataType SD1ToneCoefficients<DataType_>::get_tone() const
  {
    return alpha;
  }

  template<typename DataType>
  TS9ToneCoefficients<DataType>::TS9ToneCoefficients(gsl::index nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType>
  void TS9ToneCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    CoeffDataType tempm[2] = {static_cast<CoeffDataType>(-2) * input_sampling_rate, static_cast<CoeffDataType>(2) * input_sampling_rate};
    CoeffDataType tempp[2] = {static_cast<CoeffDataType>(1), static_cast<CoeffDataType>(1)};
    boost::math::tools::polynomial<CoeffDataType> poly1(tempm, 1);
    boost::math::tools::polynomial<CoeffDataType> poly2(tempp, 1);
    
    boost::math::tools::polynomial<CoeffDataType> b;
    boost::math::tools::polynomial<CoeffDataType> a;
    
    b += poly2 * poly2 * R2;
    b += poly2 * poly1 * (alpha * C2 * R2 * R3 + alpha * (1-alpha) * C2 * P * R2 + R2 * R4 * C2);
    
    a += poly2 * poly2 * (R2 + R1);
    a += poly2 * poly1 * ((1-alpha) * C2 * (alpha * P * R2 + R1 * alpha * P + R1 * R2) + R4 * C2 * (R2 + R1) + R1 * C1 * R2);
    a += poly1 * poly1 * (C2 * R4 * C1 * R2 * R1 + (1-alpha) * C2 * R1 * P * C1 * R2);
    
    for(gsl::index i = 0; i < in_order + 1; ++i)
    {
      coefficients_in[i] = b[i] / a[out_order];
    }
    for(gsl::index i = 0; i < out_order; ++i)
    {
      coefficients_out[i] = -a[i] / a[out_order];
    }
  }
  
  template<typename DataType_>
  void TS9ToneCoefficients<DataType_>::set_tone(CoeffDataType alpha)
  {
    if(alpha < 0 || alpha > 1)
    {
      throw std::out_of_range("Tone is outside the interval [0,1]");
    }
    this->alpha = alpha;
    
    setup();
  }
  
  template<typename DataType_>
  typename TS9ToneCoefficients<DataType_>::CoeffDataType TS9ToneCoefficients<DataType_>::get_tone() const
  {
    return alpha;
  }
}
