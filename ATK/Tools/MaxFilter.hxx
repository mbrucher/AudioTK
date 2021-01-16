/**
 * \file MaxFilter.hxx
 */

#include "MaxFilter.h"

namespace ATK
{
  template<typename DataType_>
  MaxFilter<DataType_>::MaxFilter(gsl::index nb_channels)
  :Parent(2 * nb_channels, nb_channels)
  {
  }

  template<typename DataType_>
  void MaxFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == 2 * nb_output_ports);

    for (gsl::index channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input0 = converted_inputs[2 * channel];
      const DataType* ATK_RESTRICT input1 = converted_inputs[2 * channel + 1];
      DataType* ATK_RESTRICT output = outputs[channel];
      for (gsl::index i = 0; i < size; ++i)
      {
        output[i] = TypeTraits<DataType>::max(input0[i], input1[i]);
      }
    }
  }
}
