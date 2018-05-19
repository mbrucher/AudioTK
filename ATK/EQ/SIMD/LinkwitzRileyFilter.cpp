/**
 * \file LinkwitzRileyFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SIMD/LinkwitzRileyFilter.h>

#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/LinkwitzRileyFilter.hxx>
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
  template class LinkwitzRileyLowPassCoefficients<simdpp::float64<2> >;
  template class LinkwitzRileyHighPassCoefficients<simdpp::float64<2> >;
  template class LinkwitzRiley4LowPassCoefficients<simdpp::float64<2> >;
  template class LinkwitzRiley4HighPassCoefficients<simdpp::float64<2> >;

  template class LinkwitzRileyLowPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRileyLowPassCoefficients<simdpp::float64<4> >;
  template class LinkwitzRileyHighPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRileyHighPassCoefficients<simdpp::float64<4> >;
  template class LinkwitzRiley4LowPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRiley4LowPassCoefficients<simdpp::float64<4> >;
  template class LinkwitzRiley4HighPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRiley4HighPassCoefficients<simdpp::float64<4> >;

  template class LinkwitzRileyLowPassCoefficients<simdpp::float32<8> >;
  template class LinkwitzRileyLowPassCoefficients<simdpp::float64<8> >;
  template class LinkwitzRileyHighPassCoefficients<simdpp::float32<8> >;
  template class LinkwitzRileyHighPassCoefficients<simdpp::float64<8> >;
  template class LinkwitzRiley4LowPassCoefficients<simdpp::float32<8> >;
  template class LinkwitzRiley4LowPassCoefficients<simdpp::float64<8> >;
  template class LinkwitzRiley4HighPassCoefficients<simdpp::float32<8> >;
  template class LinkwitzRiley4HighPassCoefficients<simdpp::float64<8> >;

  template class SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<simdpp::float64<2> > >;

  template class SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<simdpp::float64<4> > >;
  
  template class SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<simdpp::float64<8> > >;

  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<simdpp::float64<2> > >;

  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<simdpp::float64<4> > >;
  
  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<simdpp::float64<8> > >;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<LinkwitzRileyLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<LinkwitzRileyHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<LinkwitzRiley4LowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<LinkwitzRiley4HighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassLinkwitzRileyFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassLinkwitzRileyFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassLinkwitzRiley4Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassLinkwitzRiley4Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassLinkwitzRileyTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassLinkwitzRileyTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassLinkwitzRiley4TDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassLinkwitzRiley4TDF2Filter) ((gsl::index) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRileyTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRileyTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassLinkwitzRiley4TDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassLinkwitzRiley4TDF2Filter<double, 8>(gsl::index)));
}
