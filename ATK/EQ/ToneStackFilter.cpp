/**
 * \file ToneStackFilter.cpp
 */

#include <boost/math/tools/polynomial.hpp>

#include "ToneStackFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  ToneStackFilterCoefficients<DataType>::ToneStackFilterCoefficients(int nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels), R1(0), R2(0), R3(0), R4(0), C1(0), C2(0), C3(0), low(.5), middle(.5), high(.5)
  {
  }
  
  template<typename DataType>
  ToneStackFilterCoefficients<DataType>::ToneStackFilterCoefficients(ToneStackFilterCoefficients&& other)
  :Parent(std::move(other)), R1(other.R1), R2(other.R2), R3(other.R3), R4(other.R4), C1(other.C1), C2(other.C2), C3(other.C3), low(other.low), middle(other.middle), high(other.high)
  {
    
  }


  template<typename DataType>
  void ToneStackFilterCoefficients<DataType>::setup()
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

    for(int i = 0; i < in_order + 1; ++i)
    {
      coefficients_in[i] = b[i] / a[out_order];
    }
    for(int i = 0; i < out_order; ++i)
    {
      coefficients_out[i] = -a[i] / a[out_order];
    }
  }

  template<typename DataType_>
  void ToneStackFilterCoefficients<DataType_>::set_low(DataType_ low)
  {
    if(low < 0 || low > 1)
    {
      throw std::out_of_range("Low is outside the interval [0,1]");
    }
    this->low = low;

    setup();
  }
  
  template<typename DataType_>
  DataType_ ToneStackFilterCoefficients<DataType_>::get_low() const
  {
    return low;
  }

  template<typename DataType_>
  void ToneStackFilterCoefficients<DataType_>::set_middle(DataType_ middle)
  {
    if(middle < 0 || middle > 1)
    {
      throw std::out_of_range("Middle is outside the interval [0,1]");
    }
    this->middle = middle;

    setup();
  }

  template<typename DataType_>
  DataType_ ToneStackFilterCoefficients<DataType_>::get_middle() const
  {
    return middle;
  }


  template<typename DataType_>
  void ToneStackFilterCoefficients<DataType_>::set_high(DataType_ high)
  {
    if(high < 0 || high > 1)
    {
      throw std::out_of_range("high is outside the interval [0,1]");
    }
    this->high = high;

    setup();
  }

  template<typename DataType_>
  DataType_ ToneStackFilterCoefficients<DataType_>::get_high() const
  {
    return high;
  }


  template<typename DataType>
  IIRFilter<ToneStackFilterCoefficients<DataType> >&& ToneStackFilterCoefficients<DataType>::buildBassmanStack()
  {
    IIRFilter<ToneStackFilterCoefficients<DataType> > filter;
    filter.set_coefficients(static_cast<DataType>(250e3), static_cast<DataType>(1e6), static_cast<DataType>(25e3), static_cast<DataType>(45e3),
      static_cast<DataType>(250e-12), static_cast<DataType>(20e-9), static_cast<DataType>(20e-9));
    return std::move(filter);
  }

  template<typename DataType>
  IIRFilter<ToneStackFilterCoefficients<DataType> >&& ToneStackFilterCoefficients<DataType>::buildJCM800Stack()
  {
    IIRFilter<ToneStackFilterCoefficients<DataType> > filter;
    filter.set_coefficients(static_cast<DataType>(220e3), static_cast<DataType>(1e6), static_cast<DataType>(22e3), static_cast<DataType>(33e3),
      static_cast<DataType>(470e-12), static_cast<DataType>(22e-9), static_cast<DataType>(22e-9));
    return std::move(filter);
  }

  template<typename DataType_>
  void ToneStackFilterCoefficients<DataType_>::set_coefficients( DataType R1, DataType R2, DataType R3, DataType R4, DataType C1, DataType C2, DataType C3 )
  {
    this->R1 = R1;
    this->R2 = R2;
    this->R3 = R3;
    this->R4 = R4;
    this->C1 = C1;
    this->C2 = C2;
    this->C3 = C3;
  }

  template class ToneStackFilterCoefficients<float>;
  template class ToneStackFilterCoefficients<double>;
  
  template class IIRFilter<ToneStackFilterCoefficients<float> >;
  template class IIRFilter<ToneStackFilterCoefficients<double> >;
}
