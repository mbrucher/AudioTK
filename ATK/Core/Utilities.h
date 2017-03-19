/**
 * \file Utilities.h
 */

#ifndef ATK_CORE_UTILITIES_H
#define ATK_CORE_UTILITIES_H

#include <cstdint>
#include "config.h"

namespace ATK
{
  /// Class to convert arrays from different type to another type
  template<typename DataType1, typename DataType2>
  struct ATK_CORE_EXPORT ConversionUtilities
  {
    /*!
     * @brief Method to convert an array to another, using double as the intermediate type
     * @param input_array
     * @param output_array
     * @param size
     * @param offset
     * @param ports
     */
    static void convert_array(const DataType1* input_array, DataType2* output_array, int64_t size, int64_t offset = 0, int ports = 1);
  };
}

#endif
