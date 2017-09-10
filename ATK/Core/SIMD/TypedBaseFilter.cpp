/**
 * \file TypedBaseFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/Core/TypedBaseFilter.hxx>

namespace ATK
{
  template class TypedBaseFilter<simdpp::float32<4> >;
  template class TypedBaseFilter<simdpp::float64<4> >;
}
