/**
 * \file DryWetFilter.cpp
 */

#include "DryWetFilter.h"

#include <cassert>
#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  DryWetFilter<DataType_>::DryWetFilter(int nb_channels)
  :Parent(2 * nb_channels, nb_channels), dry(1)
  {
    
  }
  
  template<typename DataType_>
  DryWetFilter<DataType_>::~DryWetFilter()
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
  void DryWetFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == 2 * nb_output_ports);
    
    for(int channel = 0; channel < nb_output_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input0 = converted_inputs[2 * channel];
      const DataType* ATK_RESTRICT input1 = converted_inputs[2 * channel + 1];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        *(output++) = static_cast<DataType>(*(input0++) * dry + *(input1++) * (1 - dry));
      }
    }
  }
  
  template class DryWetFilter<std::int16_t>;
  template class DryWetFilter<std::int32_t>;
  template class DryWetFilter<int64_t>;
  template class DryWetFilter<float>;
  template class DryWetFilter<double>;
}
