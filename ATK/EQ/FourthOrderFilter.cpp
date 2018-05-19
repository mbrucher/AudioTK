/**
 * \file FourthOrderFilter.cpp
 */

#include <ATK/EQ/FourthOrderFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<float>::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<float>::setup();
  template ATK_EQ_EXPORT float FourthOrderBaseCoefficients<float>::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<float>::set_cut_frequency(float);
  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<double>::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<double>::setup();
  template ATK_EQ_EXPORT double FourthOrderBaseCoefficients<double>::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<double>::set_cut_frequency(double);

  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<std::complex<float> >::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<float> >::setup();
  template ATK_EQ_EXPORT float FourthOrderBaseCoefficients<std::complex<float> >::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<float> >::set_cut_frequency(float);
  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<std::complex<double> >::FourthOrderBaseCoefficients(gsl::index);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<double> >::setup();
  template ATK_EQ_EXPORT double FourthOrderBaseCoefficients<std::complex<double> >::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<double> >::set_cut_frequency(double);
}
