/**
 * \file Utilities.cpp
 */

#include "Utilities.hxx"

namespace ATK
{
  RuntimeError::RuntimeError(const std::string& what_arg)
  :std::runtime_error(what_arg)
  {
  }

  RuntimeError::RuntimeError(const char* what_arg)
  :std::runtime_error(what_arg)
  {
  }

  template class ConversionUtilities<std::int8_t, std::int16_t>;
  template class ConversionUtilities<std::int8_t, std::int32_t>;
  template class ConversionUtilities<std::int8_t, std::int64_t>;
  template class ConversionUtilities<std::int8_t, float>;
  template class ConversionUtilities<std::int8_t, double>;
  template class ConversionUtilities<std::int8_t, std::complex<float>>;
  template class ConversionUtilities<std::int8_t, std::complex<double>>;
  template class ConversionUtilities<std::int16_t, std::int16_t>;
  template class ConversionUtilities<std::int16_t, std::int32_t>;
  template class ConversionUtilities<std::int16_t, std::int64_t>;
  template class ConversionUtilities<std::int16_t, float>;
  template class ConversionUtilities<std::int16_t, double>;
  template class ConversionUtilities<std::int16_t, std::complex<float>>;
  template class ConversionUtilities<std::int16_t, std::complex<double>>;
  template class ConversionUtilities<std::int32_t, std::int16_t>;
  template class ConversionUtilities<std::int32_t, std::int32_t>;
  template class ConversionUtilities<std::int32_t, std::int64_t>;
  template class ConversionUtilities<std::int32_t, float>;
  template class ConversionUtilities<std::int32_t, double>;
  template class ConversionUtilities<std::int32_t, std::complex<float>>;
  template class ConversionUtilities<std::int32_t, std::complex<double>>;
  template class ConversionUtilities<std::int64_t, std::int16_t>;
  template class ConversionUtilities<std::int64_t, std::int32_t>;
  template class ConversionUtilities<std::int64_t, std::int64_t>;
  template class ConversionUtilities<std::int64_t, float>;
  template class ConversionUtilities<std::int64_t, double>;
  template class ConversionUtilities<std::int64_t, std::complex<float>>;
  template class ConversionUtilities<std::int64_t, std::complex<double>>;
  template class ConversionUtilities<float, std::int16_t>;
  template class ConversionUtilities<float, std::int32_t>;
  template class ConversionUtilities<float, std::int64_t>;
  template class ConversionUtilities<float, float>;
  template class ConversionUtilities<float, double>;
  template class ConversionUtilities<float, std::complex<float>>;
  template class ConversionUtilities<float, std::complex<double>>;
  template class ConversionUtilities<double, std::int16_t>;
  template class ConversionUtilities<double, std::int32_t>;
  template class ConversionUtilities<double, std::int64_t>;
  template class ConversionUtilities<double, float>;
  template class ConversionUtilities<double, double>;
  template class ConversionUtilities<double, std::complex<float>>;
  template class ConversionUtilities<double, std::complex<double>>;
  template class ConversionUtilities<char[3], std::int16_t>;
  template class ConversionUtilities<char[3], std::int32_t>;
  template class ConversionUtilities<char[3], std::int64_t>;
  template class ConversionUtilities<char[3], float>;
  template class ConversionUtilities<char[3], double>;
  template class ConversionUtilities<char[3], std::complex<float>>;
  template class ConversionUtilities<char[3], std::complex<double>>;

  template class ConversionUtilities<std::complex<float>, std::complex<float>>;
  template class ConversionUtilities<std::complex<float>, std::complex<double>>;
  template class ConversionUtilities<std::complex<double>, std::complex<float>>;
  template class ConversionUtilities<std::complex<double>, std::complex<double>>;
}
