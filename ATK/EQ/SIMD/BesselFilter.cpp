/**
 * \file BesselFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/BesselFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template class BesselLowPassCoefficients<simdpp::float32<4> >;
  template class BesselLowPassCoefficients<simdpp::float64<4> >;
  template class BesselHighPassCoefficients<simdpp::float32<4> >;
  template class BesselHighPassCoefficients<simdpp::float64<4> >;
  template class BesselBandPassCoefficients<simdpp::float32<4> >;
  template class BesselBandPassCoefficients<simdpp::float64<4> >;
  template class BesselBandStopCoefficients<simdpp::float32<4> >;
  template class BesselBandStopCoefficients<simdpp::float64<4> >;
  
  template class SimpleIIRFilter<BesselLowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<BesselLowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<BesselHighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<BesselHighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<BesselBandPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<BesselBandPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<BesselBandStopCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<BesselBandStopCoefficients<simdpp::float64<4> > >;
}
