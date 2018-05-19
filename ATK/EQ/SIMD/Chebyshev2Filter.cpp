/**
 * \file Chebyshev2Filter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SIMD/Chebyshev2Filter.h>

#include <ATK/EQ/Chebyshev2Filter.hxx>
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
  template class Chebyshev2LowPassCoefficients<simdpp::float64<2> >;
  template class Chebyshev2HighPassCoefficients<simdpp::float64<2> >;
  template class Chebyshev2BandPassCoefficients<simdpp::float64<2> >;
  template class Chebyshev2BandStopCoefficients<simdpp::float64<2> >;

  template class Chebyshev2LowPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev2LowPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev2HighPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev2HighPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev2BandPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev2BandPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev2BandStopCoefficients<simdpp::float32<4> >;
  template class Chebyshev2BandStopCoefficients<simdpp::float64<4> >;
  
  template class Chebyshev2LowPassCoefficients<simdpp::float32<8> >;
  template class Chebyshev2LowPassCoefficients<simdpp::float64<8> >;
  template class Chebyshev2HighPassCoefficients<simdpp::float32<8> >;
  template class Chebyshev2HighPassCoefficients<simdpp::float64<8> >;
  template class Chebyshev2BandPassCoefficients<simdpp::float32<8> >;
  template class Chebyshev2BandPassCoefficients<simdpp::float64<8> >;
  template class Chebyshev2BandStopCoefficients<simdpp::float32<8> >;
  template class Chebyshev2BandStopCoefficients<simdpp::float64<8> >;

  template class SimpleIIRFilter<Chebyshev2LowPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<Chebyshev2HighPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<Chebyshev2BandPassCoefficients<simdpp::float64<2> > >;
  template class SimpleIIRFilter<Chebyshev2BandStopCoefficients<simdpp::float64<2> > >;

  template class SimpleIIRFilter<Chebyshev2LowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2LowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev2HighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2HighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandStopCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandStopCoefficients<simdpp::float64<4> > >;
  
  template class SimpleIIRFilter<Chebyshev2LowPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<Chebyshev2LowPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<Chebyshev2HighPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<Chebyshev2HighPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<Chebyshev2BandPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<Chebyshev2BandPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<Chebyshev2BandStopCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<Chebyshev2BandStopCoefficients<simdpp::float64<8> > >;

  template class IIRTDF2Filter<Chebyshev2LowPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<Chebyshev2HighPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<Chebyshev2BandPassCoefficients<simdpp::float64<2> > >;
  template class IIRTDF2Filter<Chebyshev2BandStopCoefficients<simdpp::float64<2> > >;

  template class IIRTDF2Filter<Chebyshev2LowPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<Chebyshev2LowPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<Chebyshev2HighPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<Chebyshev2HighPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<Chebyshev2BandPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<Chebyshev2BandPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<Chebyshev2BandStopCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<Chebyshev2BandStopCoefficients<simdpp::float64<4> > >;
  
  template class IIRTDF2Filter<Chebyshev2LowPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<Chebyshev2LowPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<Chebyshev2HighPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<Chebyshev2HighPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<Chebyshev2BandPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<Chebyshev2BandPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<Chebyshev2BandStopCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<Chebyshev2BandStopCoefficients<simdpp::float64<8> > >;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassChebyshev2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev2LowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassChebyshev2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev2HighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassChebyshev2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev2BandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandStopChebyshev2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<Chebyshev2BandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createLowPassChebyshev2TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev2LowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createHighPassChebyshev2TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev2HighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandPassChebyshev2TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev2BandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, gsl::index VL>
    std::unique_ptr<BaseFilter> createBandStopChebyshev2TDF2Filter(gsl::index nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<Chebyshev2BandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassChebyshev2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassChebyshev2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassChebyshev2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopChebyshev2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassChebyshev2TDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassChebyshev2TDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassChebyshev2TDF2Filter) ((gsl::index) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, gsl::index VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopChebyshev2TDF2Filter) ((gsl::index) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2TDF2Filter<double, 2>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createLowPassChebyshev2TDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createHighPassChebyshev2TDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandPassChebyshev2TDF2Filter<double, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2TDF2Filter<float, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2TDF2Filter<double, 4>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2TDF2Filter<float, 8>(gsl::index)),
    (template ATK_EQSIMD_EXPORT std::unique_ptr<BaseFilter> createBandStopChebyshev2TDF2Filter<double, 8>(gsl::index)));
}
