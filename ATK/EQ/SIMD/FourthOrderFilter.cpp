/**
 * \file FourthOrderFilter.cpp
 * For SIMD
 */

#include <simdpp/simd.h>

#include <ATK/EQ/FourthOrderFilter.hxx>
#include <ATK/EQ/SimpleIIRFilter.h>

namespace ATK
{
  template ATK_EQSIMD_EXPORT FourthOrderBaseCoefficients<simdpp::float64<2> >::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<2> >::setup();
  template ATK_EQSIMD_EXPORT double  FourthOrderBaseCoefficients<simdpp::float64<2> >::get_cut_frequency() const;
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<2> >::set_cut_frequency(double);

  template ATK_EQSIMD_EXPORT FourthOrderBaseCoefficients<simdpp::float32<4> >::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float32<4> >::setup();
  template ATK_EQSIMD_EXPORT float  FourthOrderBaseCoefficients<simdpp::float32<4> >::get_cut_frequency() const;
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float32<4> >::set_cut_frequency(float);
  template ATK_EQSIMD_EXPORT FourthOrderBaseCoefficients<simdpp::float64<4> >::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<4> >::setup();
  template ATK_EQSIMD_EXPORT double  FourthOrderBaseCoefficients<simdpp::float64<4> >::get_cut_frequency() const;
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<4> >::set_cut_frequency(double);
  
  template ATK_EQSIMD_EXPORT FourthOrderBaseCoefficients<simdpp::float32<8> >::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float32<8> >::setup();
  template ATK_EQSIMD_EXPORT float  FourthOrderBaseCoefficients<simdpp::float32<8> >::get_cut_frequency() const;
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float32<8> >::set_cut_frequency(float);
  template ATK_EQSIMD_EXPORT FourthOrderBaseCoefficients<simdpp::float64<8> >::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<8> >::setup();
  template ATK_EQSIMD_EXPORT double  FourthOrderBaseCoefficients<simdpp::float64<8> >::get_cut_frequency() const;
  template ATK_EQSIMD_EXPORT void FourthOrderBaseCoefficients<simdpp::float64<8> >::set_cut_frequency(double);
}
