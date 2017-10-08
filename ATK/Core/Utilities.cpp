/**
 * \file Utilities.cpp
 */

#include <ATK/Core/Utilities.hxx>

namespace ATK
{
  template struct ConversionUtilities<std::int8_t, std::int16_t>;
  template struct ConversionUtilities<std::int8_t, std::int32_t>;
  template struct ConversionUtilities<std::int8_t, std::int64_t>;
  template struct ConversionUtilities<std::int8_t, float>;
  template struct ConversionUtilities<std::int8_t, double>;
  template struct ConversionUtilities<std::int8_t, std::complex<float>>;
  template struct ConversionUtilities<std::int8_t, std::complex<double>>;
  template struct ConversionUtilities<std::int16_t, std::int16_t>;
  template struct ConversionUtilities<std::int16_t, std::int32_t>;
  template struct ConversionUtilities<std::int16_t, std::int64_t>;
  template struct ConversionUtilities<std::int16_t, float>;
  template struct ConversionUtilities<std::int16_t, double>;
  template struct ConversionUtilities<std::int16_t, std::complex<float>>;
  template struct ConversionUtilities<std::int16_t, std::complex<double>>;
  template struct ConversionUtilities<std::int32_t, std::int16_t>;
  template struct ConversionUtilities<std::int32_t, std::int32_t>;
  template struct ConversionUtilities<std::int32_t, std::int64_t>;
  template struct ConversionUtilities<std::int32_t, float>;
  template struct ConversionUtilities<std::int32_t, double>;
  template struct ConversionUtilities<std::int32_t, std::complex<float>>;
  template struct ConversionUtilities<std::int32_t, std::complex<double>>;
  template struct ConversionUtilities<std::int64_t, std::int16_t>;
  template struct ConversionUtilities<std::int64_t, std::int32_t>;
  template struct ConversionUtilities<std::int64_t, std::int64_t>;
  template struct ConversionUtilities<std::int64_t, float>;
  template struct ConversionUtilities<std::int64_t, double>;
  template struct ConversionUtilities<std::int64_t, std::complex<float>>;
  template struct ConversionUtilities<std::int64_t, std::complex<double>>;
  template struct ConversionUtilities<float, std::int16_t>;
  template struct ConversionUtilities<float, std::int32_t>;
  template struct ConversionUtilities<float, std::int64_t>;
  template struct ConversionUtilities<float, float>;
  template struct ConversionUtilities<float, double>;
  template struct ConversionUtilities<float, std::complex<float>>;
  template struct ConversionUtilities<float, std::complex<double>>;
  template struct ConversionUtilities<double, std::int16_t>;
  template struct ConversionUtilities<double, std::int32_t>;
  template struct ConversionUtilities<double, std::int64_t>;
  template struct ConversionUtilities<double, float>;
  template struct ConversionUtilities<double, double>;
  template struct ConversionUtilities<double, std::complex<float>>;
  template struct ConversionUtilities<double, std::complex<double>>;
  template struct ConversionUtilities<char[3], std::int16_t>;
  template struct ConversionUtilities<char[3], std::int32_t>;
  template struct ConversionUtilities<char[3], std::int64_t>;
  template struct ConversionUtilities<char[3], float>;
  template struct ConversionUtilities<char[3], double>;
  template struct ConversionUtilities<char[3], std::complex<float>>;
  template struct ConversionUtilities<char[3], std::complex<double>>;

  template struct ConversionUtilities<std::complex<float>, std::complex<float>>;
  template struct ConversionUtilities<std::complex<float>, std::complex<double>>;
  template struct ConversionUtilities<std::complex<double>, std::complex<float>>;
  template struct ConversionUtilities<std::complex<double>, std::complex<double>>;
}
