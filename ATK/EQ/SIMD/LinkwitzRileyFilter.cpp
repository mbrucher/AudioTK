/**
 * \file LinkwitzRileyFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/LinkwitzRileyFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template class LinkwitzRileyLowPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRileyLowPassCoefficients<simdpp::float64<4> >;
  template class LinkwitzRileyHighPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRileyHighPassCoefficients<simdpp::float64<4> >;
  template class LinkwitzRiley4LowPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRiley4LowPassCoefficients<simdpp::float64<4> >;
  template class LinkwitzRiley4HighPassCoefficients<simdpp::float32<4> >;
  template class LinkwitzRiley4HighPassCoefficients<simdpp::float64<4> >;
  
  template class SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRileyLowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRileyHighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4LowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<LinkwitzRiley4HighPassCoefficients<simdpp::float64<4> > >;
}
