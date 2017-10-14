/**
 * \file RobertBristowJohnsonFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SIMD/RobertBristowJohnsonFilter.h>
#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/RobertBristowJohnsonFilter.hxx>
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
  template class RobertBristowJohnsonLowPassCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonLowPassCoefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonHighPassCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonHighPassCoefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonBandPassCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonBandPassCoefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonBandPass2Coefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonBandPass2Coefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonAllPassCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonAllPassCoefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonBandStopCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonBandStopCoefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<simdpp::float64<4> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<simdpp::float32<4> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<simdpp::float64<4> >;

  template class RobertBristowJohnsonLowPassCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonLowPassCoefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonHighPassCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonHighPassCoefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonBandPassCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonBandPassCoefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonBandPass2Coefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonBandPass2Coefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonAllPassCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonAllPassCoefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonBandStopCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonBandStopCoefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonLowShelvingCoefficients<simdpp::float64<8> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<simdpp::float32<8> >;
  template class RobertBristowJohnsonHighShelvingCoefficients<simdpp::float64<8> >;
  
  template class SimpleIIRFilter<RobertBristowJohnsonLowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonLowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandStopCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandStopCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonAllPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonAllPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float64<4> > >;

  template class SimpleIIRFilter<RobertBristowJohnsonLowPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonLowPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandStopCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandStopCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonAllPassCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonAllPassCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float64<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float32<8> > >;
  template class SimpleIIRFilter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float64<8> > >;
  
  template class IIRTDF2Filter<RobertBristowJohnsonLowPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonLowPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandStopCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandStopCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonAllPassCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonAllPassCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float64<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float32<4> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float64<4> > >;
  
  template class IIRTDF2Filter<RobertBristowJohnsonLowPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonLowPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPass2Coefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandStopCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandStopCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonAllPassCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonAllPassCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonBandPassPeakCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonLowShelvingCoefficients<simdpp::float64<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float32<8> > >;
  template class IIRTDF2Filter<RobertBristowJohnsonHighShelvingCoefficients<simdpp::float64<8> > >;

  namespace SIMDPP_ARCH_NAMESPACE
  {
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonBandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonBandPass2Coefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonBandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonAllPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonLowShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonFilter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new SimpleIIRFilter<RobertBristowJohnsonHighShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonLowPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonHighPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonBandPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonBandPass2Coefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonBandStopCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonAllPassCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonBandPassPeakCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonLowShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
    template<typename DataType, std::size_t VL>
    std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonTDF2Filter(std::size_t nb_channels)
    {
      return std::unique_ptr<BaseFilter>(new IIRTDF2Filter<RobertBristowJohnsonHighShelvingCoefficients<typename SIMDTypeTraits<DataType>::template SIMDType<VL> > >(nb_channels));
    }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPass2RobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createAllPassRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassPeakRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowShelvingRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighShelvingRobertBristowJohnsonFilter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowPassRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighPassRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPass2RobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandStopRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createAllPassRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBandPassPeakRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createLowShelvingRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createHighShelvingRobertBristowJohnsonTDF2Filter) ((std::size_t) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonFilter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonFilter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonFilter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonFilter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonFilter<double, 8>(std::size_t)));
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowPassRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighPassRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPass2RobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandStopRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createAllPassRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createBandPassPeakRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createLowShelvingRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonTDF2Filter<float, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonTDF2Filter<double, 4>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonTDF2Filter<float, 8>(std::size_t)),
    (template std::unique_ptr<BaseFilter> createHighShelvingRobertBristowJohnsonTDF2Filter<double, 8>(std::size_t)));
}
