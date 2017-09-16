/**
 * \file SecondOrderFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/SecondOrderFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template class SecondOrderBaseCoefficients<simdpp::float32<4> >;
  template class SecondOrderBaseCoefficients<simdpp::float64<4> >;
  
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
}
