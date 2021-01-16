/**
 * \file TypedBaseFilter.cpp
 */

#include "TypedBaseFilter.hxx"

namespace ATK
{
  template class TypedBaseFilter<std::int16_t>;
  template class TypedBaseFilter<std::int32_t>;
  template class TypedBaseFilter<int64_t>;
  template class TypedBaseFilter<float>;
  template class TypedBaseFilter<double>;

  template class TypedBaseFilter<std::complex<float>>;
  template class TypedBaseFilter<std::complex<double>>;

  // These class allows to build a complex filter from 2 real inputs
  template class TypedBaseFilter<float, std::complex<float>>;
  template class TypedBaseFilter<double, std::complex<double>>;
  template class TypedBaseFilter<std::complex<float>, float>;
  template class TypedBaseFilter<std::complex<double>, double>;
  
  template class OutputArrayInterface<std::int16_t>;
  template class OutputArrayInterface<std::int32_t>;
  template class OutputArrayInterface<std::int64_t>;
  template class OutputArrayInterface<float>;
  template class OutputArrayInterface<double>;
  template class OutputArrayInterface<std::complex<float>>;
  template class OutputArrayInterface<std::complex<double>>;
}
