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
  template<class DataType_>
  class ATK_UTILITY_EXPORT Exp
  {
  public:
    Exp(DataType_ max, int steps);

    DataType_ operator()(DataType_ value) const;

  protected:
    std::vector<DataType_> LUT;
    DataType_ scale;
    DataType_ invscale;
  };
}

#endif