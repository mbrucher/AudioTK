/**
 * \file Utilities.h
 */

#ifndef ATK_CORE_UTILITIES_H
#define ATK_CORE_UTILITIES_H

#include <ATK/Core/config.h>

#include <gsl/gsl>

#include <cstddef>

namespace ATK
{
  /// Class to convert arrays from different type to another type
  template<typename DataType1, typename DataType2>
  class ATK_CORE_EXPORT ConversionUtilities
  {
  public:
    /*!
     * @brief Method to convert an array to another, using double as the intermediate type
     * @param input_array
     * @param output_array
     * @param size
     * @param offset
     * @param ports
     */
    static void convert_array(const DataType1* input_array, DataType2* output_array, gsl::index size, gsl::index offset = 0, gsl::index ports = 1);
  };
  
  class ATK_CORE_EXPORT RuntimeError: public std::runtime_error
  {
  public:
    explicit RuntimeError(const std::string& what_arg);
    explicit RuntimeError(const char* what_arg);
  };
}

#endif
