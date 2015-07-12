/**
 * \file Utilities.h
 */

#ifndef ATK_CORE_UTILITIES_H
#define ATK_CORE_UTILITIES_H

#include <cstdint>
#include "config.h"

namespace ATK
{
  template<typename DataType1, typename DataType2>
  struct ATK_CORE_EXPORT ConversionUtilities
  {
    static void convert_array(const DataType1* input_array, DataType2* output_array, int64_t size, int offset = 0, int ports = 1);
  };
}

#endif
