/**
 * \file QuaternionConvertFilter.cpp
 */

#include <ATK/Core/SIMD/QuaternionConvertFilter.h>

#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<typename DataType_, typename SIMDType>
  RealToQuaternionFilter<DataType_, SIMDType>::RealToQuaternionFilter(std::size_t nb_channels)
  :Parent(SIMDType::length * nb_channels, nb_channels)
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

    for(std::size_t j = 0; j < nb_output_ports; ++j)
    {
      const auto* ATK_RESTRICT input1 = converted_inputs[4 * j + 0];
      const auto* ATK_RESTRICT input2 = converted_inputs[4 * j + 1];
      const auto* ATK_RESTRICT input3 = converted_inputs[4 * j + 2];
      const auto* ATK_RESTRICT input4 = converted_inputs[4 * j + 3];
      auto* ATK_RESTRICT output = outputs[j];
      
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
  }

  template<typename SIMDType, typename DataType__>
  QuaternionToRealFilter<SIMDType, DataType__>::QuaternionToRealFilter(std::size_t nb_channels)
  :Parent(nb_channels, SIMDType::length * nb_channels)
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

    for(std::size_t j = 0; j < nb_input_ports; ++j)
    {
      const auto* ATK_RESTRICT input = converted_inputs[j];
      auto* ATK_RESTRICT output1 = outputs[4 * j + 0];
      auto* ATK_RESTRICT output2 = outputs[4 * j + 1];
      auto* ATK_RESTRICT output3 = outputs[4 * j + 2];
      auto* ATK_RESTRICT output4 = outputs[4 * j + 3];
      
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
  }

  template class RealToQuaternionFilter<float, simdpp::float32<4> >;
  template class RealToQuaternionFilter<double, simdpp::float64<4> >;
  template class QuaternionToRealFilter<simdpp::float32<4>, float>;
  template class QuaternionToRealFilter<simdpp::float64<4>, double>;
  
namespace SIMDPP_ARCH_NAMESPACE
{
  template<typename DataType_, typename SIMDType>
  std::unique_ptr<BaseFilter> ATK_CORE_EXPORT createRealToQuaternionFilter(std::size_t nb_channels)
  {
    return std::unique_ptr<BaseFilter>(new RealToQuaternionFilter<DataType_, SIMDType>>(nb_channels));
  }

  template<typename SIMDType, typename DataType__>
  std::unique_ptr<BaseFilter> ATK_CORE_EXPORT createQuaternionToRealFilter(std::size_t nb_channels)
  {
    return std::unique_ptr<BaseFilter>(new QuaternionToRealFilter<SIMDType, DataType__>(nb_channels));
  }
  
  template std::unique_ptr<BaseFilter> createRealToQuaternionFilter<float,simdpp::float32<4> >(std::size_t);
  template std::unique_ptr<BaseFilter> createRealToQuaternionFilter<double,simdpp::float64<4> >(std::size_t);
  template std::unique_ptr<BaseFilter> createQuaternionToRealFilter<simdpp::float32<4>,float>(std::size_t);
  template std::unique_ptr<BaseFilter> createQuaternionToRealFilter<simdpp::float64<4>,double>(std::size_t);
}
}
