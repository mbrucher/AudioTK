/**
 * \file Utilities.hxx
 */

#include "Utilities.h"
#include <ATK/Core/TypeTraits.h>

#include <gsl/gsl>

#include <cstring>

namespace ATK
{
namespace Utilities
{
  template<typename DataType>
  void convert_to_array(const DataType* input_array, DataType* output_array, gsl::index size, gsl::index offset, gsl::index ports)
  {
    if(ports == 1)
    {
      memcpy(reinterpret_cast<void*>(output_array), reinterpret_cast<const void*>(input_array + offset), size * sizeof(DataType));
    }
    else
    {
      for(gsl::index i = 0; i < size; ++i)
      {
        output_array[i] = input_array[i * ports + offset];
      }
    }
  }
  
  template<typename DataType1, typename DataType2>
  typename std::enable_if<!std::is_same<DataType1, DataType2>::value>::type convert_to_array(const DataType1* input_array, DataType2* output_array, gsl::index size, gsl::index offset, gsl::index ports)
  {
    for(gsl::index i = 0; i < size; ++i)
    {
      output_array[i] = ATK::TypeTraits<DataType2>::from_double(ATK::TypeTraits<DataType1>::to_double(input_array[i * ports + offset]));
    }
  }
}

  template<typename DataType1, typename DataType2>
  void ConversionUtilities<DataType1, DataType2>::convert_array(const DataType1* input_array, DataType2* output_array, gsl::index size, gsl::index offset, gsl::index ports)
  {
    Utilities::convert_to_array(input_array, output_array, size, offset, ports);
  }
}
