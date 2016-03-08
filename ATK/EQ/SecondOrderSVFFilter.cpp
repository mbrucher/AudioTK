/**
 * \file SecondOrderSVFFilter.cpp
 */

#include "SecondOrderSVFFilter.h"

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType>
  SecondOrderSVFFilter<DataType>::SecondOrderSVFFilter()
  :iceq1(0), iceq2(0)
  {
  }
  
  template<typename DataType>
  void SecondOrderSVFFilter<DataType>::full_setup()
  {
    iceq1 = 0;
    iceq2 = 0;
  }

  template<typename DataType>
  void SecondOrderSVFFilter<DataType>::process_impl(int64_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];

    for(int64_t i = 0; i < size; ++i)
    {
      DataType v3 = input[i] - iceq2;
      DataType v1 = a1 * iceq1 + a2 * v3;
      DataType v2 = iceq2 + a2 * iceq1 + a3 * v3;
      iceq1 = 2 * v1 - iceq1;
      iceq2 = 2 * v2 - iceq2;

      output[i] = m0 * input[i] + m1 * v1 + m2 * v2;
    }
  }
  
  template<typename DataType>
  BaseSecondOrderSVFCoefficients<DataType>::BaseSecondOrderSVFCoefficients()
  :TypedBaseFilter<DataType>(1, 1)
  {
  }

  template<typename DataType>
  void BaseSecondOrderSVFCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }

  template<typename DataType>
  DataType BaseSecondOrderSVFCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template<typename DataType>
  void BaseSecondOrderSVFCoefficients<DataType>::set_Q(DataType Q)
  {
    this->Q = Q;
    setup();
  }

  template<typename DataType>
  DataType BaseSecondOrderSVFCoefficients<DataType>::get_Q() const
  {
    return Q;
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
    m2 = -2;
  }

  template class SecondOrderSVFFilter<LowSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<LowSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<BandSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<BandSecondOrderSVFCoefficients<double> >;
  template class SecondOrderSVFFilter<HighSecondOrderSVFCoefficients<float> >;
  template class SecondOrderSVFFilter<HighSecondOrderSVFCoefficients<double> >;
}
