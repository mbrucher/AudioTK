/**
 * \file Utilities.hxx
 */

#include <ATK/Core/Utilities.h>
#include <ATK/Core/TypeTraits.h>

#include <cstring>

#include <boost/mpl/equal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

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
}
