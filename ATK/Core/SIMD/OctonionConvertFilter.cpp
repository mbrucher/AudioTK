/**
 * \file OctonionConvertFilter.cpp
 */

#include <ATK/Core/SIMD/OctonionConvertFilter.h>

#include <simdpp/simd.h>

#include <simdpp/dispatch/dispatcher.h>
#include <simdpp/dispatch/get_arch_gcc_builtin_cpu_supports.h>
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>

#if SIMDPP_HAS_GET_ARCH_RAW_CPUID
# define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_raw_cpuid()
#elif SIMDPP_HAS_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS
# define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_gcc_builtin_cpu_supports()
#elif SIMDPP_HAS_GET_ARCH_LINUX_CPUINFO
# define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_linux_cpuinfo()
#else
# error "Unsupported platform"
#endif

namespace ATK
{
  template<typename DataType_, typename SIMDType>
  RealToOctonionFilter<DataType_, SIMDType>::RealToOctonionFilter(std::size_t nb_channels)
  :Parent(SIMDType::length * nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_, typename SIMDType>
  RealToOctonionFilter<DataType_, SIMDType>::~RealToOctonionFilter()
  {
  }

  template<typename DataType_, typename SIMDType>
  void RealToOctonionFilter<DataType_, SIMDType>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == SIMDType::length * nb_output_ports);

    for(std::size_t j = 0; j < nb_output_ports; ++j)
    {
      const auto* ATK_RESTRICT input1 = converted_inputs[8 * j + 0];
      const auto* ATK_RESTRICT input2 = converted_inputs[8 * j + 1];
      const auto* ATK_RESTRICT input3 = converted_inputs[8 * j + 2];
      const auto* ATK_RESTRICT input4 = converted_inputs[8 * j + 3];
      const auto* ATK_RESTRICT input5 = converted_inputs[8 * j + 4];
      const auto* ATK_RESTRICT input6 = converted_inputs[8 * j + 5];
      const auto* ATK_RESTRICT input7 = converted_inputs[8 * j + 6];
      const auto* ATK_RESTRICT input8 = converted_inputs[8 * j + 7];
      auto* ATK_RESTRICT output = outputs[j];
      
      for (std::size_t i = 0; i < size; ++i)
      {
        alignas(32) DataType_ data[SIMDType::length];
        data[0] = input1[i];
        data[1] = input2[i];
        data[2] = input3[i];
        data[3] = input4[i];
        data[4] = input5[i];
        data[5] = input6[i];
        data[6] = input7[i];
        data[7] = input8[i];
        output[i] = simdpp::load(data);
      }
    }
  }

  template<typename SIMDType, typename DataType__>
  OctonionToRealFilter<SIMDType, DataType__>::OctonionToRealFilter(std::size_t nb_channels)
  :Parent(nb_channels, SIMDType::length * nb_channels)
  {
  }

  template<typename SIMDType, typename DataType__>
  OctonionToRealFilter<SIMDType, DataType__>::~OctonionToRealFilter()
  {
  }

  template<typename SIMDType, typename DataType__>
  void OctonionToRealFilter<SIMDType, DataType__>::process_impl(std::size_t size) const
  {
    assert(SIMDType::length * nb_input_ports == nb_output_ports);

    for(std::size_t j = 0; j < nb_input_ports; ++j)
    {
      const auto* ATK_RESTRICT input = converted_inputs[j];
      auto* ATK_RESTRICT output1 = outputs[8 * j + 0];
      auto* ATK_RESTRICT output2 = outputs[8 * j + 1];
      auto* ATK_RESTRICT output3 = outputs[8 * j + 2];
      auto* ATK_RESTRICT output4 = outputs[8 * j + 3];
      auto* ATK_RESTRICT output5 = outputs[8 * j + 4];
      auto* ATK_RESTRICT output6 = outputs[8 * j + 5];
      auto* ATK_RESTRICT output7 = outputs[8 * j + 6];
      auto* ATK_RESTRICT output8 = outputs[8 * j + 7];
      
      for (std::size_t i = 0; i < size; ++i)
      {
        alignas(32) DataType__ data[SIMDType::length];
        
        simdpp::store(data, input[i]);
        output1[i] = data[0];
        output2[i] = data[1];
        output3[i] = data[2];
        output4[i] = data[3];
        output5[i] = data[4];
        output6[i] = data[5];
        output7[i] = data[6];
        output8[i] = data[7];
      }
    }
  }

  template class RealToOctonionFilter<float, simdpp::float32<8> >;
  template class RealToOctonionFilter<double, simdpp::float64<8> >;
  template class OctonionToRealFilter<simdpp::float32<8>, float>;
  template class OctonionToRealFilter<simdpp::float64<8>, double>;
  
namespace SIMDPP_ARCH_NAMESPACE
{
  template<typename DataType_>
  std::unique_ptr<BaseFilter> createRealToOctonionFilter(std::size_t nb_channels)
  {
    return std::unique_ptr<BaseFilter>(new RealToOctonionFilter<DataType_, typename SIMDTypeTraits<DataType_>::template SIMDType<8> >(nb_channels));
  }

  template<typename DataType__>
  std::unique_ptr<BaseFilter> createOctonionToRealFilter(std::size_t nb_channels)
  {
    return std::unique_ptr<BaseFilter>(new OctonionToRealFilter<typename SIMDTypeTraits<DataType__>::template SIMDType<8>, DataType__>(nb_channels));
  }
}
  
SIMDPP_MAKE_DISPATCHER((template<typename DataType_>) (<DataType_>) (std::unique_ptr<BaseFilter>) (createRealToOctonionFilter)
                        ((std::size_t) nb_channels))
SIMDPP_MAKE_DISPATCHER((template<typename DataType__>) (<DataType__>) (std::unique_ptr<BaseFilter>) (createOctonionToRealFilter)
                        ((std::size_t) nb_channels))

SIMDPP_INSTANTIATE_DISPATCHER(
	(template ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createRealToOctonionFilter<float>(std::size_t)),
	(template ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createRealToOctonionFilter<double>(std::size_t)),
	(template ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createOctonionToRealFilter<float>(std::size_t)),
	(template ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createOctonionToRealFilter<double>(std::size_t)));
}
