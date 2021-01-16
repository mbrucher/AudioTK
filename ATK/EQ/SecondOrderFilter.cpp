/**
 * \file SecondOrderFilter.cpp
 */

#include "SecondOrderFilter.hxx"
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
#if !(defined(_MSC_VER) || __cplusplus >= 201703L)
  template<typename DataType_>
  const gsl::index SecondOrderCoreCoefficients<DataType_>::in_order = 2;
  template<typename DataType_>
  const gsl::index SecondOrderCoreCoefficients<DataType_>::out_order = 2;
#endif
  
#if ATK_ENABLE_INSTANTIATION
  template class SecondOrderCoreCoefficients<float>;
  template class SecondOrderCoreCoefficients<std::complex<float> >;
  template class SecondOrderCoreCoefficients<std::complex<double> >;

  template class SecondOrderBaseCoefficients<float>;
  template class SecondOrderBaseCoefficients<std::complex<float> >;
  template class SecondOrderBaseCoefficients<std::complex<double> >;
  
  template class ATK_EQ_EXPORT SecondOrderBandPassCoefficients<float>;
  template class ATK_EQ_EXPORT SecondOrderBandPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SecondOrderBandPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT SecondOrderLowPassCoefficients<float>;
  template class ATK_EQ_EXPORT SecondOrderLowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SecondOrderLowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT SecondOrderHighPassCoefficients<float>;
  template class ATK_EQ_EXPORT SecondOrderHighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SecondOrderHighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT SecondOrderBandPassPeakCoefficients<float>;
  template class ATK_EQ_EXPORT SecondOrderBandPassPeakCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SecondOrderBandPassPeakCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT SecondOrderAllPassCoefficients<float>;
  template class ATK_EQ_EXPORT SecondOrderAllPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SecondOrderAllPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT SecondOrderLowShelvingCoefficients<float>;
  template class ATK_EQ_EXPORT SecondOrderLowShelvingCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SecondOrderLowShelvingCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT SecondOrderHighShelvingCoefficients<float>;
  template class ATK_EQ_EXPORT SecondOrderHighShelvingCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SecondOrderHighShelvingCoefficients<std::complex<double> >;
#endif
  template class SecondOrderCoreCoefficients<double>;
  template class SecondOrderBaseCoefficients<double>;
  template class ATK_EQ_EXPORT SecondOrderBandPassCoefficients<double>;
  template class ATK_EQ_EXPORT SecondOrderLowPassCoefficients<double>;
  template class ATK_EQ_EXPORT SecondOrderHighPassCoefficients<double>;
  template class ATK_EQ_EXPORT SecondOrderBandPassPeakCoefficients<double>;
  template class ATK_EQ_EXPORT SecondOrderAllPassCoefficients<double>;
  template class ATK_EQ_EXPORT SecondOrderLowShelvingCoefficients<double>;
  template class ATK_EQ_EXPORT SecondOrderHighShelvingCoefficients<double>;
}
