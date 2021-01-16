/**
 * \file DryWetFilter.hxx
 */

#include "DryWetFilter.h"
#include <ATK/Core/TypeTraits.h>

#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  DryWetFilter<DataType_>::DryWetFilter(gsl::index nb_channels)
  :Parent(2 * nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  void DryWetFilter<DataType_>::set_dry(double dry)
  {
    if(dry < 0 || dry > 1)
    {
      throw std::out_of_range("Dry/wet must be a value between 0 and 1");
    }
   
    this->dry = dry;
  }

  template<typename DataType_>
  double DryWetFilter<DataType_>::get_dry() const
  {
    return dry;
  }

  template<typename DataType_>
  void DryWetFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == 2 * nb_output_ports);
    
    for(gsl::index channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input0 = converted_inputs[2 * channel];
      const DataType* ATK_RESTRICT input1 = converted_inputs[2 * channel + 1];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = static_cast<DataType>(input0[i] * static_cast<typename TypeTraits<DataType>::Scalar>(dry) + input1[i] * static_cast<typename TypeTraits<DataType>::Scalar>(1 - dry));
      }
    }
  }
}
