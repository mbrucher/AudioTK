/**
 * \file SecondOrderFilter.h
 */

#include "SecondOrderFilter.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType>
  BaseCoefficients<DataType>::BaseCoefficients()
    :Parent(1, 1)
  {
  }

  template <typename DataType>
  void BaseCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }

  template <typename DataType>
  void BandPassCoefficients<DataType>::setup()
  {
    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    DataType d = (1 + std::sqrt(2.) * c + c * c);
    DataType Q_inv = 1 / Q;
    
    coefficients_in[2] = Q_inv * c / d;
    coefficients_in[1] = 0;
    coefficients_in[0] = -Q_inv * c / d;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(2.) * c + c * c) / d;
  }
  
  template <typename DataType>
  void BandPassCoefficients<DataType>::set_Q(DataType Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType>
  void LowPassCoefficients<DataType>::setup()
  {
    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    DataType d = (1 + std::sqrt(2.) * c + c * c);
    
    coefficients_in[2] = c * c / d;
    coefficients_in[1] = 2 * c * c / d;
    coefficients_in[0] = c * c / d;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(2.) * c + c * c) / d;
  }

  template <typename DataType>
  void HighPassCoefficients<DataType>::setup()
  {
    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    DataType d = (1 + std::sqrt(2.) * c + c * c);
    
    coefficients_in[2] = 1;
    coefficients_in[1] = -2;
    coefficients_in[0] = 1;
    coefficients_out[1] = - 2 * (c * c - 1) / d;
    coefficients_out[0] = - (1 - std::sqrt(2.) * c + c * c) / d;
  }

  template <typename DataType>
  void BandPassPeakCoefficients<DataType>::setup()
  {
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

  template <typename DataType>
  void BandPassPeakCoefficients<DataType>::set_Q(DataType Q)
  {
    this->Q = Q;
    setup();
  }

  template <typename DataType>
  void BandPassPeakCoefficients<DataType>::set_gain(DataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType>
  void LowShelvingCoefficients<DataType>::setup()
  {
    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    if(gain <= 1)
    {
      DataType V0 = 1 / gain;
      DataType d = (1 + std::sqrt(2. * V0) * c + V0 * c * c);
      
      coefficients_in[2] = (1 + std::sqrt(2.) * c + c * c) / d;
      coefficients_in[1] = 2 * (c * c - 1) / d;
      coefficients_in[0] = (1 - std::sqrt(2.) * c + c * c) / d;
      coefficients_out[1] = - 2 * (V0 * c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(2. * V0) * c + V0 * c * c) / d;
    }
    else
    {
      DataType d = (1 + std::sqrt(2.) * c + c * c);
      
      coefficients_in[2] = (1 + std::sqrt(2. * gain) * c + gain * c * c) / d;
      coefficients_in[1] = 2 * (gain * c * c - 1) / d;
      coefficients_in[0] = (1 - std::sqrt(2. * gain) * c + gain * c * c) / d;
      coefficients_out[1] = - 2 * (c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(2.) * c + c * c) / d;
    }
  }

  template <typename DataType>
  void LowShelvingCoefficients<DataType>::set_gain(DataType gain)
  {
    this->gain = gain;
    setup();
  }

  template <typename DataType>
  void HighShelvingCoefficients<DataType>::setup()
  {
    DataType c = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    if(gain <= 1)
    {
      DataType V0 = 1 / gain;
      DataType d = (V0 + std::sqrt(2. * V0) * c + c * c);
      
      coefficients_in[2] = -(1 + std::sqrt(2.) * c + c * c) / d;
      coefficients_in[1] = -2 * (c * c - 1) / d;
      coefficients_in[0] = -(1 - std::sqrt(2.) * c + c * c) / d;
      coefficients_out[1] = - 2 * (c * c - V0) / d;
      coefficients_out[0] = - (V0 - std::sqrt(2. * V0) * c + c * c) / d;
    }
    else
    {
      DataType d = (1 + std::sqrt(2.) * c + c * c);
      
      coefficients_in[2] = -(gain + std::sqrt(2. * gain) * c + c * c) / d;
      coefficients_in[1] = -2 * (c * c - gain) / d;
      coefficients_in[0] = -(gain - std::sqrt(2. * gain) * c + c * c) / d;
      coefficients_out[1] = - 2 * (c * c - 1) / d;
      coefficients_out[0] = - (1 - std::sqrt(2.) * c + c * c) / d;
    }
  }
  
  template<typename DataType>
  void HighShelvingCoefficients<DataType>::set_gain(DataType gain)
  {
    this->gain = gain;
    setup();
  }
  
  template<class Coefficients>
  SecondOrderFilter<Coefficients>::SecondOrderFilter()
  {
    for(int i = 0; i < 2; ++i)
    {
      buffer_in[i] = 0;
      buffer_out[i] = 0;
    }
  }

  template<class Coefficients>
  void SecondOrderFilter<Coefficients>::process_impl(int size)
  {
    assert(input_sampling_rate == output_sampling_rate);
    if(outputs_size[0] < size)
    {
      outputs[0].reset(new DataType[size]);
      outputs_size[0] = size;
    }
    
    for(int i = 0; i < size; ++i)
    {
      outputs[0][i] = coefficients_in[2] * converted_inputs[0][i] + coefficients_in[1] * buffer_in[1] + coefficients_in[0] * buffer_in[0] + coefficients_out[1] * buffer_out[1] + coefficients_out[0] * buffer_out[0];
      
      buffer_in[0] = buffer_in[1];
      buffer_in[1] = converted_inputs[0][i];
      buffer_out[0] = buffer_out[1];
      buffer_out[1] = outputs[0][i];
    }
  }

  template class BaseCoefficients<float>;
  template class BaseCoefficients<double>;
  
  template class BandPassCoefficients<float>;
  template class BandPassCoefficients<double>;
  template class LowPassCoefficients<float>;
  template class LowPassCoefficients<double>;
  template class HighPassCoefficients<float>;
  template class HighPassCoefficients<double>;
  template class BandPassPeakCoefficients<float>;
  template class BandPassPeakCoefficients<double>;
  template class LowShelvingCoefficients<float>;
  template class LowShelvingCoefficients<double>;
  template class HighShelvingCoefficients<float>;
  template class HighShelvingCoefficients<double>;
  
  template class SecondOrderFilter<BandPassCoefficients<float> >;
  template class SecondOrderFilter<BandPassCoefficients<double> >;
  template class SecondOrderFilter<LowPassCoefficients<float> >;
  template class SecondOrderFilter<LowPassCoefficients<double> >;
  template class SecondOrderFilter<HighPassCoefficients<float> >;
  template class SecondOrderFilter<HighPassCoefficients<double> >;
  template class SecondOrderFilter<BandPassPeakCoefficients<float> >;
  template class SecondOrderFilter<BandPassPeakCoefficients<double> >;
  template class SecondOrderFilter<LowShelvingCoefficients<float> >;
  template class SecondOrderFilter<LowShelvingCoefficients<double> >;
  template class SecondOrderFilter<HighShelvingCoefficients<float> >;
  template class SecondOrderFilter<HighShelvingCoefficients<double> >;
}
