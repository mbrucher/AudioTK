/**
 * \file FourthOrderFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/FourthOrderFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<simdpp::float32<4> >::FourthOrderBaseCoefficients(std::size_t);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<simdpp::float32<4> >::setup();
  template ATK_EQ_EXPORT float  FourthOrderBaseCoefficients<simdpp::float32<4> >::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<simdpp::float32<4> >::set_cut_frequency(float);
  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<simdpp::float64<4> >::FourthOrderBaseCoefficients(std::size_t);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<4> >::setup();
  template ATK_EQ_EXPORT double  FourthOrderBaseCoefficients<simdpp::float64<4> >::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<4> >::set_cut_frequency(double);
}
