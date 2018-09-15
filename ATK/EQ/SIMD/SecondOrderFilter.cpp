/**
 * \file SecondOrderFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SIMD/SecondOrderFilter.h>
#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/SecondOrderFilter.hxx>
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
#if !(defined(_MSC_VER) || __cplusplus >= 201703L)
  template<typename DataType_>
  const gsl::index SecondOrderCoreCoefficients<DataType_>::in_order = 2;
  template<typename DataType_>
  const gsl::index SecondOrderCoreCoefficients<DataType_>::out_order = 2;
#endif

  template class SecondOrderBaseCoefficients<simdpp::float64<2> >;
  template class SecondOrderBaseCoefficients<simdpp::float32<4> >;
  template class SecondOrderBaseCoefficients<simdpp::float64<4> >;
  template class SecondOrderBaseCoefficients<simdpp::float32<8> >;
  template class SecondOrderBaseCoefficients<simdpp::float64<8> >;

  template class SecondOrderBandPassCoefficients<simdpp::float64<2> >;
  template class SecondOrderLowPassCoefficients<simdpp::float64<2> >;
  template class SecondOrderHighPassCoefficients<simdpp::float64<2> >;
  template class SecondOrderBandPassPeakCoefficients<simdpp::float64<2> >;
  template class SecondOrderAllPassCoefficients<simdpp::float64<2> >;
  template class SecondOrderLowShelvingCoefficients<simdpp::float64<2> >;
  template class SecondOrderHighShelvingCoefficients<simdpp::float64<2> >;

  template class SecondOrderBandPassCoefficients<simdpp::float32<4> >;
  template class SecondOrderBandPassCoefficients<simdpp::float64<4> >;
  template class SecondOrderLowPassCoefficients<simdpp::float32<4> >;
  template class SecondOrderLowPassCoefficients<simdpp::float64<4> >;
  template class SecondOrderHighPassCoefficients<simdpp::float32<4> >;
  template class SecondOrderHighPassCoefficients<simdpp::float64<4> >;
  template class SecondOrderBandPassPeakCoefficients<simdpp::float32<4> >;
  template class SecondOrderBandPassPeakCoefficients<simdpp::float64<4> >;
  template class SecondOrderAllPassCoefficients<simdpp::float32<4> >;
  template class SecondOrderAllPassCoefficients<simdpp::float64<4> >;
  template class SecondOrderLowShelvingCoefficients<simdpp::float32<4> >;
  template class SecondOrderLowShelvingCoefficients<simdpp::float64<4> >;
  template class SecondOrderHighShelvingCoefficients<simdpp::float32<4> >;
  template class SecondOrderHighShelvingCoefficients<simdpp::float64<4> >;
  
  template class SecondOrderBandPassCoefficients<simdpp::float32<8> >;
  template class SecondOrderBandPassCoefficients<simdpp::float64<8> >;
  template class SecondOrderLowPassCoefficients<simdpp::float32<8> >;
  template class SecondOrderLowPassCoefficients<simdpp::float64<8> >;
  template class SecondOrderHighPassCoefficients<simdpp::float32<8> >;
  template class SecondOrderHighPassCoefficients<simdpp::float64<8> >;
  template class SecondOrderBandPassPeakCoefficients<simdpp::float32<8> >;
  template class SecondOrderBandPassPeakCoefficients<simdpp::float64<8> >;
  template class SecondOrderAllPassCoefficients<simdpp::float32<8> >;
  template class SecondOrderAllPassCoefficients<simdpp::float64<8> >;
  template class SecondOrderLowShelvingCoefficients<simdpp::float32<8> >;
  template class SecondOrderLowShelvingCoefficients<simdpp::float64<8> >;
  template class SecondOrderHighShelvingCoefficients<simdpp::float32<8> >;
  template class SecondOrderHighShelvingCoefficients<simdpp::float64<8> >;

  template class SimpleIIRFilter<SecondOrderBandPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<SecondOrderLowPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<SecondOrderHighPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<SecondOrderBandPassPeakCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<SecondOrderAllPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<SecondOrderLowShelvingCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<SecondOrderHighShelvingCoefficients<simdpp::float64<2> > >;

  template class SimpleIIRFilter<SecondOrderBandPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<SecondOrderBandPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<SecondOrderLowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<SecondOrderLowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<SecondOrderHighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<SecondOrderHighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<SecondOrderBandPassPeakCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<SecondOrderBandPassPeakCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<SecondOrderAllPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<SecondOrderAllPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<SecondOrderLowShelvingCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<SecondOrderLowShelvingCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<SecondOrderHighShelvingCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<SecondOrderHighShelvingCoefficients<simdpp::float64<4> > >;
  
  template class SimpleIIRFilter<SecondOrderBandPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<SecondOrderBandPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<SecondOrderLowPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<SecondOrderLowPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<SecondOrderHighPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<SecondOrderHighPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<SecondOrderBandPassPeakCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<SecondOrderBandPassPeakCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<SecondOrderAllPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<SecondOrderAllPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<SecondOrderLowShelvingCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<SecondOrderLowShelvingCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<SecondOrderHighShelvingCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<SecondOrderHighShelvingCoefficients<simdpp::float64<8> > >;

  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<simdpp::float64<2> > >;

  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<simdpp::float64<4> > >;
  
  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<SecondOrderBandPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<SecondOrderLowPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<SecondOrderHighPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<SecondOrderAllPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<SecondOrderLowShelvingCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<SecondOrderHighShelvingCoefficients<simdpp::float64<8> > >;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<SecondOrderLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<SecondOrderHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<SecondOrderBandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<SecondOrderAllPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<SecondOrderBandPassPeakCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<SecondOrderLowShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<SecondOrderHighShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<SecondOrderLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<SecondOrderHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<SecondOrderBandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<SecondOrderAllPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<SecondOrderBandPassPeakCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<SecondOrderLowShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<SecondOrderHighShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassSecondOrderFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassSecondOrderFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassSecondOrderFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createAllPassSecondOrderFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassPeakSecondOrderFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowShelvingSecondOrderFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighShelvingSecondOrderFilter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassSecondOrderTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassSecondOrderTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassSecondOrderTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createAllPassSecondOrderTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassPeakSecondOrderTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowShelvingSecondOrderTDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighShelvingSecondOrderTDF2Filter) ((gsl::index) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderFilter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderFilter<double, 8>(gsl::index)));
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowPassSecondOrderTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighPassSecondOrderTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassSecondOrderTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createAllPassSecondOrderTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createBandPassPeakSecondOrderTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createLowShelvingSecondOrderTDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD2_EXPORT std::unique_ptr<BaseFilter> createHighShelvingSecondOrderTDF2Filter<double, 8>(gsl::index)));
}
