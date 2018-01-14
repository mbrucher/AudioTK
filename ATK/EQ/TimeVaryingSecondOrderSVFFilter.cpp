/**
 * \file TimeVaryingSecondOrderSVFFilter.cpp
 */

#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.h>

#include <cassert>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename SVFCoefficients>
  struct TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::SVFState
  {
    typename SVFCoefficients::DataType iceq1;
    typename SVFCoefficients::DataType iceq2;
    
    SVFState()
    :iceq1(0), iceq2(0)
    {
    }
  };
  
  template<typename SVFCoefficients>
  TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::TimeVaryingSecondOrderSVFFilter(std::size_t nb_channels)
  :SVFCoefficients(nb_channels), state(new SVFState[nb_channels])
  {
  }

  template<typename SVFCoefficients>
  TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::~TimeVaryingSecondOrderSVFFilter()
  {
  }

  template<typename SVFCoefficients>
  void TimeVaryingSecondOrderSVFFilter<SVFCoefficients>::full_setup()
  {
    state.reset(new SVFState[nb_input_ports - 1]);
  }

  template<typename DataType>
  void TimeVaryingSecondOrderSVFFilter<DataType>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports - 1 == nb_output_ports);

    for(std::size_t i = 0; i < size; ++i)
    {
      update_coeffs(converted_inputs[0][i]);
      
      for(unsigned int j = 0; j < nb_input_ports - 1; ++j)
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
  TimeVaryingSecondOrderSVFBaseCoefficients<DataType>::TimeVaryingSecondOrderSVFBaseCoefficients(std::size_t nb_channels)
  :TypedBaseFilter<DataType>(1 + nb_channels, nb_channels),Q(1)
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
  TimeVaryingSecondOrderSVFLowPassCoefficients<DataType_>::TimeVaryingSecondOrderSVFLowPassCoefficients(std::size_t nb_channels)
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
  TimeVaryingSecondOrderSVFBandPassCoefficients<DataType_>::TimeVaryingSecondOrderSVFBandPassCoefficients(std::size_t nb_channels)
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
  TimeVaryingSecondOrderSVFHighPassCoefficients<DataType_>::TimeVaryingSecondOrderSVFHighPassCoefficients(std::size_t nb_channels)
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
  TimeVaryingSecondOrderSVFNotchCoefficients<DataType_>::TimeVaryingSecondOrderSVFNotchCoefficients(std::size_t nb_channels)
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
  TimeVaryingSecondOrderSVFPeakCoefficients<DataType_>::TimeVaryingSecondOrderSVFPeakCoefficients(std::size_t nb_channels)
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
  TimeVaryingSecondOrderSVFBellCoefficients<DataType_>::TimeVaryingSecondOrderSVFBellCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), gain(0)
  {
    
  }
  
  template<typename DataType_>
  void TimeVaryingSecondOrderSVFBellCoefficients<DataType_>::set_gain(DataType_ gain)
  {
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
    auto k = 1 / (Q* gain);
    a1 = 1 / (1 + g * (g + k));
    a2 = g * a1;
    a3 = g * a2;
    m0 = 1;
    m1 = k * (gain * gain - 1);
    m2 = 0;
  }

  template<typename DataType_>
  TimeVaryingSecondOrderSVFLowShelfCoefficients<DataType_>::TimeVaryingSecondOrderSVFLowShelfCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), gain(0)
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
  TimeVaryingSecondOrderSVFHighShelfCoefficients<DataType_>::TimeVaryingSecondOrderSVFHighShelfCoefficients(std::size_t nb_channels)
  :Parent(nb_channels), gain(0)
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

  template class TimeVaryingSecondOrderSVFBaseCoefficients<float>;
  template class TimeVaryingSecondOrderSVFBaseCoefficients<double>;

  template class TimeVaryingSecondOrderSVFLowPassCoefficients<float>;
  template class TimeVaryingSecondOrderSVFLowPassCoefficients<double>;
  template class TimeVaryingSecondOrderSVFBandPassCoefficients<float>;
  template class TimeVaryingSecondOrderSVFBandPassCoefficients<double>;
  template class TimeVaryingSecondOrderSVFHighPassCoefficients<float>;
  template class TimeVaryingSecondOrderSVFHighPassCoefficients<double>;
  template class TimeVaryingSecondOrderSVFNotchCoefficients<float>;
  template class TimeVaryingSecondOrderSVFNotchCoefficients<double>;
  template class TimeVaryingSecondOrderSVFPeakCoefficients<float>;
  template class TimeVaryingSecondOrderSVFPeakCoefficients<double>;
  template class TimeVaryingSecondOrderSVFBellCoefficients<float>;
  template class TimeVaryingSecondOrderSVFBellCoefficients<double>;
  template class TimeVaryingSecondOrderSVFLowShelfCoefficients<float>;
  template class TimeVaryingSecondOrderSVFLowShelfCoefficients<double>;
  template class TimeVaryingSecondOrderSVFHighShelfCoefficients<float>;
  template class TimeVaryingSecondOrderSVFHighShelfCoefficients<double>;

  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowPassCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBandPassCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighPassCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFNotchCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFPeakCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFBellCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFLowShelfCoefficients<double> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<float> >;
  template class TimeVaryingSecondOrderSVFFilter<TimeVaryingSecondOrderSVFHighShelfCoefficients<double> >;
}
