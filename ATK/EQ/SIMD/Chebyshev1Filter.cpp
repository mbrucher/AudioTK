/**
 * \file Chebyshev1Filter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/Chebyshev1Filter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template class Chebyshev1LowPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev1LowPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev1HighPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev1HighPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev1BandPassCoefficients<simdpp::float32<4> >;
  template class Chebyshev1BandPassCoefficients<simdpp::float64<4> >;
  template class Chebyshev1BandStopCoefficients<simdpp::float32<4> >;
  template class Chebyshev1BandStopCoefficients<simdpp::float64<4> >;
  
  template class SimpleIIRFilter<Chebyshev1LowPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev1LowPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev1HighPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev1HighPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev1BandPassCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev1BandPassCoefficients<simdpp::float64<4> > >;
  template class SimpleIIRFilter<Chebyshev1BandStopCoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<Chebyshev1BandStopCoefficients<simdpp::float64<4> > >;
}
