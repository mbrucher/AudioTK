/**
 * \file SecondOrderFilter.cpp
 * @see http://abvolt.com/research/publications2.htm
 * @see http://www.music.mcgill.ca/~ich/classes/FiltersChap2.pdf for the allpass filter
 */

#include "SecondOrderFilter.h"
#include "IIRFilter.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType_>
  SecondOrderBaseCoefficients<DataType_>::SecondOrderBaseCoefficients(unsigned int nb_channels)
    :Parent(nb_channels, nb_channels)
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
  void SecondOrderBaseCoefficients<DataType_>::set_cut_frequency(DataType_ cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  DataType_ SecondOrderBaseCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template<typename DataType_>
  SecondOrderBandPassCoefficients<DataType_>::SecondOrderBandPassCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderBandPassCoefficients<DataType_>::setup()
  {
    Parent::setup();
    
    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);
    DataType Q_inv = 1 / Q;
    
    coefficients_in[2] = Q_inv * c / d;
    coefficients_in[1] = 0;
    coefficients_in[0] = -Q_inv * c / d;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d;
  }
  
  template <typename DataType_>
  void SecondOrderBandPassCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ SecondOrderBandPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType_>
  SecondOrderLowPassCoefficients<DataType_>::SecondOrderLowPassCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderLowPassCoefficients<DataType_>::setup()
  {
    Parent::setup();

    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);
    
    coefficients_in[2] = c * c / d;
    coefficients_in[1] = 2 * c * c / d;
    coefficients_in[0] = c * c / d;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d;
  }

  template<typename DataType_>
  SecondOrderHighPassCoefficients<DataType_>::SecondOrderHighPassCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderHighPassCoefficients<DataType_>::setup()
  {
    Parent::setup();

    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);
    
    coefficients_in[2] = 1;
    coefficients_in[1] = -2;
    coefficients_in[0] = 1;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d;
  }

  template<typename DataType_>
  SecondOrderBandPassPeakCoefficients<DataType_>::SecondOrderBandPassPeakCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderBandPassPeakCoefficients<DataType_>::setup()
  {
    Parent::setup();

    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    DataType Q_inv = 1 / Q;
    if(gain <= 1)
    {
      DataType V0 = 1 / gain;
      DataType d = 1 + V0 * Q_inv * c + c * c;
      
      coefficients_in[2] = (1 + Q_inv * c + c * c) / d;
      coefficients_in[1] = 2 * (c * c - 1) / d;
      coefficients_in[0] = (1 - Q_inv * c + c * c) / d;
      coefficients_out[1] = -2 * (c * c - 1) / d;
      coefficients_out[0] = -(1 - V0 * Q_inv * c + c * c) / d;
    }
    else
    {
      DataType V0 = gain;
      DataType d = 1 + Q_inv * c + c * c;
      
      coefficients_in[2] = (1 + V0 * Q_inv * c + c * c) / d;
      coefficients_in[1] = 2 * (c * c - 1) / d;
      coefficients_in[0] = (1 - V0 * Q_inv * c + c * c) / d;
      coefficients_out[1] = -2 * (c * c - 1) / d;
      coefficients_out[0] = -(1 - Q_inv * c + c * c) / d;
    }
  }

  template <typename DataType_>
  void SecondOrderBandPassPeakCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ SecondOrderBandPassPeakCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template <typename DataType_>
  void SecondOrderBandPassPeakCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  DataType_ SecondOrderBandPassPeakCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template<typename DataType_>
  SecondOrderAllPassCoefficients<DataType_>::SecondOrderAllPassCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderAllPassCoefficients<DataType_>::setup()
  {
    Parent::setup();

    DataType c = std::tan(boost::math::constants::pi<DataType>() * Q);
    DataType d = -std::cos(2 * boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);

    coefficients_in[2] = -c;
    coefficients_in[1] = d * (1 - c);
    coefficients_in[0] = 1;
    coefficients_out[1] = -d * (1 - c);
    coefficients_out[0] = c;
  }

  template <typename DataType_>
  void SecondOrderAllPassCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ SecondOrderAllPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType_>
  SecondOrderLowShelvingCoefficients<DataType_>::SecondOrderLowShelvingCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType_>
  void SecondOrderLowShelvingCoefficients<DataType_>::setup()
  {
    Parent::setup();

    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    if(gain <= 1)
    {
      DataType V0 = 1 / gain;
      DataType d = (1 + std::sqrt(static_cast<DataType>(2.) * V0) * c + V0 * c * c);
      
      coefficients_in[2] = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d;
      coefficients_in[1] = 2 * (c * c - 1) / d;
      coefficients_in[0] = (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d;
      coefficients_out[1] = - 2 * (V0 * c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(static_cast<DataType>(2.) * V0) * c + V0 * c * c) / d;
    }
    else
    {
      DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);
      
      coefficients_in[2] = (1 + std::sqrt(static_cast<DataType>(2.) * gain) * c + gain * c * c) / d;
      coefficients_in[1] = 2 * (gain * c * c - 1) / d;
      coefficients_in[0] = (1 - std::sqrt(static_cast<DataType>(2.) * gain) * c + gain * c * c) / d;
      coefficients_out[1] = - 2 * (c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d;
    }
  }

  template <typename DataType_>
  void SecondOrderLowShelvingCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  DataType_ SecondOrderLowShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template<typename DataType_>
  SecondOrderHighShelvingCoefficients<DataType_>::SecondOrderHighShelvingCoefficients(unsigned int nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType>
  void SecondOrderHighShelvingCoefficients<DataType>::setup()
  {
    Parent::setup();

    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    if(gain <= 1)
    {
      DataType V0 = 1 / gain;
      DataType d = (V0 + std::sqrt(static_cast<DataType>(2.) * V0) * c + c * c);
      
      coefficients_in[2] = -(1 + std::sqrt(static_cast<DataType>(2.0)) * c + c * c) / d;
      coefficients_in[1] = -2 * (c * c - 1) / d;
      coefficients_in[0] = -(1 - std::sqrt(static_cast<DataType>(2.0)) * c + c * c) / d;
      coefficients_out[1] = - 2 * (c * c - V0) / d;
      coefficients_out[0] = - (V0 - std::sqrt(static_cast<DataType>(2.0) * V0) * c + c * c) / d;
    }
    else
    {
      DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);
      
      coefficients_in[2] = -(gain + std::sqrt(static_cast<DataType>(2.0) * gain) * c + c * c) / d;
      coefficients_in[1] = -2 * (c * c - gain) / d;
      coefficients_in[0] = -(gain - std::sqrt(static_cast<DataType>(2.0) * gain) * c + c * c) / d;
      coefficients_out[1] = - 2 * (c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(static_cast<DataType>(2.0)) * c + c * c) / d;
    }
  }
  
  template<typename DataType_>
  void SecondOrderHighShelvingCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  DataType_ SecondOrderHighShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template class SecondOrderBaseCoefficients<float>;
  template class SecondOrderBaseCoefficients<double>;
  
  template class SecondOrderBandPassCoefficients<float>;
  template class SecondOrderBandPassCoefficients<double>;
  template class SecondOrderLowPassCoefficients<float>;
  template class SecondOrderLowPassCoefficients<double>;
  template class SecondOrderHighPassCoefficients<float>;
  template class SecondOrderHighPassCoefficients<double>;
  template class SecondOrderBandPassPeakCoefficients<float>;
  template class SecondOrderBandPassPeakCoefficients<double>;
  template class SecondOrderAllPassCoefficients<float>;
  template class SecondOrderAllPassCoefficients<double>;
  template class SecondOrderLowShelvingCoefficients<float>;
  template class SecondOrderLowShelvingCoefficients<double>;
  template class SecondOrderHighShelvingCoefficients<float>;
  template class SecondOrderHighShelvingCoefficients<double>;
  
  template class IIRFilter<SecondOrderBandPassCoefficients<float> >;
  template class IIRFilter<SecondOrderBandPassCoefficients<double> >;
  template class IIRFilter<SecondOrderLowPassCoefficients<float> >;
  template class IIRFilter<SecondOrderLowPassCoefficients<double> >;
  template class IIRFilter<SecondOrderHighPassCoefficients<float> >;
  template class IIRFilter<SecondOrderHighPassCoefficients<double> >;
  template class IIRFilter<SecondOrderBandPassPeakCoefficients<float> >;
  template class IIRFilter<SecondOrderBandPassPeakCoefficients<double> >;
  template class IIRFilter<SecondOrderAllPassCoefficients<float> >;
  template class IIRFilter<SecondOrderAllPassCoefficients<double> >;
  template class IIRFilter<SecondOrderLowShelvingCoefficients<float> >;
  template class IIRFilter<SecondOrderLowShelvingCoefficients<double> >;
  template class IIRFilter<SecondOrderHighShelvingCoefficients<float> >;
  template class IIRFilter<SecondOrderHighShelvingCoefficients<double> >;
}
