/**
 * \file ToneStackFilter.hxx
 */

#include "ToneStackFilter.h"

#include <boost/math/tools/polynomial.hpp>

namespace ATK
{
  template<typename DataType>
  ToneStackCoefficients<DataType>::ToneStackCoefficients(gsl::index nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType>
  ToneStackCoefficients<DataType>::ToneStackCoefficients(ToneStackCoefficients&& other)
  :Parent(std::move(other)), R1(other.R1), R2(other.R2), R3(other.R3), R4(other.R4), C1(other.C1), C2(other.C2), C3(other.C3), low(other.low), middle(other.middle), high(other.high)
  {
    
  }

  template<typename DataType>
  void ToneStackCoefficients<DataType>::setup()
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
    
    b = poly2 * poly2 * poly1 * (high*C1*R1 + middle*C3*R3 + low*(C1*R2 + C2*R2) + (C1*R3 + C2*R3));
    b += poly2 * poly1 * poly1 * (high*(C1*C2*R1*R4 + C1*C3*R1*R4) - middle*middle*(C1*C3*R3*R3 + C2*C3*R3*R3) + middle*(C1*C3*R1*R3 + C1*C3*R3*R3 + C2*C3*R3*R3)
      + low*(C1*C2*R1*R2 + C1*C2*R2*R4 + C1*C3*R2*R4) + low*middle*(C1*C3*R2*R3 + C2*C3*R2*R3)
      + (C1*C2*R1*R3 + C1*C2*R3*R4 + C1*C3*R3*R4));
    b += poly1 * poly1 * poly1 * (low*middle*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4) - middle*middle*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
      + middle*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4) + high*C1*C2*C3*R1*R3*R4 - high*middle*C1*C2*C3*R1*R3*R4
      + high*low*C1*C2*C3*R1*R2*R4);

    a = poly2 * poly2 * poly2;
    a += poly2 * poly2 * poly1 * ((C1*R1 + C1*R3 + C2*R3 + C2*R4 + C3*R4) + middle*C3*R3 + low*(C1*R2 + C2*R2));
    a += poly2 * poly1 * poly1 * (middle*(C1*C3*R1*R3 - C2*C3*R3*R4 + C1*C3*R3*R3 + C2*C3*R3*R3)
      + low*middle*(C1*C3*R2*R3 + C2*C3*R2*R3) - middle*middle*(C1*C3*R3*R3 + C2*C3*R3*R3) + low*(C1*C2*R2*R4 + C1*C2*R1*R2 + C1*C3*R2*R4 + C2*C3*R2*R4)
      + (C1*C2*R1*R4 + C1*C3*R1*R4 + C1*C2*R3*R4 + C1*C2*R1*R3 + C1*C3*R3*R4 + C2*C3*R3*R4));
    a += poly1 * poly1 * poly1 * (low*middle*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4) - middle*middle*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
      + middle*(C1*C2*C3*R3*R3*R4 + C1*C2*C3*R1*R3*R3 - C1*C2*C3*R1*R3*R4)
      + low*C1*C2*C3*R1*R2*R4 + C1*C2*C3*R1*R3*R4);

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
  void ToneStackCoefficients<DataType_>::set_low(CoeffDataType low)
  {
    if(low < 0 || low > 1)
    {
      throw std::out_of_range("Low is outside the interval [0,1]");
    }
    this->low = low;

    setup();
  }
  
  template<typename DataType_>
  typename ToneStackCoefficients<DataType_>::CoeffDataType ToneStackCoefficients<DataType_>::get_low() const
  {
    return low;
  }

  template<typename DataType_>
  void ToneStackCoefficients<DataType_>::set_middle(CoeffDataType middle)
  {
    if(middle < 0 || middle > 1)
    {
      throw std::out_of_range("Middle is outside the interval [0,1]");
    }
    this->middle = middle;

    setup();
  }

  template<typename DataType_>
  typename ToneStackCoefficients<DataType_>::CoeffDataType ToneStackCoefficients<DataType_>::get_middle() const
  {
    return middle;
  }


  template<typename DataType_>
  void ToneStackCoefficients<DataType_>::set_high(CoeffDataType high)
  {
    if(high < 0 || high > 1)
    {
      throw std::out_of_range("high is outside the interval [0,1]");
    }
    this->high = high;

    setup();
  }

  template<typename DataType_>
  typename ToneStackCoefficients<DataType_>::CoeffDataType ToneStackCoefficients<DataType_>::get_high() const
  {
    return high;
  }

  template<typename DataType>
  IIRFilter<ToneStackCoefficients<DataType> > ToneStackCoefficients<DataType>::buildBassmanStack()
  {
    IIRFilter<ToneStackCoefficients<DataType> > filter;
    filter.set_coefficients(static_cast<CoeffDataType>(250e3), static_cast<CoeffDataType>(1e6), static_cast<CoeffDataType>(25e3), static_cast<CoeffDataType>(45e3),
      static_cast<CoeffDataType>(250e-12), static_cast<CoeffDataType>(20e-9), static_cast<CoeffDataType>(20e-9));
    return std::move(filter);
  }

  template<typename DataType>
  IIRFilter<ToneStackCoefficients<DataType> > ToneStackCoefficients<DataType>::buildJCM800Stack()
  {
    IIRFilter<ToneStackCoefficients<DataType> > filter;
    filter.set_coefficients(static_cast<CoeffDataType>(220e3), static_cast<CoeffDataType>(1e6), static_cast<CoeffDataType>(22e3), static_cast<CoeffDataType>(33e3),
      static_cast<CoeffDataType>(470e-12), static_cast<CoeffDataType>(22e-9), static_cast<CoeffDataType>(22e-9));
    return std::move(filter);
  }

  template<typename DataType_>
  void ToneStackCoefficients<DataType_>::set_coefficients(CoeffDataType R1, CoeffDataType R2, CoeffDataType R3, CoeffDataType R4, CoeffDataType C1, CoeffDataType C2, CoeffDataType C3)
  {
    this->R1 = R1;
    this->R2 = R2;
    this->R3 = R3;
    this->R4 = R4;
    this->C1 = C1;
    this->C2 = C2;
    this->C3 = C3;
  }
}
