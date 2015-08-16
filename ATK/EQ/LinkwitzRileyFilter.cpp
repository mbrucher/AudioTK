/**
 * \file LinkwitzRileyFilter.cpp
 */

#include <boost/math/tools/polynomial.hpp>

#include "LinkwitzRileyFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  LinkwitzRileyLowPassCoefficients<DataType>::LinkwitzRileyLowPassCoefficients(int nb_channels)
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
  LinkwitzRileyHighPassCoefficients<DataType>::LinkwitzRileyHighPassCoefficients(int nb_channels)
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

  template class LinkwitzRileyLowPassCoefficients<float>;
  template class LinkwitzRileyLowPassCoefficients<double>;
  template class LinkwitzRileyHighPassCoefficients<float>;
  template class LinkwitzRileyHighPassCoefficients<double>;
  
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRileyLowPassCoefficients<double> >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<float> >;
  template class IIRFilter<LinkwitzRileyHighPassCoefficients<double> >;
}
