/**
 * \file BesselFilter.cpp
 */

#include <ATK/EQ/BesselFilter.hxx>

namespace ATK
{
  template class ATK_EQ_EXPORT BesselLowPassCoefficients<float>;
  template class ATK_EQ_EXPORT BesselLowPassCoefficients<double>;
  template class ATK_EQ_EXPORT BesselLowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT BesselLowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT BesselHighPassCoefficients<float>;
  template class ATK_EQ_EXPORT BesselHighPassCoefficients<double>;
  template class ATK_EQ_EXPORT BesselHighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT BesselHighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT BesselBandPassCoefficients<float>;
  template class ATK_EQ_EXPORT BesselBandPassCoefficients<double>;
  template class ATK_EQ_EXPORT BesselBandPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT BesselBandPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT BesselBandStopCoefficients<float>;
  template class ATK_EQ_EXPORT BesselBandStopCoefficients<double>;
  template class ATK_EQ_EXPORT BesselBandStopCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT BesselBandStopCoefficients<std::complex<double> >;
}
