/**
 * \file SecondOrderSVFFilter.cpp
 */

#include "SecondOrderSVFFilter.h"

#include <boost/math/constants/constants.hpp>

#include <cassert>

namespace ATK
{
  template<typename SVFCoefficients>
  class SecondOrderSVFFilter<SVFCoefficients>::SVFState
  {
  public:
    typename SVFCoefficients::DataType iceq1{0};
    typename SVFCoefficients::DataType iceq2{0};
  };
  
  template<typename SVFCoefficients>
  SecondOrderSVFFilter<SVFCoefficients>::SecondOrderSVFFilter(gsl::index nb_channels)
  :SVFCoefficients(nb_channels), state(std::make_unique<SVFState[]>(nb_channels))
  {
  }

  template<typename SVFCoefficients>
  SecondOrderSVFFilter<SVFCoefficients>::~SecondOrderSVFFilter()
  {
  }

  template<typename SVFCoefficients>
  void SecondOrderSVFFilter<SVFCoefficients>::full_setup()
  {
    state = std::make_unique<SVFState[]>(nb_input_ports);
  }

  template<typename DataType>
  void SecondOrderSVFFilter<DataType>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == nb_output_ports);
    
    for(gsl::index j = 0; j < nb_input_ports; ++j)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[j];
      DataType* ATK_RESTRICT output = outputs[j];
      
      for(gsl::index i = 0; i < size; ++i)
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
  SecondOrderSVFBaseCoefficients<DataType>::SecondOrderSVFBaseCoefficients(gsl::index nb_channels)
  :TypedBaseFilter<DataType>(nb_channels, nb_channels)
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
  SecondOrderSVFLowPassCoefficients<DataType_>::SecondOrderSVFLowPassCoefficients(gsl::index nb_channels)
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
  SecondOrderSVFBandPassCoefficients<DataType_>::SecondOrderSVFBandPassCoefficients(gsl::index nb_channels)
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
  SecondOrderSVFHighPassCoefficients<DataType_>::SecondOrderSVFHighPassCoefficients(gsl::index nb_channels)
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
  SecondOrderSVFNotchCoefficients<DataType_>::SecondOrderSVFNotchCoefficients(gsl::index nb_channels)
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
    m2 = 0;
  }

  template<typename DataType_>
  SecondOrderSVFPeakCoefficients<DataType_>::SecondOrderSVFPeakCoefficients(gsl::index nb_channels)
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
    m2 = 2;
  }

  template<typename DataType_>
  SecondOrderSVFBellCoefficients<DataType_>::SecondOrderSVFBellCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
    
  }
  
  template<typename DataType_>
  void SecondOrderSVFBellCoefficients<DataType_>::set_gain(CoeffDataType gain)
  {
    if(gain <= 0)
    {
      throw std::out_of_range("Gain must be positive");
    }
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
    auto k = 1 / (Q * gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain * gain - 1);
    m2 = 0;
  }

  template<typename DataType_>
  SecondOrderSVFLowShelfCoefficients<DataType_>::SecondOrderSVFLowShelfCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
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
  SecondOrderSVFHighShelfCoefficients<DataType_>::SecondOrderSVFHighShelfCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
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
    auto k = 1 / (Q * gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = gain * gain;
    m1 = k * (1 - gain) * gain;
    m2 = 1 - gain * gain;
  }

#if ATK_ENABLE_INSTANTIATION
  template class SecondOrderSVFBaseCoefficients<float>;
  template class SecondOrderSVFBaseCoefficients<std::complex<float> >;
  template class SecondOrderSVFBaseCoefficients<std::complex<double> >;

  template class SecondOrderSVFLowPassCoefficients<float>;
  template class SecondOrderSVFLowPassCoefficients<std::complex<float> >;
  template class SecondOrderSVFLowPassCoefficients<std::complex<double> >;
  template class SecondOrderSVFBandPassCoefficients<float>;
  template class SecondOrderSVFBandPassCoefficients<std::complex<float> >;
  template class SecondOrderSVFBandPassCoefficients<std::complex<double> >;
  template class SecondOrderSVFHighPassCoefficients<float>;
  template class SecondOrderSVFHighPassCoefficients<std::complex<float> >;
  template class SecondOrderSVFHighPassCoefficients<std::complex<double> >;
  template class SecondOrderSVFNotchCoefficients<float>;
  template class SecondOrderSVFNotchCoefficients<std::complex<float> >;
  template class SecondOrderSVFNotchCoefficients<std::complex<double> >;
  template class SecondOrderSVFPeakCoefficients<float>;
  template class SecondOrderSVFPeakCoefficients<std::complex<float> >;
  template class SecondOrderSVFPeakCoefficients<std::complex<double> >;
  template class SecondOrderSVFBellCoefficients<float>;
  template class SecondOrderSVFBellCoefficients<std::complex<float> >;
  template class SecondOrderSVFBellCoefficients<std::complex<double> >;
  template class SecondOrderSVFLowShelfCoefficients<float>;
  template class SecondOrderSVFLowShelfCoefficients<std::complex<float> >;
  template class SecondOrderSVFLowShelfCoefficients<std::complex<double> >;
  template class SecondOrderSVFHighShelfCoefficients<float>;
  template class SecondOrderSVFHighShelfCoefficients<std::complex<float> >;
  template class SecondOrderSVFHighShelfCoefficients<std::complex<double> >;

  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<std::complex<double> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<float> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<std::complex<float> > >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<std::complex<double> > >;
#endif
  template class SecondOrderSVFBaseCoefficients<double>;
  
  template class SecondOrderSVFLowPassCoefficients<double>;
  template class SecondOrderSVFBandPassCoefficients<double>;
  template class SecondOrderSVFHighPassCoefficients<double>;
  template class SecondOrderSVFNotchCoefficients<double>;
  template class SecondOrderSVFPeakCoefficients<double>;
  template class SecondOrderSVFBellCoefficients<double>;
  template class SecondOrderSVFLowShelfCoefficients<double>;
  template class SecondOrderSVFHighShelfCoefficients<double>;
  
  template class SecondOrderSVFFilter<SecondOrderSVFLowPassCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBandPassCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighPassCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFNotchCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFPeakCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFBellCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFLowShelfCoefficients<double> >;
  template class SecondOrderSVFFilter<SecondOrderSVFHighShelfCoefficients<double> >;
}
