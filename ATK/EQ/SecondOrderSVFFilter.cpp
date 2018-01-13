/**
 * \file SecondOrderSVFFilter.cpp
 */

#include <ATK/EQ/SecondOrderSVFFilter.h>

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
  SecondOrderSVFFilter<SVFCoefficients>::SecondOrderSVFFilter(std::size_t nb_channels)
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
  void SecondOrderSVFFilter<DataType>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == nb_output_ports);
    
    for(unsigned int j = 0; j < nb_input_ports; ++j)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[j];
      DataType* ATK_RESTRICT output = outputs[j];
      
      for(std::size_t i = 0; i < size; ++i)
      {
        DataType v3 = input[i] - state[j].iceq2;
        DataType v1 = a1 * state[j].iceq1 + a2 * v3;
        DataType v2 = state[j].iceq2 + a2 * state[j].iceq1 + a3 * v3;
        state[j].iceq1 = CoeffDataType(2) * v1 - state[j].iceq1;
        state[j].iceq2 = CoeffDataType(2) * v2 - state[j].iceq2;
        
        output[i] = m0 * input[i] + m1 * v1 + m2 * v2;
      }
    }
  }
  
  template<typename DataType>
  SecondOrderSVFBaseCoefficients<DataType>::SecondOrderSVFBaseCoefficients(std::size_t nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels), cut_frequency(0), Q(1)
  {
  }

  template<typename DataType_>
  void SecondOrderSVFBaseCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequencies must be positive");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }

  template<typename DataType>
  typename SecondOrderSVFBaseCoefficients<DataType>::CoeffDataType SecondOrderSVFBaseCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template<typename DataType_>
  void SecondOrderSVFBaseCoefficients<DataType_>::set_Q(CoeffDataType Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q must be positive");
    }
    this->Q = Q;
    setup();
  }

  template<typename DataType>
  typename SecondOrderSVFBaseCoefficients<DataType>::CoeffDataType SecondOrderSVFBaseCoefficients<DataType>::get_Q() const
  {
    return Q;
  }

  template<typename DataType_>
  SecondOrderSVFLowPassCoefficients<DataType_>::SecondOrderSVFLowPassCoefficients(std::size_t nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void SecondOrderSVFLowPassCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1/Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 0;
    m1 = 0;
    m2 = 1;
  }

  template<typename DataType_>
  SecondOrderSVFBandPassCoefficients<DataType_>::SecondOrderSVFBandPassCoefficients(std::size_t nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void SecondOrderSVFBandPassCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 0;
    m1 = 1;
    m2 = 0;
  }

  template<typename DataType_>
  SecondOrderSVFHighPassCoefficients<DataType_>::SecondOrderSVFHighPassCoefficients(std::size_t nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void SecondOrderSVFHighPassCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = -1;
  }

  template<typename DataType_>
  SecondOrderSVFNotchCoefficients<DataType_>::SecondOrderSVFNotchCoefficients(std::size_t nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void SecondOrderSVFNotchCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = 2;
  }

  template<typename DataType_>
  SecondOrderSVFPeakCoefficients<DataType_>::SecondOrderSVFPeakCoefficients(std::size_t nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void SecondOrderSVFPeakCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = 0;
  }

  template<typename DataType_>
  SecondOrderSVFBellCoefficients<DataType_>::SecondOrderSVFBellCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), gain(0)
  {
    
  }
  
  template<typename DataType_>
  void SecondOrderSVFBellCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  typename SecondOrderSVFBellCoefficients<DataType>::CoeffDataType SecondOrderSVFBellCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void SecondOrderSVFBellCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / (Q* gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain * gain - 1);
    m2 = 0;
  }

  template<typename DataType_>
  SecondOrderSVFLowShelfCoefficients<DataType_>::SecondOrderSVFLowShelfCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), gain(0)
  {
    
  }

  template<typename DataType_>
  void SecondOrderSVFLowShelfCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  typename SecondOrderSVFLowShelfCoefficients<DataType>::CoeffDataType SecondOrderSVFLowShelfCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void SecondOrderSVFLowShelfCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain - 1);
    m2 = gain * gain - 1;
  }

  template<typename DataType_>
  SecondOrderSVFHighShelfCoefficients<DataType_>::SecondOrderSVFHighShelfCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), gain(0)
  {
  }

  template<typename DataType_>
  void SecondOrderSVFHighShelfCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  typename SecondOrderSVFHighShelfCoefficients<DataType>::CoeffDataType SecondOrderSVFHighShelfCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void SecondOrderSVFHighShelfCoefficients<DataType>::setup()
  {
    auto g = std::tan(boost::math::constants::pi<CoeffDataType>() * cut_frequency / input_sampling_rate);
    auto k = 1 / (Q* gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = gain * gain;
    m1 = k * (1 - gain) * gain;
    m2 = 1 - gain * gain;
  }

  template class SecondOrderSVFBaseCoefficients<float>;
  template class SecondOrderSVFBaseCoefficients<double>;
  template class SecondOrderSVFBaseCoefficients<std::complex<float> >;
  template class SecondOrderSVFBaseCoefficients<std::complex<double> >;

  template class SecondOrderSVFLowPassCoefficients<float>;
  template class SecondOrderSVFLowPassCoefficients<double>;
  template class SecondOrderSVFLowPassCoefficients<std::complex<float> >;
  template class SecondOrderSVFLowPassCoefficients<std::complex<double> >;
  template class SecondOrderSVFBandPassCoefficients<float>;
  template class SecondOrderSVFBandPassCoefficients<double>;
  template class SecondOrderSVFBandPassCoefficients<std::complex<float> >;
  template class SecondOrderSVFBandPassCoefficients<std::complex<double> >;
  template class SecondOrderSVFHighPassCoefficients<float>;
  template class SecondOrderSVFHighPassCoefficients<double>;
  template class SecondOrderSVFHighPassCoefficients<std::complex<float> >;
  template class SecondOrderSVFHighPassCoefficients<std::complex<double> >;
  template class SecondOrderSVFNotchCoefficients<float>;
  template class SecondOrderSVFNotchCoefficients<double>;
  template class SecondOrderSVFNotchCoefficients<std::complex<float> >;
  template class SecondOrderSVFNotchCoefficients<std::complex<double> >;
  template class SecondOrderSVFPeakCoefficients<float>;
  template class SecondOrderSVFPeakCoefficients<double>;
  template class SecondOrderSVFPeakCoefficients<std::complex<float> >;
  template class SecondOrderSVFPeakCoefficients<std::complex<double> >;
  template class SecondOrderSVFBellCoefficients<float>;
  template class SecondOrderSVFBellCoefficients<double>;
  template class SecondOrderSVFBellCoefficients<std::complex<float> >;
  template class SecondOrderSVFBellCoefficients<std::complex<double> >;
  template class SecondOrderSVFLowShelfCoefficients<float>;
  template class SecondOrderSVFLowShelfCoefficients<double>;
  template class SecondOrderSVFLowShelfCoefficients<std::complex<float> >;
  template class SecondOrderSVFLowShelfCoefficients<std::complex<double> >;
  template class SecondOrderSVFHighShelfCoefficients<float>;
  template class SecondOrderSVFHighShelfCoefficients<double>;
  template class SecondOrderSVFHighShelfCoefficients<std::complex<float> >;
  template class SecondOrderSVFHighShelfCoefficients<std::complex<double> >;

  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<std::complex<double> > >;
}
