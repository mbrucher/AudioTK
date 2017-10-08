/**
 * \file RobertBristowJohnsonFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/RobertBristowJohnsonFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

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
}
