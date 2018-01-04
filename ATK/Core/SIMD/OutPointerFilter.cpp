/**
 * \file OutPointerFilter.cpp
 */

#include <simdpp/simd.h>

#include <ATK/Core/OutPointerFilter.hxx>

namespace ATK
{
  template class OutPointerFilter<simdpp::float64<2> >;
  template class OutPointerFilter<simdpp::float32<4> >;
  template class OutPointerFilter<simdpp::float64<4> >;
  template class OutPointerFilter<simdpp::float32<8> >;
  template class OutPointerFilter<simdpp::float64<8> >;
}
