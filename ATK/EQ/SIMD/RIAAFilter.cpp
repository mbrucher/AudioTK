/**
 * \file RIAAFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/RIAAFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template class RIAACoefficients<simdpp::float32<4> >;
  template class RIAACoefficients<simdpp::float64<4> >;
  
  template class SimpleIIRFilter<RIAACoefficients<simdpp::float32<4> > >;
  template class SimpleIIRFilter<RIAACoefficients<simdpp::float64<4> > >;
}
