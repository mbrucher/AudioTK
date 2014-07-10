/**
 * \file TimeVaryingSecondOrderFilter.cpp
 * @see http://abvolt.com/research/publications2.htm
 * @see http://www.music.mcgill.ca/~ich/classes/FiltersChap2.pdf for the allpass filter
 */

#include "TimeVaryingSecondOrderFilter.h"
#include "TimeVaryingIIRFilter.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  /// Time varying coefficient base class. Two input ports, the first is the data, the second one is the central frequency
  template <typename DataType>
  TimeVaryingBaseSecondOrderCoefficients<DataType>::TimeVaryingBaseSecondOrderCoefficients()
    :Parent(2, 1), min_frequency(1), max_frequency(10), memory(.5), number_of_steps(10)
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
      throw std::out_of_range("Memory for time varying EQ had to be int he range [0, 1[");
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
    
    for(int i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = (max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency;
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
  
  template <typename DataType>
  void TimeVaryingBandPassCoefficients<DataType>::set_Q(DataType Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType>
  typename TimeVaryingBandPassCoefficients<DataType>::DataType TimeVaryingBandPassCoefficients<DataType>::get_Q() const
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

    for(int i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = (max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency;
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

    for(int i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = (max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency;
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

    for(int i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = (max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency;
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

  template <typename DataType>
  void TimeVaryingBandPassPeakCoefficients<DataType>::set_Q(DataType Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType>
  typename TimeVaryingBandPassPeakCoefficients<DataType>::DataType TimeVaryingBandPassPeakCoefficients<DataType>::get_Q() const
  {
    return Q;
  }

  template <typename DataType>
  void TimeVaryingBandPassPeakCoefficients<DataType>::set_gain(DataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType>
  typename TimeVaryingBandPassPeakCoefficients<DataType>::DataType TimeVaryingBandPassPeakCoefficients<DataType>::get_gain() const
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

    for(int i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = (max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency;
      DataType c = std::tan(boost::math::constants::pi<DataType>() * Q);
      DataType d = -std::cos(2 * boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);

      coefficients_in.push_back(1);
      coefficients_in.push_back(d * (1 - c));
      coefficients_in.push_back(-c);
      coefficients_out.push_back(c);
      coefficients_out.push_back(-d * (1 - c));
    }
  }

  template <typename DataType>
  void TimeVaryingAllPassCoefficients<DataType>::set_Q(DataType Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType>
  typename TimeVaryingAllPassCoefficients<DataType>::DataType TimeVaryingAllPassCoefficients<DataType>::get_Q() const
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

    for(int i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = (max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency;
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

  template <typename DataType>
  void TimeVaryingLowShelvingCoefficients<DataType>::set_gain(DataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType>
  typename TimeVaryingLowShelvingCoefficients<DataType>::DataType TimeVaryingLowShelvingCoefficients<DataType>::get_gain() const
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

    for(int i = 0; i < number_of_steps; ++i)
    {
      DataType cut_frequency = (max_frequency - min_frequency) * i / (number_of_steps - 1) + min_frequency;
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
  
  template<typename DataType>
  void TimeVaryingHighShelvingCoefficients<DataType>::set_gain(DataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType>
  typename TimeVaryingHighShelvingCoefficients<DataType>::DataType TimeVaryingHighShelvingCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template class TimeVaryingBaseSecondOrderCoefficients<float>;
  template class TimeVaryingBaseSecondOrderCoefficients<double>;
  
  template class TimeVaryingBandPassCoefficients<float>;
  template class TimeVaryingBandPassCoefficients<double>;
  template class TimeVaryingLowPassCoefficients<float>;
  template class TimeVaryingLowPassCoefficients<double>;
  template class TimeVaryingHighPassCoefficients<float>;
  template class TimeVaryingHighPassCoefficients<double>;
  template class TimeVaryingBandPassPeakCoefficients<float>;
  template class TimeVaryingBandPassPeakCoefficients<double>;
  template class TimeVaryingAllPassCoefficients<float>;
  template class TimeVaryingAllPassCoefficients<double>;
  template class TimeVaryingLowShelvingCoefficients<float>;
  template class TimeVaryingLowShelvingCoefficients<double>;
  template class TimeVaryingHighShelvingCoefficients<float>;
  template class TimeVaryingHighShelvingCoefficients<double>;
  
  template class TimeVaryingIIRFilter<TimeVaryingBandPassCoefficients<float> >;
  template class TimeVaryingIIRFilter<TimeVaryingBandPassCoefficients<double> >;
  template class TimeVaryingIIRFilter<TimeVaryingLowPassCoefficients<float> >;
  template class TimeVaryingIIRFilter<TimeVaryingLowPassCoefficients<double> >;
  template class TimeVaryingIIRFilter<TimeVaryingHighPassCoefficients<float> >;
  template class TimeVaryingIIRFilter<TimeVaryingHighPassCoefficients<double> >;
  template class TimeVaryingIIRFilter<TimeVaryingBandPassPeakCoefficients<float> >;
  template class TimeVaryingIIRFilter<TimeVaryingBandPassPeakCoefficients<double> >;
  template class TimeVaryingIIRFilter<TimeVaryingAllPassCoefficients<float> >;
  template class TimeVaryingIIRFilter<TimeVaryingAllPassCoefficients<double> >;
  template class TimeVaryingIIRFilter<TimeVaryingLowShelvingCoefficients<float> >;
  template class TimeVaryingIIRFilter<TimeVaryingLowShelvingCoefficients<double> >;
  template class TimeVaryingIIRFilter<TimeVaryingHighShelvingCoefficients<float> >;
  template class TimeVaryingIIRFilter<TimeVaryingHighShelvingCoefficients<double> >;
}
