/**
 * \file BesselFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SIMD/BesselFilter.h>

#include <ATK/EQ/BesselFilter.hxx>
#include <ATK/EQ/IIRFilter.h>
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
  template class ATK_EQSIMD_EXPORT BesselLowPassCoefficients<simdpp::float64<2> >;
  template class ATK_EQSIMD_EXPORT BesselHighPassCoefficients<simdpp::float64<2> >;
  template class ATK_EQSIMD_EXPORT BesselBandPassCoefficients<simdpp::float64<2> >;
  template class ATK_EQSIMD_EXPORT BesselBandStopCoefficients<simdpp::float64<2> >;

  template class ATK_EQSIMD_EXPORT BesselLowPassCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT BesselLowPassCoefficients<simdpp::float64<4> >;
  template class ATK_EQSIMD_EXPORT BesselHighPassCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT BesselHighPassCoefficients<simdpp::float64<4> >;
  template class ATK_EQSIMD_EXPORT BesselBandPassCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT BesselBandPassCoefficients<simdpp::float64<4> >;
  template class ATK_EQSIMD_EXPORT BesselBandStopCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT BesselBandStopCoefficients<simdpp::float64<4> >;

  template class ATK_EQSIMD_EXPORT BesselLowPassCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT BesselLowPassCoefficients<simdpp::float64<8> >;
  template class ATK_EQSIMD_EXPORT BesselHighPassCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT BesselHighPassCoefficients<simdpp::float64<8> >;
  template class ATK_EQSIMD_EXPORT BesselBandPassCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT BesselBandPassCoefficients<simdpp::float64<8> >;
  template class ATK_EQSIMD_EXPORT BesselBandStopCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT BesselBandStopCoefficients<simdpp::float64<8> >;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassBesselFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<BesselLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassBesselFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<BesselHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassBesselFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<BesselBandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandStopBesselFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<BesselBandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<BesselLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<BesselHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<BesselBandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<BesselBandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassBesselFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassBesselFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassBesselFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopBesselFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassBesselTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassBesselTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassBesselTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopBesselTDF2Filter) ((gsl::index) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassBesselTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassBesselTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopBesselTDF2Filter<double, 8>(gsl::index)));
}
