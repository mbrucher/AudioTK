/**
 * \file InPointerFilter.cpp
 */

#include <simdpp/simd.h>

#include <ATK/Core/InPointerFilter.hxx>

namespace ATK
{
  template class InPointerFilter<simdpp::float64<2> >;
  template class InPointerFilter<simdpp::float32<4> >;
  template class InPointerFilter<simdpp::float64<4> >;
  template class InPointerFilter<simdpp::float32<8> >;
  template class InPointerFilter<simdpp::float64<8> >;
}
