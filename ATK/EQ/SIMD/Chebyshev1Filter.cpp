/**
 * \file Chebyshev1Filter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SIMD/Chebyshev1Filter.h>

#include <ATK/EQ/Chebyshev1Filter.hxx>
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
  template class ATK_EQSIMD_EXPORT Chebyshev1LowPassCoefficients<simdpp::float64<2> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1HighPassCoefficients<simdpp::float64<2> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandPassCoefficients<simdpp::float64<2> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandStopCoefficients<simdpp::float64<2> >;

  template class ATK_EQSIMD_EXPORT Chebyshev1LowPassCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1LowPassCoefficients<simdpp::float64<4> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1HighPassCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1HighPassCoefficients<simdpp::float64<4> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandPassCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandPassCoefficients<simdpp::float64<4> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandStopCoefficients<simdpp::float32<4> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandStopCoefficients<simdpp::float64<4> >;
  
  template class ATK_EQSIMD_EXPORT Chebyshev1LowPassCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1LowPassCoefficients<simdpp::float64<8> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1HighPassCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1HighPassCoefficients<simdpp::float64<8> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandPassCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandPassCoefficients<simdpp::float64<8> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandStopCoefficients<simdpp::float32<8> >;
  template class ATK_EQSIMD_EXPORT Chebyshev1BandStopCoefficients<simdpp::float64<8> >;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev1LowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev1HighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev1BandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev1BandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev1LowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev1HighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev1BandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev1BandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassChebyshev1Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassChebyshev1Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassChebyshev1Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopChebyshev1Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassChebyshev1TDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassChebyshev1TDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassChebyshev1TDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopChebyshev1TDF2Filter) ((gsl::index) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev1TDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev1TDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev1TDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev1TDF2Filter<double, 8>(gsl::index)));
}
