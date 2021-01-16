/**
 * \file OversamplingFilter.cpp
 */

#include "OversamplingFilter.hxx"

#include <complex>

namespace ATK
{
#if ATK_ENABLE_INSTANTIATION
  template class Oversampling6points5order_2<float>;
  template class Oversampling6points5order_4<float>;
  template class Oversampling6points5order_8<float>;
  template class Oversampling6points5order_16<float>;
  template class Oversampling6points5order_32<float>;
  
  template class OversamplingFilter<float, Oversampling6points5order_2<float> >;
  template class OversamplingFilter<std::complex<float>, Oversampling6points5order_2<float> >;
  template class OversamplingFilter<std::complex<double>, Oversampling6points5order_2<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_4<float> >;
  template class OversamplingFilter<std::complex<float>, Oversampling6points5order_4<float> >;
  template class OversamplingFilter<std::complex<double>, Oversampling6points5order_4<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_8<float> >;
  template class OversamplingFilter<std::complex<float>, Oversampling6points5order_8<float> >;
  template class OversamplingFilter<std::complex<double>, Oversampling6points5order_8<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_16<float> >;
  template class OversamplingFilter<std::complex<float>, Oversampling6points5order_16<float> >;
  template class OversamplingFilter<std::complex<double>, Oversampling6points5order_16<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_32<float> >;
  template class OversamplingFilter<std::complex<float>, Oversampling6points5order_32<float> >;
  template class OversamplingFilter<std::complex<double>, Oversampling6points5order_32<double> >;
#endif
  template class Oversampling6points5order_2<double>;
  template class Oversampling6points5order_4<double>;
  template class Oversampling6points5order_8<double>;
  template class Oversampling6points5order_16<double>;
  template class Oversampling6points5order_32<double>;

  template class OversamplingFilter<double, Oversampling6points5order_2<double> >;
  template class OversamplingFilter<double, Oversampling6points5order_4<double> >;
  template class OversamplingFilter<double, Oversampling6points5order_8<double> >;
  template class OversamplingFilter<double, Oversampling6points5order_16<double> >;
  template class OversamplingFilter<double, Oversampling6points5order_32<double> >;
}
