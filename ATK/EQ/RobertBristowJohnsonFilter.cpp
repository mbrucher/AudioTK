/**
 * \file RobertBristowJohnsonFilter.cpp
 */

#include <boost/math/constants/constants.hpp>

#include "RobertBristowJohnsonFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  RobertBristowJohnsonLowPassCoefficients<DataType>::RobertBristowJohnsonLowPassCoefficients(std::size_t nb_channels)
    :Parent(nb_channels), Q(1)
  {
  }

  template <typename DataType>
  void RobertBristowJohnsonLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);

    coefficients_in[2] = (1 - cosw0)/2 / (1 + alpha);
    coefficients_in[1] = (1 - cosw0) / (1 + alpha);
    coefficients_in[0] = (1 - cosw0) / 2 / (1 + alpha);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }

  template <typename DataType_>
  void RobertBristowJohnsonLowPassCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename RobertBristowJohnsonLowPassCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonLowPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType>
  RobertBristowJohnsonHighPassCoefficients<DataType>::RobertBristowJohnsonHighPassCoefficients(std::size_t nb_channels)
    :Parent(nb_channels), Q(1)
  {
  }

  template <typename DataType>
  void RobertBristowJohnsonHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);

    coefficients_in[2] = (1 + cosw0) / 2 / (1 + alpha);
    coefficients_in[1] = -(1 + cosw0) / (1 + alpha);
    coefficients_in[0] = (1 + cosw0) / 2 / (1 + alpha);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }

  template <typename DataType_>
  void RobertBristowJohnsonHighPassCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename RobertBristowJohnsonHighPassCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonHighPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType>
  RobertBristowJohnsonBandPassCoefficients<DataType>::RobertBristowJohnsonBandPassCoefficients(std::size_t nb_channels)
    :Parent(nb_channels), Q(1)
  {
  }

  template <typename DataType>
  void RobertBristowJohnsonBandPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);

    coefficients_in[2] = Q * alpha / (1 + alpha);
    coefficients_in[1] = 0;
    coefficients_in[0] = - Q * alpha / (1 + alpha);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }

  template <typename DataType_>
  void RobertBristowJohnsonBandPassCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename RobertBristowJohnsonBandPassCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonBandPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType>
  RobertBristowJohnsonBandPass2Coefficients<DataType>::RobertBristowJohnsonBandPass2Coefficients(std::size_t nb_channels)
    :Parent(nb_channels), Q(1)
  {
  }

  template <typename DataType>
  void RobertBristowJohnsonBandPass2Coefficients<DataType>::setup()
  {
    Parent::setup();

    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);

    coefficients_in[2] = alpha / (1 + alpha);
    coefficients_in[1] = 0;
    coefficients_in[0] = -alpha / (1 + alpha);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }

  template <typename DataType_>
  void RobertBristowJohnsonBandPass2Coefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename RobertBristowJohnsonBandPass2Coefficients<DataType_>::CoeffDataType RobertBristowJohnsonBandPass2Coefficients<DataType_>::get_Q() const
  {
    return Q;
  }
  
  template<typename DataType>
  RobertBristowJohnsonBandStopCoefficients<DataType>::RobertBristowJohnsonBandStopCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), Q(1)
  {
  }
  
  template <typename DataType>
  void RobertBristowJohnsonBandStopCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);
    
    coefficients_in[2] = 1 / (1 + alpha);
    coefficients_in[1] = -2 * cosw0 / (1 + alpha);
    coefficients_in[0] = 1 / (1 + alpha);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }
  
  template <typename DataType_>
  void RobertBristowJohnsonBandStopCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }
  
  template <typename DataType_>
  typename RobertBristowJohnsonBandStopCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonBandStopCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType>
  RobertBristowJohnsonAllPassCoefficients<DataType>::RobertBristowJohnsonAllPassCoefficients(std::size_t nb_channels)
    :Parent(nb_channels), Q(1)
  {
  }

  template <typename DataType>
  void RobertBristowJohnsonAllPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);

    coefficients_in[2] = (1 - alpha) / (1 + alpha);
    coefficients_in[1] = -2 * cosw0 / (1 + alpha);
    coefficients_in[0] = 1;
    coefficients_out[1] = 2 * cosw0 / (1 + alpha);
    coefficients_out[0] = (alpha - 1) / (1 + alpha);
  }

  template <typename DataType_>
  void RobertBristowJohnsonAllPassCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  typename RobertBristowJohnsonAllPassCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonAllPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }
  
  template<typename DataType>
  RobertBristowJohnsonBandPassPeakCoefficients<DataType>::RobertBristowJohnsonBandPassPeakCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), Q(1)
  {
  }
  
  template <typename DataType>
  void RobertBristowJohnsonBandPassPeakCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);
    
    coefficients_in[2] = (1 + alpha * gain) / (1 + alpha / gain);
    coefficients_in[1] = -2 * cosw0 / (1 + alpha / gain);
    coefficients_in[0] = (1 - alpha * gain) / (1 + alpha / gain);
    coefficients_out[1] = 2 * cosw0 / (1 + alpha / gain);
    coefficients_out[0] = (alpha / gain - 1) / (1 + alpha / gain);
  }
  
  template <typename DataType_>
  void RobertBristowJohnsonBandPassPeakCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }
  
  template <typename DataType_>
  typename RobertBristowJohnsonBandPassPeakCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonBandPassPeakCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }
  
  template <typename DataType_>
  void RobertBristowJohnsonBandPassPeakCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    if (gain <= 0)
    {
      throw std::out_of_range("gain must be positive");
    }
    this->gain = gain;
    setup();
  }
  
  template <typename DataType_>
  typename RobertBristowJohnsonBandPassPeakCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonBandPassPeakCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }
  
  template<typename DataType>
  RobertBristowJohnsonLowShelvingCoefficients<DataType>::RobertBristowJohnsonLowShelvingCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), Q(1), gain(1)
  {
  }
  
  template <typename DataType>
  void RobertBristowJohnsonLowShelvingCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);
    CoeffDataType d = (gain + 1) + (gain - 1) * cosw0 + 2 * std::sqrt(gain) * alpha;

    coefficients_in[2] = gain * ((gain + 1) - (gain - 1) * cosw0 + 2 * sqrt(gain) * alpha) / d;
    coefficients_in[1] = 2 * gain * ((gain - 1) - (gain + 1) * cosw0) / d;
    coefficients_in[0] = gain * ((gain + 1) - (gain - 1) * cosw0 - 2 * sqrt(gain) * alpha) / d;
    coefficients_out[1] = 2 * ((gain - 1) + (gain + 1) * cosw0) / d;
    coefficients_out[0] = -((gain + 1) + (gain - 1) * cosw0 - 2 * sqrt(gain) * alpha) / d;
  }
  
  template <typename DataType_>
  void RobertBristowJohnsonLowShelvingCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }
  
  template <typename DataType_>
  typename RobertBristowJohnsonLowShelvingCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonLowShelvingCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }
  
  template <typename DataType_>
  void RobertBristowJohnsonLowShelvingCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    if (gain <= 0)
    {
      throw std::out_of_range("gain must be positive");
    }
    this->gain = gain;
    setup();
  }
  
  template <typename DataType_>
  typename RobertBristowJohnsonLowShelvingCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonLowShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }
  
  template<typename DataType>
  RobertBristowJohnsonHighShelvingCoefficients<DataType>::RobertBristowJohnsonHighShelvingCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), Q(1), gain(1)
  {
  }
  
  template <typename DataType>
  void RobertBristowJohnsonHighShelvingCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    CoeffDataType w0 = 2 * boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate;
    CoeffDataType cosw0 = std::cos(w0);
    CoeffDataType alpha = std::sin(w0) / (2 * Q);
    CoeffDataType d = (gain + 1) - (gain - 1) * cosw0 + 2 * std::sqrt(gain) * alpha;
    
    coefficients_in[2] = gain * ((gain + 1) + (gain - 1) * cosw0 + 2 * sqrt(gain) * alpha) / d;
    coefficients_in[1] = -2 * gain * ((gain - 1) + (gain + 1) * cosw0) / d;
    coefficients_in[0] = gain * ((gain + 1) + (gain - 1) * cosw0 - 2 * sqrt(gain) * alpha) / d;
    coefficients_out[1] = -2 * ((gain - 1) - (gain + 1) * cosw0) / d;
    coefficients_out[0] = -((gain + 1) - (gain - 1) * cosw0 - 2 * sqrt(gain) * alpha) / d;
  }
  
  template <typename DataType_>
  void RobertBristowJohnsonHighShelvingCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if (Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }
  
  template <typename DataType_>
  typename RobertBristowJohnsonHighShelvingCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonHighShelvingCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }
  
  template <typename DataType_>
  void RobertBristowJohnsonHighShelvingCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    if (gain <= 0)
    {
      throw std::out_of_range("gain must be positive");
    }
    this->gain = gain;
    setup();
  }
  
  template <typename DataType_>
  typename RobertBristowJohnsonHighShelvingCoefficients<DataType_>::CoeffDataType RobertBristowJohnsonHighShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template class RobertBristowJohnsonLowPassCoefficients<float>;
  template class RobertBristowJohnsonLowPassCoefficients<double>;
  template class RobertBristowJohnsonLowPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonLowPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonHighPassCoefficients<float>;
  template class RobertBristowJohnsonHighPassCoefficients<double>;
  template class RobertBristowJohnsonHighPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonHighPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandPassCoefficients<float>;
  template class RobertBristowJohnsonBandPassCoefficients<double>;
  template class RobertBristowJohnsonBandPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandPass2Coefficients<float>;
  template class RobertBristowJohnsonBandPass2Coefficients<double>;
  template class RobertBristowJohnsonBandPass2Coefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandPass2Coefficients<std::complex<double> >;
  template class RobertBristowJohnsonAllPassCoefficients<float>;
  template class RobertBristowJohnsonAllPassCoefficients<double>;
  template class RobertBristowJohnsonAllPassCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonAllPassCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandStopCoefficients<float>;
  template class RobertBristowJohnsonBandStopCoefficients<double>;
  template class RobertBristowJohnsonBandStopCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandStopCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<float>;
  template class RobertBristowJohnsonBandPassPeakCoefficients<double>;
  template class RobertBristowJohnsonBandPassPeakCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<float>;
  template class RobertBristowJohnsonLowShelvingCoefficients<double>;
  template class RobertBristowJohnsonLowShelvingCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<std::complex<double> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<float>;
  template class RobertBristowJohnsonHighShelvingCoefficients<double>;
  template class RobertBristowJohnsonHighShelvingCoefficients<std::complex<float> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<std::complex<double> >;

  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonLowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonHighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandPass2Coefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandStopCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonAllPassCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<std::complex<double> > >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<float> >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<double> >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<std::complex<float> > >;
  template class IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<std::complex<double> > >;
}
