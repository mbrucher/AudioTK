/**
 * \file LinkwitzRileyFilter.cpp
 */

#include <boost/math/tools/polynomial.hpp>

#include "LinkwitzRileyFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  LinkwitzRileyLowPassCoefficients<DataType>::LinkwitzRileyLowPassCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType>
  void LinkwitzRileyLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    DataType omega = boost::math::constants::pi<DataType>() * cut_frequency;
    DataType kappa = omega / std::tan(omega / input_sampling_rate);
    DataType delta = kappa * kappa + omega * omega + 2 * kappa * omega;

    coefficients_in[2] = omega * omega / delta;
    coefficients_in[1] = 2 * omega * omega / delta;
    coefficients_in[0] = omega * omega / delta;
    coefficients_out[1] = 2 * (kappa * kappa - omega * omega) / delta;
    coefficients_out[0] = -(omega * omega + kappa * kappa - 2 * kappa * omega) / delta;
  }

  template<typename DataType>
  LinkwitzRileyHighPassCoefficients<DataType>::LinkwitzRileyHighPassCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType>
  void LinkwitzRileyHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    DataType omega = boost::math::constants::pi<DataType>() * cut_frequency;
    DataType kappa = omega / std::tan(omega / input_sampling_rate);
    DataType delta = kappa * kappa + omega * omega + 2 * kappa * omega;
    
    coefficients_in[2] = kappa * kappa / delta;
    coefficients_in[1] = - 2 * kappa * kappa / delta;
    coefficients_in[0] = kappa * kappa / delta;
    coefficients_out[1] = 2 * (kappa * kappa - omega * omega) / delta;
    coefficients_out[0] = -(omega * omega + kappa * kappa - 2 * kappa * omega) / delta;
  }

  template<typename DataType>
  LinkwitzRiley4LowPassCoefficients<DataType>::LinkwitzRiley4LowPassCoefficients(unsigned int nb_channels)
  :Parent(nb_channels)
  {
  }
  
  template <typename DataType>
  void LinkwitzRiley4LowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    auto wc=2*boost::math::constants::pi<DataType>() * cut_frequency;
    auto wc2=wc*wc;
    auto wc3=wc2*wc;
    auto wc4=wc2*wc2;
    auto k=wc/std::tan(wc/2/input_sampling_rate);
    auto k2=k*k;
    auto k3=k2*k;
    auto k4=k2*k2;
    auto sqrt2=std::sqrt(DataType(2));
    auto sq_tmp1=sqrt2*wc3*k;
    auto sq_tmp2=sqrt2*wc*k3;
    auto a_tmp=4*wc2*k2+2*sq_tmp1+k4+2*sq_tmp2+wc4;
    
    coefficients_out[3]=(4*(wc4+sq_tmp1-k4-sq_tmp2))/a_tmp;
    coefficients_out[2]=(6*wc4-8*wc2*k2+6*k4)/a_tmp;
    coefficients_out[1]=(4*(wc4-sq_tmp1+sq_tmp2-k4))/a_tmp;
    coefficients_out[0]=(k4-2*sq_tmp1+wc4-2*sq_tmp2+4*wc2*k2)/a_tmp;
    
    coefficients_in[0] = coefficients_in[4] = wc4/a_tmp;
    coefficients_in[1] = coefficients_in[3] = 4*wc4/a_tmp;
    coefficients_in[2] = 6*wc4/a_tmp;
  }
  
  template<typename DataType>
  LinkwitzRiley4HighPassCoefficients<DataType>::LinkwitzRiley4HighPassCoefficients(unsigned int nb_channels)
  :Parent(nb_channels)
  {
  }
  
  template <typename DataType>
  void LinkwitzRiley4HighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    auto wc=2*boost::math::constants::pi<DataType>() * cut_frequency;
    auto wc2=wc*wc;
    auto wc3=wc2*wc;
    auto wc4=wc2*wc2;
    auto k=wc/std::tan(wc/2/input_sampling_rate);
    auto k2=k*k;
    auto k3=k2*k;
    auto k4=k2*k2;
    auto sqrt2=std::sqrt(DataType(2));
    auto sq_tmp1=sqrt2*wc3*k;
    auto sq_tmp2=sqrt2*wc*k3;
    auto a_tmp=4*wc2*k2+2*sq_tmp1+k4+2*sq_tmp2+wc4;
    
    coefficients_out[3]=(4*(wc4+sq_tmp1-k4-sq_tmp2))/a_tmp;
    coefficients_out[2]=(6*wc4-8*wc2*k2+6*k4)/a_tmp;
    coefficients_out[1]=(4*(wc4-sq_tmp1+sq_tmp2-k4))/a_tmp;
    coefficients_out[0]=(k4-2*sq_tmp1+wc4-2*sq_tmp2+4*wc2*k2)/a_tmp;
    
    coefficients_in[0] = coefficients_in[4] = k4/a_tmp;
    coefficients_in[1] = coefficients_in[3] = -4*k4/a_tmp;
    coefficients_in[2] = 6*k4/a_tmp;
  }

  template class LinkwitzRileyLowPassCoefficients<float>;
  template class LinkwitzRileyLowPassCoefficients<double>;
  template class LinkwitzRileyHighPassCoefficients<float>;
  template class LinkwitzRileyHighPassCoefficients<double>;
  template class LinkwitzRiley4LowPassCoefficients<float>;
  template class LinkwitzRiley4LowPassCoefficients<double>;
  template class LinkwitzRiley4HighPassCoefficients<float>;
  template class LinkwitzRiley4HighPassCoefficients<double>;
  
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRiley4LowPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRiley4LowPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRiley4HighPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRiley4HighPassCoefficients<double> >;
}
