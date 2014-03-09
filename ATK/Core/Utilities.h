/**
 * \file Utilities.h
 */

#ifndef ATK_CORE_UTILITIES_H
#define ATK_CORE_UTILITIES_H

namespace ATK
{
  template<typename DataType1, typename DataType2>
  struct ConversionUtilities
  {
    static void convert_array(const DataType1* input_array, DataType2* output_array, long size, int offset = 0);
  };
}

#endif
