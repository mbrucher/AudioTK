/**
 * \file MSFilter.hxx
 */

#include "MSFilter.h"

namespace ATK
{
  template<typename DataType_>
  MiddleSideFilter<DataType_>::MiddleSideFilter(gsl::index nb_channels)
    :Parent(2 * nb_channels, 2 * nb_channels)
  {
  }
  
  template<typename DataType_>
  void MiddleSideFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for (gsl::index channel = 0; channel < nb_output_ports / 2; ++channel)
    {
      const DataType* ATK_RESTRICT input0 = converted_inputs[2 * channel];
      const DataType* ATK_RESTRICT input1 = converted_inputs[2 * channel + 1];
      DataType* ATK_RESTRICT output0 = outputs[2 * channel];
      DataType* ATK_RESTRICT output1 = outputs[2 * channel + 1];

      for (gsl::index i = 0; i < size; ++i)
      {
        output0[i] = input0[i] + input1[i];
        output1[i] = input0[i] - input1[i];
      }
    }
  }
}
