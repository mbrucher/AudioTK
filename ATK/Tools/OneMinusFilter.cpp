/**
 * \file OneMinusFilter.cpp
 */

#include "OneMinusFilter.h"

#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<typename DataType_>
  OneMinusFilter<DataType_>::OneMinusFilter(int nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  OneMinusFilter<DataType_>::~OneMinusFilter()
  {
  }

  template<typename DataType_>
  void OneMinusFilter<DataType_>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == nb_output_ports);

    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
      {
        output[i] = static_cast<DataType>(static_cast<TypeTraits<DataType>::Scalar>(1) - static_cast<TypeTraits<DataType>::Scalar>(input[i]));
      }
    }
  }
  
  template class OneMinusFilter<float>;
  template class OneMinusFilter<double>;
  template class OneMinusFilter<std::complex<float>>;
  template class OneMinusFilter<std::complex<double>>;
}
