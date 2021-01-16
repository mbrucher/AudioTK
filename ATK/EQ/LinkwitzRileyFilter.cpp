/**
 * \file LinkwitzRileyFilter.cpp
 */

#include "LinkwitzRileyFilter.hxx"
#include <ATK/EQ/FourthOrderFilter.hxx>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class FourthOrderBaseCoefficients<float>;

  template class ATK_EQ_EXPORT LinkwitzRileyLowPassCoefficients<float>;
  template class ATK_EQ_EXPORT LinkwitzRileyLowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT LinkwitzRileyLowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT LinkwitzRileyHighPassCoefficients<float>;
  template class ATK_EQ_EXPORT LinkwitzRileyHighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT LinkwitzRileyHighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT LinkwitzRiley4LowPassCoefficients<float>;
  template class ATK_EQ_EXPORT LinkwitzRiley4LowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT LinkwitzRiley4LowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT LinkwitzRiley4HighPassCoefficients<float>;
  template class ATK_EQ_EXPORT LinkwitzRiley4HighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT LinkwitzRiley4HighPassCoefficients<std::complex<double> >;
#endif
  template class FourthOrderBaseCoefficients<double>;
  template class ATK_EQ_EXPORT LinkwitzRileyLowPassCoefficients<double>;
  template class ATK_EQ_EXPORT LinkwitzRileyHighPassCoefficients<double>;
  template class ATK_EQ_EXPORT LinkwitzRiley4LowPassCoefficients<double>;
  template class ATK_EQ_EXPORT LinkwitzRiley4HighPassCoefficients<double>;
}
