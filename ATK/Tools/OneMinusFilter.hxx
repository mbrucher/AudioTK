/**
 * \file OneMinusFilter.hxx
 */

#include "OneMinusFilter.h"
#include <ATK/Core/TypeTraits.h>

#include <cassert>

namespace ATK
{
  template<typename DataType_>
  OneMinusFilter<DataType_>::OneMinusFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  void OneMinusFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = TypeTraits<DataType>::One() - input[i];
      }
    }
  }
}
