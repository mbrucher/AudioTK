/**
 * \file Chebyshev2Filter.cpp
 */

#include <ATK/EQ/Chebyshev2Filter.hxx>

namespace ATK
{
  template class ATK_EQ_EXPORT Chebyshev2LowPassCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev2LowPassCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev2LowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev2LowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT Chebyshev2HighPassCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev2HighPassCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev2HighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev2HighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT Chebyshev2BandPassCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev2BandPassCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev2BandPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev2BandPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT Chebyshev2BandStopCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev2BandStopCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev2BandStopCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev2BandStopCoefficients<std::complex<double> >;
}
