/**
 * \file TimeVaryingSecondOrderFilter.cpp
 * @see http://abvolt.com/research/publications2.htm
 * @see http://www.music.mcgill.ca/~ich/classes/FiltersChap2.pdf for the allpass filter
 */

#include "TimeVaryingSecondOrderFilter.h"
#include <ATK/EQ/TimeVaryingIIRFilter.h>

#include <boost/math/constants/constants.hpp>

#include <cassert>
#include <cmath>

namespace ATK
{
  /// Time varying coefficient base class. Two input ports, the first is the data, the second one is the central frequency
  template <typename DataType>
  TimeVaryingBaseSecondOrderCoefficients<DataType>::TimeVaryingBaseSecondOrderCoefficients()
    :Parent(2, 1)
  {
  }

  template <typename DataType>
  void TimeVaryingBaseSecondOrderCoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.clear();
    coefficients_in.reserve((in_order+1) * number_of_steps);
    coefficients_out.clear();
    coefficients_out.reserve(out_order * number_of_steps);
  }

  template <typename DataType>
  void TimeVaryingBaseSecondOrderCoefficients<DataType>::set_min_frequency(double min_frequency)
  {
    if(min_frequency <= 0)
    {
      throw std::out_of_range("Min frequency must be positive");
    }
    this->min_frequency = min_frequency;
    setup();
  }

  template <typename DataType>
  double TimeVaryingBaseSecondOrderCoefficients<DataType>::get_min_frequency() const
  {
    return min_frequency;
  }

  template <typename DataType>
  void TimeVaryingBaseSecondOrderCoefficients<DataType>::set_max_frequency(double max_frequency)
  {
    if(max_frequency <= min_frequency)
    {
      throw std::out_of_range("Max frequency must be greater than min frequency");
    }
    this->max_frequency = max_frequency;
    setup();
  }

  template <typename DataType>
  double TimeVaryingBaseSecondOrderCoefficients<DataType>::get_max_frequency() const
  {
    return max_frequency;
  }

  template <typename DataType>
  void TimeVaryingBaseSecondOrderCoefficients<DataType>::set_number_of_steps(int number_of_steps)
  {
    if(number_of_steps <= 0)
    {
      throw std::out_of_range("Number of steps must be strictly positive");
    }
    this->number_of_steps = number_of_steps;
    setup();
  }

  template <typename DataType>
  int TimeVaryingBaseSecondOrderCoefficients<DataType>::get_number_of_steps() const
  {
    return number_of_steps;
  }

  template <typename DataType>
  void TimeVaryingBaseSecondOrderCoefficients<DataType>::set_memory(double memory)
  {
    if(memory < 0 || memory >= 1)
    {
      throw std::out_of_range("Memory for time varying EQ had to be in the range [0, 1[");
    }
    this->memory = memory;
  }

  template <typename DataType>
  double TimeVaryingBaseSecondOrderCoefficients<DataType>::get_memory() const
  {
    return memory;
  }

  template<typename DataType>
  TimeVaryingBandPassCoefficients<DataType>::TimeVaryingBandPassCoefficients()
    :Parent()
  {
  }

  template <typename DataType>
  void TimeVaryingBandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    for(gsl::index i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = static_cast<DataType>((max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency);
      DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
      DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);
      DataType Q_inv = 1 / Q;

      coefficients_in.push_back(-Q_inv * c / d);
      coefficients_in.push_back(0);
      coefficients_in.push_back(Q_inv * c / d);
      coefficients_out.push_back(- (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d);
      coefficients_out.push_back(- 2 * (c * c - 1) / d);
    }
  }
  
  template <typename DataType_>
  void TimeVaryingBandPassCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q must be strictly positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ TimeVaryingBandPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType>
  TimeVaryingLowPassCoefficients<DataType>::TimeVaryingLowPassCoefficients()
    :Parent()
  {
  }

  template <typename DataType>
  void TimeVaryingLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    for(gsl::index i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = static_cast<DataType>((max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency);
      DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
      DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);
    
      coefficients_in.push_back(c * c / d);
      coefficients_in.push_back(2 * c * c / d);
      coefficients_in.push_back(c * c / d);
      coefficients_out.push_back(- (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d);
      coefficients_out.push_back(- 2 * (c * c - 1) / d);
    }
  }

  template<typename DataType>
  TimeVaryingHighPassCoefficients<DataType>::TimeVaryingHighPassCoefficients()
    :Parent()
  {
  }

  template <typename DataType>
  void TimeVaryingHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    for(gsl::index i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = static_cast<DataType>((max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency);
      DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
      DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);

      coefficients_in.push_back(1);
      coefficients_in.push_back(-2);
      coefficients_in.push_back(1);
      coefficients_out.push_back(- (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d);
      coefficients_out.push_back(- 2 * (c * c - 1) / d);
    }
  }

  template<typename DataType>
  TimeVaryingBandPassPeakCoefficients<DataType>::TimeVaryingBandPassPeakCoefficients()
    :Parent()
  {
  }

  template <typename DataType>
  void TimeVaryingBandPassPeakCoefficients<DataType>::setup()
  {
    Parent::setup();

    for(gsl::index i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = static_cast<DataType>((max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency);
      DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
      DataType Q_inv = 1 / Q;
      if(gain <= 1)
      {
        DataType V0 = 1 / gain;
        DataType d = 1 + V0 * Q_inv * c + c * c;

        coefficients_in.push_back((1 - Q_inv * c + c * c) / d);
        coefficients_in.push_back(2 * (c * c - 1) / d);
        coefficients_in.push_back((1 + Q_inv * c + c * c) / d);
        coefficients_out.push_back(-(1 - V0 * Q_inv * c + c * c) / d);
        coefficients_out.push_back(-2 * (c * c - 1) / d);
      }
      else
      {
        DataType V0 = gain;
        DataType d = 1 + Q_inv * c + c * c;

        coefficients_in.push_back((1 - V0 * Q_inv * c + c * c) / d);
        coefficients_in.push_back(2 * (c * c - 1) / d);
        coefficients_in.push_back((1 + V0 * Q_inv * c + c * c) / d);
        coefficients_out.push_back(-(1 - Q_inv * c + c * c) / d);
        coefficients_out.push_back(-2 * (c * c - 1) / d);
      }
    }
  }

  template <typename DataType_>
  void TimeVaryingBandPassPeakCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q must be strictly positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ TimeVaryingBandPassPeakCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template <typename DataType_>
  void TimeVaryingBandPassPeakCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    if(gain <= 0)
    {
      throw std::out_of_range("Gain must be strictly positive");
    }
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  DataType_ TimeVaryingBandPassPeakCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  TimeVaryingAllPassCoefficients<DataType>::TimeVaryingAllPassCoefficients()
    :Parent()
  {
  }

  template <typename DataType>
  void TimeVaryingAllPassCoefficients<DataType>::setup()
  {
    Parent::setup();

    for(gsl::index i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = static_cast<DataType>((max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency);
      DataType c = std::tan(boost::math::constants::pi<DataType>() * Q);
      DataType d = -std::cos(2 * boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);

      coefficients_in.push_back(1);
      coefficients_in.push_back(d * (1 - c));
      coefficients_in.push_back(-c);
      coefficients_out.push_back(c);
      coefficients_out.push_back(-d * (1 - c));
    }
  }

  template <typename DataType_>
  void TimeVaryingAllPassCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q must be strictly positive");
    }
    this->Q = Q;
    setup();
  }

  template <typename DataType_>
  DataType_ TimeVaryingAllPassCoefficients<DataType_>::get_Q() const
  {
    return Q;
  }

  template<typename DataType>
  TimeVaryingLowShelvingCoefficients<DataType>::TimeVaryingLowShelvingCoefficients()
    :Parent()
  {
  }

  template <typename DataType>
  void TimeVaryingLowShelvingCoefficients<DataType>::setup()
  {
    Parent::setup();

    for(gsl::index i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = static_cast<DataType>((max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency);
      DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
      if(gain <= 1)
      {
        DataType V0 = 1 / gain;
        DataType d = (1 + std::sqrt(static_cast<DataType>(2.) * V0) * c + V0 * c * c);

        coefficients_in.push_back((1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d);
        coefficients_in.push_back(2 * (c * c - 1) / d);
        coefficients_in.push_back((1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d);
        coefficients_out.push_back(- (1 - std::sqrt(static_cast<DataType>(2.) * V0) * c + V0 * c * c) / d);
        coefficients_out.push_back(- 2 * (V0 * c * c - 1) / d);
      }
      else
      {
        DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);

        coefficients_in.push_back((1 - std::sqrt(static_cast<DataType>(2.) * gain) * c + gain * c * c) / d);
        coefficients_in.push_back(2 * (gain * c * c - 1) / d);
        coefficients_in.push_back((1 + std::sqrt(static_cast<DataType>(2.) * gain) * c + gain * c * c) / d);
        coefficients_out.push_back(- (1 - std::sqrt(static_cast<DataType>(2.)) * c + c * c) / d);
        coefficients_out.push_back(- 2 * (c * c - 1) / d);
      }
    }
  }

  template <typename DataType_>
  void TimeVaryingLowShelvingCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    if(gain <= 0)
    {
      throw std::out_of_range("Gain must be strictly positive");
    }
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  DataType_ TimeVaryingLowShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  TimeVaryingHighShelvingCoefficients<DataType>::TimeVaryingHighShelvingCoefficients()
    :Parent()
  {
  }

  template <typename DataType>
  void TimeVaryingHighShelvingCoefficients<DataType>::setup()
  {
    Parent::setup();

    for(gsl::index i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = static_cast<DataType>((max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency);
      DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
      if(gain <= 1)
      {
        DataType V0 = 1 / gain;
        DataType d = (V0 + std::sqrt(static_cast<DataType>(2.) * V0) * c + c * c);

        coefficients_in.push_back(-(1 - std::sqrt(static_cast<DataType>(2.0)) * c + c * c) / d);
        coefficients_in.push_back(-2 * (c * c - 1) / d);
        coefficients_in.push_back(-(1 + std::sqrt(static_cast<DataType>(2.0)) * c + c * c) / d);
        coefficients_out.push_back(- (V0 - std::sqrt(static_cast<DataType>(2.0) * V0) * c + c * c) / d);
        coefficients_out.push_back(- 2 * (c * c - V0) / d);
      }
      else
      {
        DataType d = (1 + std::sqrt(static_cast<DataType>(2.)) * c + c * c);

        coefficients_in.push_back(-(gain - std::sqrt(static_cast<DataType>(2.0) * gain) * c + c * c) / d);
        coefficients_in.push_back(-2 * (c * c - gain) / d);
        coefficients_in.push_back(-(gain + std::sqrt(static_cast<DataType>(2.0) * gain) * c + c * c) / d);
        coefficients_out.push_back(- (1 - std::sqrt(static_cast<DataType>(2.0)) * c + c * c) / d);
        coefficients_out.push_back(- 2 * (c * c - 1) / d);
      }
    }
  }
  
  template<typename DataType_>
  void TimeVaryingHighShelvingCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    if(gain <= 0)
    {
      throw std::out_of_range("Gain must be strictly positive");
    }
    this->gain = gain;
    setup();
  }

  template <typename DataType_>
  DataType_ TimeVaryingHighShelvingCoefficients<DataType_>::get_gain() const
  {
    return gain;
  }

#if ATK_ENABLE_INSTANTIATION
  template class TimeVaryingBaseSecondOrderCoefficients<float>;
  
  template class ATK_EQ_EXPORT TimeVaryingBandPassCoefficients<float>;
  template class ATK_EQ_EXPORT TimeVaryingLowPassCoefficients<float>;
  template class ATK_EQ_EXPORT TimeVaryingHighPassCoefficients<float>;
  template class ATK_EQ_EXPORT TimeVaryingBandPassPeakCoefficients<float>;
  template class ATK_EQ_EXPORT TimeVaryingAllPassCoefficients<float>;
  template class ATK_EQ_EXPORT TimeVaryingLowShelvingCoefficients<float>;
  template class ATK_EQ_EXPORT TimeVaryingHighShelvingCoefficients<float>;
#endif
  template class TimeVaryingBaseSecondOrderCoefficients<double>;

  template class ATK_EQ_EXPORT TimeVaryingBandPassCoefficients<double>;
  template class ATK_EQ_EXPORT TimeVaryingLowPassCoefficients<double>;
  template class ATK_EQ_EXPORT TimeVaryingHighPassCoefficients<double>;
  template class ATK_EQ_EXPORT TimeVaryingBandPassPeakCoefficients<double>;
  template class ATK_EQ_EXPORT TimeVaryingAllPassCoefficients<double>;
  template class ATK_EQ_EXPORT TimeVaryingLowShelvingCoefficients<double>;
  template class ATK_EQ_EXPORT TimeVaryingHighShelvingCoefficients<double>;
}
