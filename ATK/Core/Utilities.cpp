/**
 * \file Utilities.cpp
 */

#include "Utilities.h"

#include <complex>
#include <cstdint>

#include <boost/mpl/equal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

#include "TypeTraits.h"

namespace
{
  template<typename DataType>
  void convert_to_array(const DataType* input_array, DataType* output_array, std::size_t size, std::size_t offset, int ports)
  {
    if(ports == 1)
    {
      memcpy(reinterpret_cast<void*>(output_array), reinterpret_cast<const void*>(input_array + offset), size * sizeof(DataType));
    }
    else
    {
      for(std::size_t i = 0; i < size; ++i)
      {
        output_array[i] = input_array[i * ports + offset];
      }
    }
  }
  
  template<typename DataType1, typename DataType2>
  typename std::enable_if<!std::is_same<DataType1, DataType2>::value>::type convert_to_array(const DataType1* input_array, DataType2* output_array, std::size_t size, std::size_t offset, int ports)
  {
    for(std::size_t i = 0; i < size; ++i)
    {
      output_array[i] = ATK::TypeTraits<DataType2>::from_double(ATK::TypeTraits<DataType1>::to_double(input_array[i * ports + offset]));
    }
  }

}

namespace ATK
{
  template<typename DataType1, typename DataType2>
  void ConversionUtilities<DataType1, DataType2>::convert_array(const DataType1* input_array, DataType2* output_array, std::size_t size, std::size_t offset, int ports)
  {
    convert_to_array(input_array, output_array, size, offset, ports);
  }

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
