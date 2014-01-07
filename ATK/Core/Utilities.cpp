/**
 * \file Utilities.cpp
 */

#include "Utilities.h"

#include <cstdint>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/utility/enable_if.hpp>

#include "TypeTraits.h"

namespace
{
  template<typename DataType>
  void convert_to_array(const DataType* input_array, DataType* output_array, int size)
  {
    for(int i = 0; i < size; ++i)
    {
      output_array[i] = input_array[i];
    }
  }
  
  template<typename DataType1, typename DataType2>
  typename boost::disable_if<typename boost::mpl::equal<typename boost::mpl::vector<DataType1>::type, typename boost::mpl::vector<DataType2>::type>::type, void>::type
      convert_to_array(const DataType1* input_array, DataType2* output_array, int size)
  {
    for(int i = 0; i < size; ++i)
    {
      output_array[i] = ATK::TypeTraits<DataType2>::from_double(ATK::TypeTraits<DataType1>::to_double(input_array[i]));
    }
  }

}

namespace ATK
{
  template<typename DataType1, typename DataType2>
  void ConversionUtilities<DataType1, DataType2>::convert_array(const DataType1* input_array, DataType2* output_array, int size)
  {
    convert_to_array(input_array, output_array, size);
  }
  
  template struct ConversionUtilities<std::int16_t, std::int16_t>;
  template struct ConversionUtilities<std::int16_t, std::int32_t>;
  template struct ConversionUtilities<std::int16_t, std::int64_t>;
  template struct ConversionUtilities<std::int16_t, float>;
  template struct ConversionUtilities<std::int16_t, double>;
  template struct ConversionUtilities<std::int32_t, std::int16_t>;
  template struct ConversionUtilities<std::int32_t, std::int32_t>;
  template struct ConversionUtilities<std::int32_t, std::int64_t>;
  template struct ConversionUtilities<std::int32_t, float>;
  template struct ConversionUtilities<std::int32_t, double>;
  template struct ConversionUtilities<std::int64_t, std::int16_t>;
  template struct ConversionUtilities<std::int64_t, std::int32_t>;
  template struct ConversionUtilities<std::int64_t, std::int64_t>;
  template struct ConversionUtilities<std::int64_t, float>;
  template struct ConversionUtilities<std::int64_t, double>;
  template struct ConversionUtilities<float, std::int16_t>;
  template struct ConversionUtilities<float, std::int32_t>;
  template struct ConversionUtilities<float, std::int64_t>;
  template struct ConversionUtilities<float, float>;
  template struct ConversionUtilities<float, double>;
  template struct ConversionUtilities<double, std::int16_t>;
  template struct ConversionUtilities<double, std::int32_t>;
  template struct ConversionUtilities<double, std::int64_t>;
  template struct ConversionUtilities<double, float>;
  template struct ConversionUtilities<double, double>;
}
