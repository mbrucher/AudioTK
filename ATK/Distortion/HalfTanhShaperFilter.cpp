/**
 * \file HalfTanhShaperFilter.cpp
 */

#include "HalfTanhShaperFilter.h"
#include <ATK/Utility/fmath.h>

#include <cassert>
#include <cmath>

namespace ATK
{
  template<typename DataType_>
  HalfTanhShaperFilter<DataType_>::HalfTanhShaperFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  void HalfTanhShaperFilter<DataType_>::set_coefficient(DataType coeff)
  {
    if(coeff <= 0)
    {
      throw std::out_of_range("Coefficient must be strictly positive.");
    }
    this->coeff = coeff;
  }
  
  template<typename DataType_>
  DataType_ HalfTanhShaperFilter<DataType_>::get_coefficient() const
  {
    return coeff;
  }

  template<typename DataType_>
  void HalfTanhShaperFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        if(input[i] < 0)
        {
          auto exp = fmath::exp(2 * coeff * input[i]);
          output[i] = (exp - 1) / (coeff * (exp + 1));
        }
        else
        {
          output[i] = input[i];
        }
      }
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class HalfTanhShaperFilter<float>;
#endif
  template class HalfTanhShaperFilter<double>;
}
