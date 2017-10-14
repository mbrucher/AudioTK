/**
 * \file RIAAFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SIMD/RIAAFilter.h>
#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/RIAAFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

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

  template class RIAACoefficients<simdpp::float64<2> >;
  template class InverseRIAACoefficients<simdpp::float64<2> >;

  template class RIAACoefficients<simdpp::float32<4> >;
  template class RIAACoefficients<simdpp::float64<4> >;
  template class InverseRIAACoefficients<simdpp::float32<4> >;
  template class InverseRIAACoefficients<simdpp::float64<4> >;

  template class RIAACoefficients<simdpp::float32<8> >;
  template class RIAACoefficients<simdpp::float64<8> >;
  template class InverseRIAACoefficients<simdpp::float32<8> >;
  template class InverseRIAACoefficients<simdpp::float64<8> >;
  
  template class SimpleIIRFilter<RIAACoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<InverseRIAACoefficients<simdpp::float64<2> > >;

  template class SimpleIIRFilter<RIAACoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RIAACoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<InverseRIAACoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<InverseRIAACoefficients<simdpp::float64<4> > >;
  
  template class SimpleIIRFilter<RIAACoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RIAACoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<InverseRIAACoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<InverseRIAACoefficients<simdpp::float64<8> > >;

  template class IIRTDF2Filter<RIAACoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<InverseRIAACoefficients<simdpp::float64<2> > >;

  template class IIRTDF2Filter<RIAACoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RIAACoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<InverseRIAACoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<InverseRIAACoefficients<simdpp::float64<4> > >;

  template class IIRTDF2Filter<RIAACoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RIAACoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<InverseRIAACoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<InverseRIAACoefficients<simdpp::float64<8> > >;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createRIAAFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RIAACoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createInverseRIAAFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<InverseRIAACoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createRIAATDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RIAACoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createInverseRIAATDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<InverseRIAACoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createRIAAFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createInverseRIAAFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createRIAATDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createInverseRIAATDF2Filter) ((std::size_t) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template std::unique_ptr<BaseFilter> createRIAAFilter<double, 2>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAAFilter<double, 2>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAATDF2Filter<double, 2>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAATDF2Filter<double, 2>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAAFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAAFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAAFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAAFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAAFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAAFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAAFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAAFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAATDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAATDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAATDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAATDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAATDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createRIAATDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAATDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createInverseRIAATDF2Filter<double, 8>(std::size_t)));
}
