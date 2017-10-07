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
  template class TypedBaseFilter<simdpp::float32<8> >;
  template class TypedBaseFilter<simdpp::float64<8> >;

  template class TypedBaseFilter<float, simdpp::float32<4> >;
  template class TypedBaseFilter<double, simdpp::float64<4> >;
  template class TypedBaseFilter<float, simdpp::float32<8> >;
  template class TypedBaseFilter<double, simdpp::float64<8> >;

  template class TypedBaseFilter<simdpp::float32<4>, float>;
  template class TypedBaseFilter<simdpp::float64<4>, double>;
  template class TypedBaseFilter<simdpp::float32<8>, float>;
  template class TypedBaseFilter<simdpp::float64<8>, double>;
}
