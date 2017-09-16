/**
 * \file Chebyshev2Filter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/Chebyshev2Filter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template class Chebyshev2LowPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev2LowPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev2HighPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev2HighPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev2BandPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev2BandPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev2BandStopCoefficients<simdpp::float32<4> >;
  template class Chebyshev2BandStopCoefficients<simdpp::float64<4> >;
  
  template class SimpleIIRFilter<Chebyshev2LowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2LowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev2HighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2HighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandStopCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev2BandStopCoefficients<simdpp::float64<4> > >;
}
