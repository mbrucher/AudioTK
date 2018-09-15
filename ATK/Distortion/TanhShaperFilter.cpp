/**
 * \file TanhShaperFilter.cpp
 */

#include <ATK/Distortion/TanhShaperFilter.h>

#include <ATK/Utility/fmath.h>

#include <cassert>
#include <cmath>

namespace ATK
{
  template<typename DataType_>
  TanhShaperFilter<DataType_>::TanhShaperFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels), coeff(1)
  {
  }
  
  template<typename DataType_>
  TanhShaperFilter<DataType_>::~TanhShaperFilter()
  {
  }
  
  template<typename DataType_>
  void TanhShaperFilter<DataType_>::set_coefficient(DataType coeff)
  {
    if(coeff <= 0)
    {
      throw std::out_of_range("Coefficient must be strictly positive.");
    }
    this->coeff = coeff;
  }
  
  template<typename DataType_>
  DataType_ TanhShaperFilter<DataType_>::get_coefficient() const
  {
    return coeff;
  }

  template<typename DataType_>
  void TanhShaperFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        auto exp = fmath::exp(coeff * input[i]);
        auto invexp = 1 / exp;
        output[i] = (exp - invexp) / (coeff * (exp + invexp));
      }
    }
  }
  
  template class TanhShaperFilter<float>;
  template class TanhShaperFilter<double>;
}
