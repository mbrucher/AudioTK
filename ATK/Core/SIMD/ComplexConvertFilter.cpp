/**
 * \file ComplexConvertFilter.cpp
 */

#include <ATK/Core/SIMD/ComplexConvertFilter.h>

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
  RealToComplexFilter<DataType_, SIMDType>::RealToComplexFilter(std::size_t nb_channels)
  :Parent(2 * nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_, typename SIMDType>
  RealToComplexFilter<DataType_, SIMDType>::~RealToComplexFilter()
  {
  }

  template<typename DataType_, typename SIMDType>
  void RealToComplexFilter<DataType_, SIMDType>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == SIMDType::length * nb_output_ports);
    
    for(std::size_t j = 0; j < nb_output_ports; ++j)
    {
      const auto* ATK_RESTRICT input1 = converted_inputs[2 * j + 0];
      const auto* ATK_RESTRICT input2 = converted_inputs[2 * j + 1];
      auto* ATK_RESTRICT output = outputs[j];
      
      for (std::size_t i = 0; i < size; ++i)
      {
        DataType_ data[SIMDType::length];
        data[0] = input1[i];
        data[1] = input2[i];
        output[i] = simdpp::load(data);
      }
    }
  }

  template<typename SIMDType, typename DataType__>
  ComplexToRealFilter<SIMDType, DataType__>::ComplexToRealFilter(std::size_t nb_channels)
    :Parent(nb_channels, 2 * nb_channels)
  {
  }

  template<typename SIMDType, typename DataType__>
  ComplexToRealFilter<SIMDType, DataType__>::~ComplexToRealFilter()
  {
  }

  template<typename SIMDType, typename DataType__>
  void ComplexToRealFilter<SIMDType, DataType__>::process_impl(std::size_t size) const
  {
    assert(SIMDType::length * nb_input_ports == nb_output_ports);
    
    for(std::size_t j = 0; j < nb_input_ports; ++j)
    {
      const auto* ATK_RESTRICT input = converted_inputs[j];
      auto* ATK_RESTRICT output1 = outputs[2 * j + 0];
      auto* ATK_RESTRICT output2 = outputs[2 * j + 1];
      
      for (std::size_t i = 0; i < size; ++i)
      {
        DataType__ data[SIMDType::length];
        
        simdpp::store(data, input[i]);
        output1[i] = data[0];
        output2[i] = data[1];
      }
    }
  }

  template class RealToComplexFilter<double, simdpp::float64<2>>;
  template class ComplexToRealFilter<simdpp::float64<2>, double>;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType_>
    std::unique_ptr<BaseFilter> createRealToComplexFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new RealToComplexFilter<DataType_, typename SIMDTypeTraits<DataType_>::template SIMDType<2> >(nb_channels));
    }
    
    template<typename DataType__>
    std::unique_ptr<BaseFilter> createComplexToRealFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new ComplexToRealFilter<typename SIMDTypeTraits<DataType__>::template SIMDType<2>, DataType__>(nb_channels));
    }
  }
  
SIMDPP_MAKE_DISPATCHER((template<typename DataType_>) (<DataType_>) (std::unique_ptr<BaseFilter>) (createRealToComplexFilter)
                        ((std::size_t) nb_channels))
SIMDPP_MAKE_DISPATCHER((template<typename DataType__>) (<DataType__>) (std::unique_ptr<BaseFilter>) (createComplexToRealFilter)
                        ((std::size_t) nb_channels))
  
SIMDPP_INSTANTIATE_DISPATCHER(
	(template ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createRealToComplexFilter<double>(std::size_t)),
	(template ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createComplexToRealFilter<double>(std::size_t)));
}
