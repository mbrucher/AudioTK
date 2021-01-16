/**
 * \file GainFilter.cpp
 */

#include "GainFilter.h"
#include <ATK/Core/Utilities.h>

#include <cassert>
#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  ParentGainFilter<DataType_>::ParentGainFilter(gsl::index nb_channels, size_t LUTsize, size_t LUTprecision)
  :Parent(nb_channels, nb_channels), LUTsize(LUTsize), LUTprecision(LUTprecision), gainLUT(LUTsize, 0)
  {
  }
  
  template<typename DataType_>
  void ParentGainFilter<DataType_>::set_threshold(DataType_ threshold)
  {
    if (threshold <= 0)
    {
      throw ATK::RuntimeError("Threshold factor must be strictly positive value");
    }
    this->threshold = 1 / threshold;
  }

  template<typename DataType_>
  void ParentGainFilter<DataType_>::set_threshold_db(DataType_ threshold_db)
  {
    this->threshold = static_cast<DataType_>(std::pow(10, - threshold_db / 10));
  }

  template<typename DataType_>
  DataType_ ParentGainFilter<DataType_>::get_threshold() const
  {
    return 1 / threshold;
  }

  template<typename DataType_>
  void ParentGainFilter<DataType_>::set_ratio(DataType_ ratio)
  {
    if (ratio <= 0)
    {
      throw ATK::RuntimeError("Ratio factor must be higher than 0");
    }
    this->ratio = ratio;
    start_recomputeLUT();
  }

  template<typename DataType_>
  DataType_ ParentGainFilter<DataType_>::get_ratio() const
  {
    return ratio;
  }

#if ATK_ENABLE_INSTANTIATION
  template class ParentGainFilter<float>;
#endif
  template class ParentGainFilter<double>;
}
