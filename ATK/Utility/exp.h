/**
 * \file exp.h
 */

#ifndef ATK_UTILITY_EXP_H
#define ATK_UTILITY_EXP_H

#include <cstdint>
#include <vector>

#include "config.h"

namespace ATK
{
  /// A natural exponential approximation class
  /**
   * A natural exponential approximation class, using a LUT to approximate positive exponent values, and the inverse for negative ones
   */
  template<class DataType_>
  class ATK_UTILITY_EXPORT Exp
  {
  public:
    /*!
     * @brief Constructor, with the number of steps and scale
     * @param max is the maximum value that the instance will try to approximate
     * @steps is the number of steps and the size of the LUT table
     */
    Exp(DataType_ max, int steps);

    Exp(const Exp&) = delete;
    Exp& operator=(const Exp&) = delete;

    /// Returns the approximation of the natural exponential of the input value
    DataType_ operator()(DataType_ value) const;

  private:
    /// The internal LUT table
    std::vector<DataType_> LUT;
    /// Coefficient to unscale the input value from the LUT table
    DataType_ scale;
    /// Inverse coefficient to scale the input value to the LUT table
    DataType_ invscale;
  };
}

#endif
