/**
 * \file Utilities.cpp
 */

#include <ATK/Core/Utilities.hxx>
#include <simdpp/simd.h>

namespace ATK
{
  template class ConversionUtilities<simdpp::float64<2>, simdpp::float64<2> >;
  template class ConversionUtilities<simdpp::float32<4>, simdpp::float32<4> >;
  template class ConversionUtilities<simdpp::float64<4>, simdpp::float64<4> >;
  template class ConversionUtilities<simdpp::float32<8>, simdpp::float32<8> >;
  template class ConversionUtilities<simdpp::float64<8>, simdpp::float64<8> >;
}
