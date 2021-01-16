/**
 * \file SecondOrderFilter.hxx
 * @see http://abvolt.com/research/publications2.htm
 * @see http://www.music.mcgill.ca/~ich/classes/FiltersChap2.pdf for the allpass filter
 */

#include "SecondOrderFilter.h"

#include <boost/math/constants/constants.hpp>

#include <cassert>
#include <cmath>

namespace ATK
{
  template <typename DataType_>
  SecondOrderCoreCoefficients<DataType_>::SecondOrderCoreCoefficients(gsl::index nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template <typename DataType_>
  SecondOrderBaseCoefficients<DataType_>::SecondOrderBaseCoefficients(gsl::index nb_channels)
    : Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderBaseCoefficients<DataType_>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
  }

  template <typename DataType_>
  void SecondOrderBaseCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename SecondOrderBaseCoefficients<DataType_>::CoeffDataType  SecondOrderBaseCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template<typename DataType_>
  SecondOrderBandPassCoefficients<DataType_>::SecondOrderBandPassCoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderBandPassCoefficients<DataType_>::setup()
  {
    Parent::setup();
    
    CoeffDataType c = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    CoeffDataType d = (1 + std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c);
    CoeffDataType Q_inv = 1 / Q;
    
    coefficients_in[2] = Q_inv * c / d;
    coefficients_in[1] = 0;
    coefficients_in[0] = -Q_inv * c / d;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c) / d;
  }
  
  template <typename DataType_>
  void SecondOrderBandPassCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q can't be negative");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename SecondOrderBandPassCoefficients<DataType_>::CoeffDataType SecondOrderBandPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType_>
  SecondOrderLowPassCoefficients<DataType_>::SecondOrderLowPassCoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderLowPassCoefficients<DataType_>::setup()
  {
    Parent::setup();

    CoeffDataType c = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    CoeffDataType d = (1 + std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c);
    
    coefficients_in[2] = c * c / d;
    coefficients_in[1] = 2 * c * c / d;
    coefficients_in[0] = c * c / d;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c) / d;
  }

  template<typename DataType_>
  SecondOrderHighPassCoefficients<DataType_>::SecondOrderHighPassCoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderHighPassCoefficients<DataType_>::setup()
  {
    Parent::setup();

    CoeffDataType c = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    CoeffDataType d = (1 + std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c);
    
    coefficients_in[2] = 1;
    coefficients_in[1] = -2;
    coefficients_in[0] = 1;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c) / d;
  }

  template<typename DataType_>
  SecondOrderBandPassPeakCoefficients<DataType_>::SecondOrderBandPassPeakCoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderBandPassPeakCoefficients<DataType_>::setup()
  {
    Parent::setup();

    CoeffDataType c = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    CoeffDataType Q_inv = 1 / Q;
    if(gain <= 1)
    {
      CoeffDataType V0 = 1 / gain;
      CoeffDataType d = 1 + V0 * Q_inv * c + c * c;
      
      coefficients_in[2] = (1 + Q_inv * c + c * c) / d;
      coefficients_in[1] = 2 * (c * c - 1) / d;
      coefficients_in[0] = (1 - Q_inv * c + c * c) / d;
      coefficients_out[1] = -2 * (c * c - 1) / d;
      coefficients_out[0] = -(1 - V0 * Q_inv * c + c * c) / d;
    }
    else
    {
      CoeffDataType V0 = gain;
      CoeffDataType d = 1 + Q_inv * c + c * c;
      
      coefficients_in[2] = (1 + V0 * Q_inv * c + c * c) / d;
      coefficients_in[1] = 2 * (c * c - 1) / d;
      coefficients_in[0] = (1 - V0 * Q_inv * c + c * c) / d;
      coefficients_out[1] = -2 * (c * c - 1) / d;
      coefficients_out[0] = -(1 - Q_inv * c + c * c) / d;
    }
  }

  template <typename DataType_>
  void SecondOrderBandPassPeakCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q can't be negative");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename SecondOrderBandPassPeakCoefficients<DataType_>::CoeffDataType SecondOrderBandPassPeakCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template <typename DataType_>
  void SecondOrderBandPassPeakCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  typename SecondOrderBandPassPeakCoefficients<DataType_>::CoeffDataType SecondOrderBandPassPeakCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template<typename DataType_>
  SecondOrderAllPassCoefficients<DataType_>::SecondOrderAllPassCoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderAllPassCoefficients<DataType_>::setup()
  {
    Parent::setup();

    CoeffDataType c = std::tan(boost::math::constants::pi<CoeffDataType>() * Q);
    CoeffDataType d = -std::cos(2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);

    coefficients_in[2] = -c;
    coefficients_in[1] = d * (1 - c);
    coefficients_in[0] = 1;
    coefficients_out[1] = -d * (1 - c);
    coefficients_out[0] = c;
  }

  template <typename DataType_>
  void SecondOrderAllPassCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q can't be negative");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename SecondOrderAllPassCoefficients<DataType_>::CoeffDataType SecondOrderAllPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType_>
  SecondOrderLowShelvingCoefficients<DataType_>::SecondOrderLowShelvingCoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderLowShelvingCoefficients<DataType_>::setup()
  {
    Parent::setup();

    CoeffDataType c = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    if(gain <= 1)
    {
      CoeffDataType V0 = 1 / gain;
      CoeffDataType d = (1 + std::sqrt(static_cast<CoeffDataType>(2.) * V0) * c + V0 * c * c);
      
      coefficients_in[2] = (1 + std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c) / d;
      coefficients_in[1] = 2 * (c * c - 1) / d;
      coefficients_in[0] = (1 - std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c) / d;
      coefficients_out[1] = - 2 * (V0 * c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(static_cast<CoeffDataType>(2.) * V0) * c + V0 * c * c) / d;
    }
    else
    {
      CoeffDataType d = (1 + std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c);
      
      coefficients_in[2] = (1 + std::sqrt(static_cast<CoeffDataType>(2.) * gain) * c + gain * c * c) / d;
      coefficients_in[1] = 2 * (gain * c * c - 1) / d;
      coefficients_in[0] = (1 - std::sqrt(static_cast<CoeffDataType>(2.) * gain) * c + gain * c * c) / d;
      coefficients_out[1] = - 2 * (c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c) / d;
    }
  }

  template <typename DataType_>
  void SecondOrderLowShelvingCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  typename SecondOrderLowShelvingCoefficients<DataType_>::CoeffDataType SecondOrderLowShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template<typename DataType_>
  SecondOrderHighShelvingCoefficients<DataType_>::SecondOrderHighShelvingCoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType>
  void SecondOrderHighShelvingCoefficients<DataType>::setup()
  {
    Parent::setup();

    CoeffDataType c = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    if(gain <= 1)
    {
      CoeffDataType V0 = 1 / gain;
      CoeffDataType d = (V0 + std::sqrt(static_cast<CoeffDataType>(2.) * V0) * c + c * c);
      
      coefficients_in[2] = -(1 + std::sqrt(static_cast<CoeffDataType>(2.0)) * c + c * c) / d;
      coefficients_in[1] = -2 * (c * c - 1) / d;
      coefficients_in[0] = -(1 - std::sqrt(static_cast<CoeffDataType>(2.0)) * c + c * c) / d;
      coefficients_out[1] = - 2 * (c * c - V0) / d;
      coefficients_out[0] = - (V0 - std::sqrt(static_cast<CoeffDataType>(2.0) * V0) * c + c * c) / d;
    }
    else
    {
      CoeffDataType d = (1 + std::sqrt(static_cast<CoeffDataType>(2.)) * c + c * c);
      
      coefficients_in[2] = -(gain + std::sqrt(static_cast<CoeffDataType>(2.0) * gain) * c + c * c) / d;
      coefficients_in[1] = -2 * (c * c - gain) / d;
      coefficients_in[0] = -(gain - std::sqrt(static_cast<CoeffDataType>(2.0) * gain) * c + c * c) / d;
      coefficients_out[1] = - 2 * (c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(static_cast<CoeffDataType>(2.0)) * c + c * c) / d;
    }
  }
  
  template<typename DataType_>
  void SecondOrderHighShelvingCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  typename SecondOrderHighShelvingCoefficients<DataType_>::CoeffDataType SecondOrderHighShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }
}
