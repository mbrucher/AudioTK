/**
 * \file ComplexConvertFilter.cpp
 */

#include "ComplexConvertFilter.h"

#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  RealToComplexFilter<DataType_>::RealToComplexFilter(gsl::index nb_channels)
  :Parent(2 * nb_channels, nb_channels)
  {
  }
  
  template<typename DataType_>
  void RealToComplexFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == 2*nb_output_ports);

    for(gsl::index channel = 0; channel < nb_output_ports; ++channel)
    {
      const auto* ATK_RESTRICT input1 = converted_inputs[2 * channel];
      const auto* ATK_RESTRICT input2 = converted_inputs[2 * channel + 1];
      auto* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = std::complex<DataType_>(input1[i], input2[i]);
      }
    }
  }

  template<typename DataType_>
  ComplexToRealFilter<DataType_>::ComplexToRealFilter(gsl::index nb_channels)
    :Parent(nb_channels, 2 * nb_channels)
  {
  }

  template<typename DataType_>
  void ComplexToRealFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(2* nb_input_ports == nb_output_ports);

    for (gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const auto* ATK_RESTRICT input = converted_inputs[channel];
      auto* ATK_RESTRICT output1 = outputs[2 * channel];
      auto* ATK_RESTRICT output2 = outputs[2 * channel + 1];
      for (gsl::index i = 0; i < size; ++i)
      {
        output1[i] = std::real(input[i]);
        output2[i] = std::imag(input[i]);
      }
    }
  }

  template class RealToComplexFilter<float>;
  template class ComplexToRealFilter<float>;
#if ATK_ENABLE_INSTANTIATION
  template class RealToComplexFilter<double>;
  template class ComplexToRealFilter<double>;
#endif
}
