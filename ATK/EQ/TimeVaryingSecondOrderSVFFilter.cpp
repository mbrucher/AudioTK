/**
 * \file TimeVaryingSecondOrderSVFFilter.cpp
 */

#include "TimeVaryingSecondOrderSVFFilter.h"

#include <boost/math/constants/constants.hpp>

#include <cassert>

namespace ATK
{
  template<typename SVFCoefficients>
  class TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::SVFState
  {
  public:
    typename SVFCoefficients::DataType iceq1{0};
    typename SVFCoefficients::DataType iceq2{0};
  };
  
  template<typename SVFCoefficients>
  TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::TimeVaryingSecondOrderSVFFilter(gsl::index nb_channels)
  :SVFCoefficients(nb_channels), state(std::make_unique<SVFState[]>(nb_channels))
  {
  }

  template<typename SVFCoefficients>
  TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::~TimeVaryingSecondOrderSVFFilter()
  {
  }

  template<typename SVFCoefficients>
  void TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::full_setup()
  {
    state = std::make_unique<SVFState[]>(nb_input_ports - 1);
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFFilter<DataType>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports - 1 == nb_output_ports);

    for(gsl::index i = 0; i < size; ++i)
    {
      update_coeffs(converted_inputs[0][i]);
      
      for(gsl::index j = 0; j < nb_input_ports - 1; ++j)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[j+1];
        DataType* ATK_RESTRICT output = outputs[j];

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
  TimeVaryingSecondOrderSVFBaseCoefficients<DataType>::TimeVaryingSecondOrderSVFBaseCoefficients(gsl::index nb_channels)
  :TypedBaseFilter<DataType>(1 + nb_channels, nb_channels)
  {
  }

  template<typename DataType_>
  void TimeVaryingSecondOrderSVFBaseCoefficients<DataType_>::set_Q(DataType_ Q)
  {
    if(Q <= 0)
    {
      throw std::out_of_range("Q must be strictly positive");
    }
    this->Q = Q;
    setup();
  }

  template<typename DataType>
  DataType TimeVaryingSecondOrderSVFBaseCoefficients<DataType>::get_Q() const
  {
    return Q;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFLowPassCoefficients<DataType_>::TimeVaryingSecondOrderSVFLowPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFLowPassCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1/Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 0;
    m1 = 0;
    m2 = 1;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFBandPassCoefficients<DataType_>::TimeVaryingSecondOrderSVFBandPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFBandPassCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 0;
    m1 = 1;
    m2 = 0;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFHighPassCoefficients<DataType_>::TimeVaryingSecondOrderSVFHighPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFHighPassCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = -1;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFNotchCoefficients<DataType_>::TimeVaryingSecondOrderSVFNotchCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFNotchCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = 0;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFPeakCoefficients<DataType_>::TimeVaryingSecondOrderSVFPeakCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFPeakCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = -k;
    m2 = 2;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFBellCoefficients<DataType_>::TimeVaryingSecondOrderSVFBellCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
    
  }
  
  template<typename DataType_>
  void TimeVaryingSecondOrderSVFBellCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    if(gain <= 0)
    {
      throw std::out_of_range("Gain must be strictly positive");
    }
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  DataType TimeVaryingSecondOrderSVFBellCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFBellCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1 / (Q * gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain * gain - 1);
    m2 = 0;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFLowShelfCoefficients<DataType_>::TimeVaryingSecondOrderSVFLowShelfCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
    
  }

  template<typename DataType_>
  void TimeVaryingSecondOrderSVFLowShelfCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  DataType TimeVaryingSecondOrderSVFLowShelfCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFLowShelfCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1 / Q;
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain - 1);
    m2 = gain * gain - 1;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFHighShelfCoefficients<DataType_>::TimeVaryingSecondOrderSVFHighShelfCoefficients(gsl::index nb_channels)
  :Parent(nb_channels)
  {
  }

  template<typename DataType_>
  void TimeVaryingSecondOrderSVFHighShelfCoefficients<DataType_>::set_gain(DataType_ gain)
  {
    this->gain = gain;
    setup();
  }

  template<typename DataType>
  DataType TimeVaryingSecondOrderSVFHighShelfCoefficients<DataType>::get_gain() const
  {
    return gain;
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFHighShelfCoefficients<DataType>::update_coeffs(DataType g) const
  {
    auto k = 1 / (Q* gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = gain * gain;
    m1 = k * (1 - gain) * gain;
    m2 = 1 - gain * gain;
  }

#if ATK_ENABLE_INSTANTIATION
  template class TimeVaryingSecondOrderSVFBaseCoefficients<float>;

  template class TimeVaryingSecondOrderSVFLowPassCoefficients<float>;
  template class TimeVaryingSecondOrderSVFBandPassCoefficients<float>;
  template class TimeVaryingSecondOrderSVFHighPassCoefficients<float>;
  template class TimeVaryingSecondOrderSVFNotchCoefficients<float>;
  template class TimeVaryingSecondOrderSVFPeakCoefficients<float>;
  template class TimeVaryingSecondOrderSVFBellCoefficients<float>;
  template class TimeVaryingSecondOrderSVFLowShelfCoefficients<float>;
  template class TimeVaryingSecondOrderSVFHighShelfCoefficients<float>;

  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<float> >;
#endif
  template class TimeVaryingSecondOrderSVFBaseCoefficients<double>;

  template class TimeVaryingSecondOrderSVFLowPassCoefficients<double>;
  template class TimeVaryingSecondOrderSVFBandPassCoefficients<double>;
  template class TimeVaryingSecondOrderSVFHighPassCoefficients<double>;
  template class TimeVaryingSecondOrderSVFNotchCoefficients<double>;
  template class TimeVaryingSecondOrderSVFPeakCoefficients<double>;
  template class TimeVaryingSecondOrderSVFBellCoefficients<double>;
  template class TimeVaryingSecondOrderSVFLowShelfCoefficients<double>;
  template class TimeVaryingSecondOrderSVFHighShelfCoefficients<double>;

  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<double> >;
}
