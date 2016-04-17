/**
 * \file SecondOrderSVFFilter.cpp
 */

#include "SecondOrderSVFFilter.h"

#include <cassert>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename SVFCoefficients>
  struct SecondOrderSVFFilter<SVFCoefficients>::SVFState
  {
    typename SVFCoefficients::DataType iceq1;
    typename SVFCoefficients::DataType iceq2;
    
    SVFState()
    :iceq1(0), iceq2(0)
    {
    }
  };
  
  template<typename SVFCoefficients>
  SecondOrderSVFFilter<SVFCoefficients>::SecondOrderSVFFilter(int nb_channels)
  :SVFCoefficients(nb_channels), state(new SVFState[nb_channels])
  {
  }

  template<typename SVFCoefficients>
  SecondOrderSVFFilter<SVFCoefficients>::~SecondOrderSVFFilter()
  {
  }

  template<typename SVFCoefficients>
  void SecondOrderSVFFilter<SVFCoefficients>::full_setup()
  {
    state.reset(new SVFState[nb_input_ports]);
  }

  template<typename DataType>
  void SecondOrderSVFFilter<DataType>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);
    
    for(int j = 0; j < nb_input_ports; ++j)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[j];
      DataType* ATK_RESTRICT output = outputs[j];
      
      for(int64_t i = 0; i < size; ++i)
      {
        DataType v3 = input[i] - state[j].iceq2;
        DataType v1 = a1 * state[j].iceq1 + a2 * v3;
        DataType v2 = state[j].iceq2 + a2 * state[j].iceq1 + a3 * v3;
        state[j].iceq1 = 2 * v1 - state[j].iceq1;
        state[j].iceq2 = 2 * v2 - state[j].iceq2;
        
        output[i] = m0 * input[i] + m1 * v1 + m2 * v2;
      }
    }
  }
  
  template<typename DataType>
  BaseSecondOrderSVFCoefficients<DataType>::BaseSecondOrderSVFCoefficients(int nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels), cut_frequency(0), Q(1)
  {
  }

  template<typename DataType_>
  void BaseSecondOrderSVFCoefficients<DataType_>::set_cut_frequency(DataType_ cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }

  template<typename DataType>
  DataType BaseSecondOrderSVFCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template<typename DataType_>
  void BaseSecondOrderSVFCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    this->Q = Q;
    setup();
  }

  template<typename DataType>
  DataType BaseSecondOrderSVFCoefficients<DataType>::get_Q() const
  {
    return Q;
  }

  template<typename DataType_>
  LowSecondOrderSVFCoefficients<DataType_>::LowSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void LowSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1/Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 0;
    m1 = 0;
    m2 = 1;
  }

  template<typename DataType_>
  BandSecondOrderSVFCoefficients<DataType_>::BandSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void BandSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 0;
    m1 = 1;
    m2 = 0;
  }

  template<typename DataType_>
  HighSecondOrderSVFCoefficients<DataType_>::HighSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void HighSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = -1;
  }

  template<typename DataType_>
  NotchSecondOrderSVFCoefficients<DataType_>::NotchSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void NotchSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = 2;
  }

  template<typename DataType_>
  PeakSecondOrderSVFCoefficients<DataType_>::PeakSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void PeakSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = 0;
  }

  template<typename DataType_>
  BellSecondOrderSVFCoefficients<DataType_>::BellSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels), gain(0)
  {
    
  }
  
  template<typename DataType_>
  void BellSecondOrderSVFCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  DataType BellSecondOrderSVFCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void BellSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / (Q* gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain * gain - 1);
    m2 = 0;
  }

  template<typename DataType_>
  LowShelfSecondOrderSVFCoefficients<DataType_>::LowShelfSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels), gain(0)
  {
    
  }

  template<typename DataType_>
  void LowShelfSecondOrderSVFCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  DataType LowShelfSecondOrderSVFCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void LowShelfSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain - 1);
    m2 = gain * gain - 1;
  }

  template<typename DataType_>
  HighShelfSecondOrderSVFCoefficients<DataType_>::HighShelfSecondOrderSVFCoefficients(int nb_channels)
  :Parent(nb_channels), gain(0)
  {
  }

  template<typename DataType_>
  void HighShelfSecondOrderSVFCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  DataType HighShelfSecondOrderSVFCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void HighShelfSecondOrderSVFCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<DataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / (Q* gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = gain * gain;
    m1 = k * (1 - gain) * gain;
    m2 = 1 - gain * gain;
  }

  template class BaseSecondOrderSVFCoefficients<float>;
  template class BaseSecondOrderSVFCoefficients<double>;

  template class LowSecondOrderSVFCoefficients<float>;
  template class LowSecondOrderSVFCoefficients<double>;
  template class BandSecondOrderSVFCoefficients<float>;
  template class BandSecondOrderSVFCoefficients<double>;
  template class HighSecondOrderSVFCoefficients<float>;
  template class HighSecondOrderSVFCoefficients<double>;
  template class NotchSecondOrderSVFCoefficients<float>;
  template class NotchSecondOrderSVFCoefficients<double>;
  template class PeakSecondOrderSVFCoefficients<float>;
  template class PeakSecondOrderSVFCoefficients<double>;
  template class BellSecondOrderSVFCoefficients<float>;
  template class BellSecondOrderSVFCoefficients<double>;
  template class LowShelfSecondOrderSVFCoefficients<float>;
  template class LowShelfSecondOrderSVFCoefficients<double>;
  template class HighShelfSecondOrderSVFCoefficients<float>;
  template class HighShelfSecondOrderSVFCoefficients<double>;

  template class SecondOrderSVFFilter<LowSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<LowSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<BandSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<BandSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<HighSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<HighSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<NotchSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<NotchSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<PeakSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<PeakSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<BellSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<BellSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<LowShelfSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<LowShelfSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<HighShelfSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<HighShelfSecondOrderSVFCoefficients<double> >;
}
