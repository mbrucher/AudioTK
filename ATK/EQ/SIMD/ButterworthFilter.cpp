/**
 * \file ButterworthFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/ButterworthFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template class ButterworthLowPassCoefficients<simdpp::float32<4> >;
  template class ButterworthLowPassCoefficients<simdpp::float64<4> >;
  template class ButterworthHighPassCoefficients<simdpp::float32<4> >;
  template class ButterworthHighPassCoefficients<simdpp::float64<4> >;
  template class ButterworthBandPassCoefficients<simdpp::float32<4> >;
  template class ButterworthBandPassCoefficients<simdpp::float64<4> >;
  template class ButterworthBandStopCoefficients<simdpp::float32<4> >;
  template class ButterworthBandStopCoefficients<simdpp::float64<4> >;
  
  template class SimpleIIRFilter<ButterworthLowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<ButterworthLowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<ButterworthHighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<ButterworthHighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<ButterworthBandPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<ButterworthBandPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<ButterworthBandStopCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<ButterworthBandStopCoefficients<simdpp::float64<4> > >;
}
