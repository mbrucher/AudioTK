/**
 * \file RobertBristowJohnsonFilter.cpp
 */

#include <boost/math/constants/constants.hpp>

#include "RobertBristowJohnsonFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  RobertBristowJohnsonLowPassCoefficients<DataType>::RobertBristowJohnsonLowPassCoefficients(int nb_channels)
    :Parent(nb_channels), Q(1)
  {
  }

  template <typename DataType>
  void RobertBristowJohnsonLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    DataType w0 = 2 * boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate;
    DataType cosw0 = std::cos(w0);
    DataType alpha = std::sin(w0) / (2 * Q);

    coefficients_in[2] = (1 - cosw0)/2 / (1 + alpha);
    coefficients_in[1] = (1 - cosw0) / (1 + alpha);
    coefficients_in[0] = (1 - cosw0) / 2 / (1 + alpha);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }

  template <typename DataType_>
  void RobertBristowJohnsonLowPassCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ RobertBristowJohnsonLowPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType>
  RobertBristowJohnsonHighPassCoefficients<DataType>::RobertBristowJohnsonHighPassCoefficients(int nb_channels)
    :Parent(nb_channels), Q(1)
  {
  }

  template <typename DataType>
  void RobertBristowJohnsonHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    DataType w0 = 2 * boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate;
    DataType cosw0 = std::cos(w0);
    DataType alpha = std::sin(w0) / (2 * Q);

    coefficients_in[2] = (1 + cosw0) / 2 / (1 + alpha);
    coefficients_in[1] = -(1 + cosw0) / (1 + alpha);
    coefficients_in[0] = (1 + cosw0) / 2 / (1 + alpha);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }

  template <typename DataType_>
  void RobertBristowJohnsonHighPassCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ RobertBristowJohnsonHighPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template class RobertBristowJohnsonLowPassCoefficients<float>;
  template class RobertBristowJohnsonLowPassCoefficients<double>;
  template class RobertBristowJohnsonHighPassCoefficients<float>;
  template class RobertBristowJohnsonHighPassCoefficients<double>;
  
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<double> >;
}
