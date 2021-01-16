/**
 * \file TanFilter.cpp
 */

#include "TanFilter.h"

#include <boost/math/constants/constants.hpp>

#include <cassert>
#include <cmath>

namespace ATK
{
  template<typename DataType_>
  TanFilter<DataType_>::TanFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  void TanFilter<DataType_>::setup()
  {
    coeff = boost::math::constants::pi<DataType_>() / input_sampling_rate;
  }
  
  template<typename DataType_>
  void TanFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = static_cast<DataType>(tan(input[i] * coeff));
      }
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class TanFilter<float>;
#endif
  template class TanFilter<double>;
}
