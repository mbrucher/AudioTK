/**
 * \file OversamplingFilter.cpp
 */

#include <ATK/Tools/SIMD/OversamplingFilter.h>
#include <ATK/Tools/OversamplingFilter.hxx>
#include <ATK/Core/TypeTraits.h>

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
  template class OversamplingFilter<simdpp::float64<2>, Oversampling6points5order_2<double> >;
  template class OversamplingFilter<simdpp::float32<4>, Oversampling6points5order_2<float> >;
  template class OversamplingFilter<simdpp::float64<4>, Oversampling6points5order_2<double> >;
  template class OversamplingFilter<simdpp::float32<8>, Oversampling6points5order_2<float> >;
  template class OversamplingFilter<simdpp::float64<8>, Oversampling6points5order_2<double> >;
  template class OversamplingFilter<simdpp::float64<2>, Oversampling6points5order_4<double> >;
  template class OversamplingFilter<simdpp::float32<4>, Oversampling6points5order_4<float> >;
  template class OversamplingFilter<simdpp::float64<4>, Oversampling6points5order_4<double> >;
  template class OversamplingFilter<simdpp::float32<8>, Oversampling6points5order_4<float> >;
  template class OversamplingFilter<simdpp::float64<8>, Oversampling6points5order_4<double> >;
  template class OversamplingFilter<simdpp::float64<2>, Oversampling6points5order_8<double> >;
  template class OversamplingFilter<simdpp::float32<4>, Oversampling6points5order_8<float> >;
  template class OversamplingFilter<simdpp::float64<4>, Oversampling6points5order_8<double> >;
  template class OversamplingFilter<simdpp::float32<8>, Oversampling6points5order_8<float> >;
  template class OversamplingFilter<simdpp::float64<8>, Oversampling6points5order_8<double> >;
  template class OversamplingFilter<simdpp::float64<2>, Oversampling6points5order_16<double> >;
  template class OversamplingFilter<simdpp::float32<4>, Oversampling6points5order_16<float> >;
  template class OversamplingFilter<simdpp::float64<4>, Oversampling6points5order_16<double> >;
  template class OversamplingFilter<simdpp::float32<8>, Oversampling6points5order_16<float> >;
  template class OversamplingFilter<simdpp::float64<8>, Oversampling6points5order_16<double> >;
  template class OversamplingFilter<simdpp::float64<2>, Oversampling6points5order_32<double> >;
  template class OversamplingFilter<simdpp::float32<4>, Oversampling6points5order_32<float> >;
  template class OversamplingFilter<simdpp::float64<4>, Oversampling6points5order_32<double> >;
  template class OversamplingFilter<simdpp::float32<8>, Oversampling6points5order_32<float> >;
  template class OversamplingFilter<simdpp::float64<8>, Oversampling6points5order_32<double> >;
  
  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_2(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new OversamplingFilter<typename SIMDTypeTraits<DataType>::template SIMDType<VL>, Oversampling6points5order_2<DataType> >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_4(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new OversamplingFilter<typename SIMDTypeTraits<DataType>::template SIMDType<VL>, Oversampling6points5order_4<DataType> >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_8(gsl::index nb_channels)
    {
        return std::unique_ptr<BaseFilter>(new OversamplingFilter<typename SIMDTypeTraits<DataType>::template SIMDType<VL>, Oversampling6points5order_8<DataType> >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_16(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new OversamplingFilter<typename SIMDTypeTraits<DataType>::template SIMDType<VL>, Oversampling6points5order_16<DataType> >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_32(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new OversamplingFilter<typename SIMDTypeTraits<DataType>::template SIMDType<VL>, Oversampling6points5order_32<DataType> >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createOversamplingFilter6points5order_2) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createOversamplingFilter6points5order_4) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createOversamplingFilter6points5order_8) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createOversamplingFilter6points5order_16) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createOversamplingFilter6points5order_32) ((gsl::index) nb_channels))

  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_2<double, 2>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_2<float, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_2<double, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_2<float, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_2<double, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_4<double, 2>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_4<float, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_4<double, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_4<float, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_4<double, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_8<double, 2>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_8<float, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_8<double, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_8<float, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_8<double, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_16<double, 2>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_16<float, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_16<double, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_16<float, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_16<double, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_32<double, 2>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_32<float, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_32<double, 4>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_32<float, 8>(gsl::index)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_32<double, 8>(gsl::index)));
}
