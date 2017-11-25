/**
 * \file InPointerFilter.cpp
 */

#include <ATK/Core/InPointerFilter.hxx>

#include <complex>

namespace ATK
{
  template class InPointerFilter<std::int16_t>;
  template class InPointerFilter<std::int32_t>;
  template class InPointerFilter<std::int64_t>;
  template class InPointerFilter<float>;
  template class InPointerFilter<double>;
  template class InPointerFilter<std::complex<float>>;
  template class InPointerFilter<std::complex<double>>;
}
