/**
 * \file QuaternionConvertFilter.cpp
 */

#include "QuaternionConvertFilter.h"

#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<typename DataType_, typename SIMDType>
  RealToQuaternionFilter<DataType_, SIMDType>::RealToQuaternionFilter(/*std::size_t nb_channels*/)
  :Parent(SIMDType::length, 1/*SIMDType::length * nb_channels, nb_channels*/)
  {
  }
  
  template<typename DataType_, typename SIMDType>
  RealToQuaternionFilter<DataType_, SIMDType>::~RealToQuaternionFilter()
  {
  }

  template<typename DataType_, typename SIMDType>
  void RealToQuaternionFilter<DataType_, SIMDType>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == SIMDType::length * nb_output_ports);

    const auto* ATK_RESTRICT input1 = converted_inputs[0];
    const auto* ATK_RESTRICT input2 = converted_inputs[1];
    const auto* ATK_RESTRICT input3 = converted_inputs[2];
    const auto* ATK_RESTRICT input4 = converted_inputs[3];
    auto* ATK_RESTRICT output = outputs[0];
    
    for (std::size_t i = 0; i < size; ++i)
    {
      DataType_ data[SIMDType::length];
      data[0] = input1[i];
      data[1] = input2[i];
      data[2] = input3[i];
      data[3] = input4[i];
      output[i] = simdpp::load(data);
    }
  }

  template<typename SIMDType, typename DataType__>
  QuaternionToRealFilter<SIMDType, DataType__>::QuaternionToRealFilter(/*std::size_t nb_channels*/)
  :Parent(1, SIMDType::length/*nb_channels, SIMDType::length * nb_channels*/)
  {
  }

  template<typename SIMDType, typename DataType__>
  QuaternionToRealFilter<SIMDType, DataType__>::~QuaternionToRealFilter()
  {
  }

  template<typename SIMDType, typename DataType__>
  void QuaternionToRealFilter<SIMDType, DataType__>::process_impl(std::size_t size) const
  {
    assert(SIMDType::length * nb_input_ports == nb_output_ports);

    const auto* ATK_RESTRICT input = converted_inputs[0];
    auto* ATK_RESTRICT output1 = outputs[0];
    auto* ATK_RESTRICT output2 = outputs[1];
    auto* ATK_RESTRICT output3 = outputs[2];
    auto* ATK_RESTRICT output4 = outputs[3];

    for (std::size_t i = 0; i < size; ++i)
    {
      DataType__ data[SIMDType::length];
      
      simdpp::store(data, input[i]);
      output1[i] = data[0];
      output2[i] = data[1];
      output3[i] = data[2];
      output4[i] = data[3];
    }
  }

  template class RealToQuaternionFilter<float, simdpp::float32<4> >;
  template class RealToQuaternionFilter<double, simdpp::float64<4> >;
  template class QuaternionToRealFilter<simdpp::float32<4>, float>;
  template class QuaternionToRealFilter<simdpp::float64<4>, double>;
}
