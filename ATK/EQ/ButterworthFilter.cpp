/**
 * \file ButterworthFilter.cpp
 */

#include <ATK/EQ/ButterworthFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class ButterworthLowPassCoefficients<float>;
  template class ButterworthLowPassCoefficients<double>;
  template class ButterworthLowPassCoefficients<std::complex<float> >;
  template class ButterworthLowPassCoefficients<std::complex<double> >;
  template class ButterworthHighPassCoefficients<float>;
  template class ButterworthHighPassCoefficients<double>;
  template class ButterworthHighPassCoefficients<std::complex<float> >;
  template class ButterworthHighPassCoefficients<std::complex<double> >;
  template class ButterworthBandPassCoefficients<float>;
  template class ButterworthBandPassCoefficients<double>;
  template class ButterworthBandPassCoefficients<std::complex<float> >;
  template class ButterworthBandPassCoefficients<std::complex<double> >;
  template class ButterworthBandStopCoefficients<float>;
  template class ButterworthBandStopCoefficients<double>;
  template class ButterworthBandStopCoefficients<std::complex<float> >;
  template class ButterworthBandStopCoefficients<std::complex<double> >;
  
  template class IIRFilter<ButterworthLowPassCoefficients<float> >;
  template class IIRFilter<ButterworthLowPassCoefficients<double> >;
  template class IIRFilter<ButterworthLowPassCoefficients<std::complex<float> > >;
  template class IIRFilter<ButterworthLowPassCoefficients<std::complex<double> > >;
  template class IIRFilter<ButterworthHighPassCoefficients<float> >;
  template class IIRFilter<ButterworthHighPassCoefficients<double> >;
  template class IIRFilter<ButterworthHighPassCoefficients<std::complex<float> > >;
  template class IIRFilter<ButterworthHighPassCoefficients<std::complex<double> > >;
  template class IIRFilter<ButterworthBandPassCoefficients<float> >;
  template class IIRFilter<ButterworthBandPassCoefficients<double> >;
  template class IIRFilter<ButterworthBandPassCoefficients<std::complex<float> > >;
  template class IIRFilter<ButterworthBandPassCoefficients<std::complex<double> > >;
  template class IIRFilter<ButterworthBandStopCoefficients<float> >;
  template class IIRFilter<ButterworthBandStopCoefficients<double> >;
  template class IIRFilter<ButterworthBandStopCoefficients<std::complex<float> > >;
  template class IIRFilter<ButterworthBandStopCoefficients<std::complex<double> > >;

  template class IIRTDF2Filter<ButterworthLowPassCoefficients<float> >;
  template class IIRTDF2Filter<ButterworthLowPassCoefficients<double> >;
  template class IIRTDF2Filter<ButterworthLowPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<ButterworthLowPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<ButterworthHighPassCoefficients<float> >;
  template class IIRTDF2Filter<ButterworthHighPassCoefficients<double> >;
  template class IIRTDF2Filter<ButterworthHighPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<ButterworthHighPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<ButterworthBandPassCoefficients<float> >;
  template class IIRTDF2Filter<ButterworthBandPassCoefficients<double> >;
  template class IIRTDF2Filter<ButterworthBandPassCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<ButterworthBandPassCoefficients<std::complex<double> > >;
  template class IIRTDF2Filter<ButterworthBandStopCoefficients<float> >;
  template class IIRTDF2Filter<ButterworthBandStopCoefficients<double> >;
  template class IIRTDF2Filter<ButterworthBandStopCoefficients<std::complex<float> > >;
  template class IIRTDF2Filter<ButterworthBandStopCoefficients<std::complex<double> > >;
}
