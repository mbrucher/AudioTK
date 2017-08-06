/**
 * \file TanhShaperFilter.cpp
 */

#include "TanhShaperFilter.h"

#include <ATK/Utility/fmath.h>

#include <cassert>
#include <cmath>

namespace ATK
{
  template<typename DataType_>
  TanhShaperFilter<DataType_>::TanhShaperFilter(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  TanhShaperFilter<DataType_>::~TanhShaperFilter()
  {
  }
  
  template<typename DataType_>
  void TanhShaperFilter<DataType_>::process_impl(std::size_t size) const
  {
    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        auto exp = fmath::exp(input[i]);
        auto invexp = 1 / exp;
        output[i] = (exp - invexp) / (exp + invexp);
      }
    }
  }
  
  template class TanhShaperFilter<float>;
  template class TanhShaperFilter<double>;
}
