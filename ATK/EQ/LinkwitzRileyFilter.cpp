/**
 * \file LinkwitzRileyFilter.cpp
 */

#include "LinkwitzRileyFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  LowPassLinkwitzRileyFilterCoefficients<DataType>::LowPassLinkwitzRileyFilterCoefficients(int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType>
  void LowPassLinkwitzRileyFilterCoefficients<DataType>::setup()
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
  HighPassLinkwitzRileyFilterCoefficients<DataType>::HighPassLinkwitzRileyFilterCoefficients(int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType>
  void HighPassLinkwitzRileyFilterCoefficients<DataType>::setup()
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

  template class LowPassLinkwitzRileyFilterCoefficients<float>;
  template class LowPassLinkwitzRileyFilterCoefficients<double>;
  template class HighPassLinkwitzRileyFilterCoefficients<float>;
  template class HighPassLinkwitzRileyFilterCoefficients<double>;
  
  template class IIRFilter<LowPassLinkwitzRileyFilterCoefficients<float> >;
  template class IIRFilter<LowPassLinkwitzRileyFilterCoefficients<double> >;
  template class IIRFilter<HighPassLinkwitzRileyFilterCoefficients<float> >;
  template class IIRFilter<HighPassLinkwitzRileyFilterCoefficients<double> >;
}
